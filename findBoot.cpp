#include <cstdio>
#include <vector>
using namespace std;                                                     
void printBoot(FILE *in, long off)
{
	fseek(in, off - 512, SEEK_SET);
	char fname[20];
	sprintf(fname, "boot%ld.bin", off);
	FILE *out = fopen(fname, "wb");

	for (int i = 0; i < 512; ++i)
	{
		char tmp = getc(in);
		putc(tmp, out);
	}
	fclose(out);
}
int main()
{
	FILE *in = fopen("plan9", "rb");

	char prv = getc(in);	
	long pos = 1;
	vector<long> positions;
	while(!feof(in))
	{
		char cur = getc(in);
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