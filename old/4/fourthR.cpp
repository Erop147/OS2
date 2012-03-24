#include <cstdlib>

const int size = 1 << 8;

int A[size][size];
int B[size][size];
int R[size][size];

int main()
{
	srand(147);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			A[i][j] = rand();
			B[i][j] = rand();
		}
	}

	
	for (int x = 0; x < size; ++x)
	{
		for (int y = 0; y < size; ++y)
		{
			for (int i = 0; i < size; ++i)
			{
				R[x][y] += A[x][i] * B[i][y];
			}
		}
	}

	return 0;
}