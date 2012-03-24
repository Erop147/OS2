#include <cstdio>
#include <cstdlib>

char* code="org 0x7c00\n"
"	cli\n"
"	xor ax, ax\n"
"	mov ds, ax\n"
"	mov es, ax\n"
"	mov ss, ax\n"
"	sti\n"
"	mov ah, 0x02\n"
"	mov al, [sectors]\n"
"	mov cx, 0x0002\n"
"	mov bx, buff\n"
"	int 0x13\n"
"\n"
"	mov cx, end2-buff\n"
"	mov di, buff\n"
"	cld\n"
"%%define poly_low 0x8320\n"
"%%define poly_high 0xedb8\n"
"\n"
"	mov ax, [current_crc + 2]\n"
"	mov bx, [current_crc + 0]\n"
"\n"
"crc32_loop:\n"
"	xor bl, [di]\n"
"	inc di\n"
"\n"
"	push cx\n"
"\n"
"	mov cx, 8\n"
"crc32_1b_loop:\n"
"	shr ax, 1\n"
"	rcr bx, 1\n"
"	jnc L0\n"
"	xor bx, poly_low\n"
"	xor ax, poly_high\n"
"L0:\n"
"	loop crc32_1b_loop\n"
"\n"
"	pop cx\n"
"	loop crc32_loop\n"
"\n"
"	xor ax, 0xffff\n"
"	xor bx, 0xffff\n"
"	mov [current_crc + 2], ax\n"
"	mov [current_crc + 0], bx\n"
"	cmp ax, [crc32 + 2]\n"
"	jne @err\n"
"\n"
"	cmp bx, [crc32 + 0]\n"
"	jne @err\n"
"\n"
"	jmp buff\n"
"@err:\n"
"	mov ax, 0x0300\n"
"	xor bx, bx\n"
"	int 0x10\n"
"	mov ax, 0x1301\n"
"	mov bx, 0x0007\n"
"	mov cx, crc32-crcErr\n"
"	mov bp, crcErr\n"
"	int 0x10\n"
"	cli\n"
"	hlt\n"
"crcErr:\n"
"db \"CRC don't equal!\"\n"
"crc32:\n"
"dd 0x%X\n"
"crcpoly:\n"
"	dd 0xEDB88320\n"
"current_crc:\n"
"	dd 0xFFFFFFFF\n"
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
		crc ^= buff[i];
		for (int j = 0; j < 8; ++j)
		{
			if (crc & 1)
			{
				crc >>= 1;
				crc ^= crcPoly;
			}
			else
			{
				crc >>= 1;
			}
		}
	}
	return crc ^ 0xFFFFFFFFUL; 
}


int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		fprintf(stderr, "No args\n");
		return 0;
	}
	const int MAXSIZE = 30 * 1024;
	unsigned char buffer[MAXSIZE];
	FILE *in = fopen(argv[1], "r");
	if (in == NULL)
	{
		fprintf(stderr,"Can't open file %s\n", argv[1]);
		return 0;
	}

	if (fseek(in, 0, SEEK_END) != 0)
	{
		fprintf(stderr, "Can't seek\n");
		return 0;
	}

	if (ftell(in) > MAXSIZE)
	{
		fprintf(stderr, "File too long\n");
		return 0;
	}

	if (fseek(in, 0, SEEK_SET) != 0)
	{
		fprintf(stderr, "Can't seek\n");
		return 0;
	}

	int size = fread(buffer, 1, MAXSIZE, in);
	if (fclose(in))
	{
		fprintf(stderr, "Can't close file %s\n", argv[1]);
		return 0;
	}
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

	if (fprintf(out, code, Crc32(buffer, size), sectors) < 0)
	{
		fprintf(stderr,"Can't write to boot.asm\n");
		return 0;
	}

	for(int i = 0; i < size; ++i)
	{
		if (fprintf(out, "db 0x%X\n", buffer[i]) < 0)
		{
			fprintf(stderr,"Can't write to boot.asm\n");
			return 0;
		}
	}
	fprintf(out, code2, 512 * (sectors + 1));
	if (fclose(out))
	{
		fprintf(stderr, "Can't close boot.asm\n");
	}

	system("nasm boot.asm -o boot.bin");
	return 0;
}