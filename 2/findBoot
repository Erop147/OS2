#include <cstdio>
#include <vector>
using namespace std;

const char imageName[] = "plan9";
                                                     
void printBoot(FILE *in, long off)
{
	fseek(in, off - 512, SEEK_SET);
	char fname[50];
	sprintf(fname, "boot%09ld.bin", off);
	FILE *out = fopen(fname, "wb");

	for (int i = 0; i < 512; ++i)
	{
		char tmp = getc(in);
		if (ferror(in))
		{
			printf("Can't read from %s!\n", imageName);
			break;                           
		}
		putc(tmp, out);
		if (ferror(out))
		{
			printf("Can't write to %s!\n", fname);
			break;                           
		}
	}
	fclose(out);
}
int main()
{
	FILE *in = fopen(imageName, "rb");

	char prv = getc(in);	
	long pos = 1;
	vector<long> positions;
	while(!feof(in))
	{
		char cur = getc(in);
		if (ferror(in))
		{
			printf("Can't read from %s!\n", imageName);
			break;
		}
		++pos;

		if (prv == char(0x55) && cur == char(0xAA) && pos >= 512)
		{
			positions.push_back(pos);
			printf("%ld\n", pos);
		}
		prv = cur;
	}
	for(vector<long>::iterator it = positions.begin(); it != positions.end(); ++it)
	{
		printBoot(in, *it);
	}
	fclose(in);
	return 0;
}