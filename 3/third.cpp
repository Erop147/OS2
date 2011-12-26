#include <cstdio>
#include <cstdlib>

char* code="org 0x7c00\n"
"cli\n"
"xor ax, ax\n"
"mov ds, ax\n"
"mov es, ax\n"
"mov ss, ax\n"
"sti\n"
"mov ah, 0x02\n"
"mov al, [sectors]\n"
"mov cx, 0x0002\n"
"mov bx, buff\n"
"int 0x13\n"
"\n"
"mov cx, end2-buff\n"
"mov si, buff\n"
"cld\n"
"@1:\n"
"        xor eax, eax\n"
"        lodsb\n"
"        mov ebx, [crcval]\n"
"        xor eax, ebx\n"
"        and eax, 0x000000FF\n"
"        push cx\n"
"        mov cx, 8\n"
"@2:\n"
"        shr eax, 1\n"
"        jnc @3\n"
"        xor eax, [crcpoly]\n"
"@3:\n"
"        loop @2\n"
"        shr ebx, 8\n"
"        xor eax, ebx\n"
"        mov [crcval], eax\n"
"        pop cx\n"
"        loop @1\n"
"        mov eax, [crcval]\n"
"        xor eax, 0xFFFFFFFF\n"
"        mov [crcval], eax\n"
"        cmp eax, [crc32]\n"
"        jne @err\n"
"\n"
"jmp buff\n"
"@err:\n"
"mov ax, 0x0300\n"
"xor bx, bx\n"
"int 0x10\n"
"mov ax, 0x1301\n"
"mov bx, 0x0007\n"
"mov cx, crc32-crcErr\n"
"mov bp, crcErr\n"
"int 0x10\n"
"cli\n"
"hlt\n"
"crcErr:\n"
"db \"CRC don't equal!\"\n"
"crc32:\n"
"dd 0x%X\n"
"crcpoly:\n"
"        dd 0xEDB88320\n"
"crcval:\n"
"        dd 0xFFFFFFFF\n"
"sectors:\n"
"db %d\n"
"end:\n"
"times 510-($-$$) db 0\n"
"db 0x55, 0xaa\n"
"buff:\n";

char* code2="end2:\n"
"        db 0\n"
"times %d-($-$$) db 0";
//512*(sectors+1)

unsigned long Crc32(unsigned char *buff, int len)
{
    unsigned long crc = 0xFFFFFFFFUL;
    const unsigned long crcPoly = 0xEDB88320UL;
	for (int i = 0; i < len; ++i)
	{
		unsigned long t = (crc ^ buff[i]) & (0xff);
		for (int j = 0; j < 8; ++j)
		{
			if (t & 1)
			{
				t >>= 1;
				t ^= crcPoly;
			}
			else
			{
				t >>= 1;
			}
		}
		crc = (crc >> 8) ^ t;		 
	}                           
    return crc ^ 0xFFFFFFFFUL; 
}


int main(int argc, char* argv[])
{
	if(argc==1)
	{
		fprintf(stderr,"No args\n");
		return 0;
	}
	const int MAXSIZE = 30 * 1024;
	unsigned char buffer[MAXSIZE];
	FILE *in = fopen(argv[1],"r");
	if(in == NULL)
	{
		fprintf(stderr,"Can't open file %s\n", argv[1]);
		return 0;
	}

	fseek(in, 0, SEEK_END);
	
	if(ftell(in) > MAXSIZE)
	{
		fprintf(stderr, "File too long\n");
		return 0;
	}

	fseek(in, 0, SEEK_SET);
    int size = fread(buffer, 1, 30720, in);
    fclose(in);
	int sectors = (size + 1) >> 9;

	if ((size + 1) & 511)
	{
		sectors++;
	}
	FILE *out = fopen("boot.asm", "w");
	if(out == NULL)
	{
		fprintf(stderr,"Can't write to boot.asm\n");
		return 0;
	}

	fprintf(out, code, Crc32(buffer, size), sectors);

	for(int i = 0; i < size; ++i)
	{
		fprintf(out, "db 0x%X\n", buffer[i]);
	}
	fprintf(out, code2, 512 * (sectors + 1));
	fclose(out);                        
	system("nasm boot.asm -o boot.bin");
	return 0;
}