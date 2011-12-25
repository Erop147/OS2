#include <cstdio>
#include <vector>
using namespace std;

const char imageName[] = "plan9";

void printBoot(FILE *in, long off)
{
	fseek(in, off - 512, SEEK_SET);

	char buffer[512];
	int cnt = fread(buffer, 1, 512, in);
	if (cnt != 512 || ferror(in))
	{
		printf("Can't read from %s!\n", imageName);
		return;
	}

	char fname[50];
	sprintf(fname, "boot%09ld.bin", off);
	FILE *out = fopen(fname, "wb");

	if (out == NULL)
	{
		fprintf(stderr, "can't open file %s\n", fname);
		return;
	}

	cnt = fwrite(buffer, 1, 512, out);

	if (cnt != 512 || ferror(out))
	{
		printf("Can't write to %s!\n", fname);
	}

	if (fclose(out))
	{
		fprintf(stderr, "can't close file %s \n", fname);
	}
}

class bufferedReader
{
	static const int BUFFERSIZE = 1 << 16;
	char buffer[BUFFERSIZE];
	FILE *in;
	int size;
	int pos;
	bool readNext() // удалось ли прочитать
	{
		pos = 0;
		size = fread(buffer, 1, BUFFERSIZE, in);
		if (size == 0 || ferror(in))
		{
			return false;
		}
		return true;
	}

public:
	bufferedReader(FILE *_in)
	{
		in = _in;
		size = 0;
		pos = 0;
	}
	bool getNext(char &c) // была ли ошибка
	{
		if (pos == size && feof(in))
			return true;
		if (pos == size)
		{
			if (!readNext())
				return true;
		}
		c = buffer[pos];
		++pos;
		return false;
	}
	bool hasNext()
	{
		if (pos == size)
		{
			if (!readNext()) return false;
		}
		return pos < size;
	}
};

int main()
{
	FILE *in = fopen(imageName, "rb");
	if (in == NULL)
	{
		fprintf(stderr, "can't open file %s\n", imageName);
		return 0;
	}


	bufferedReader reader(in);
	char prv;
	if (reader.getNext(prv))
	{
		printf("Can't read from %s!\n", imageName);
		return 0;
	}
	long pos = 1;
	vector<long> positions;
	while(reader.hasNext())
	{
		char cur;
		if (reader.getNext(cur))
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
	if (fclose(in))
	{
		fprintf(stderr, "can't close file %s \n", imageName);
	}
	return 0;
}