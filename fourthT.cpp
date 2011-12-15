#include <cstdlib>

const int SH = 8;
const int size = 1 << SH;

const int sizeTiles = SH / 2;
const int MOD = sizeTiles - 1;
const int cntTiles = size / (1<<sizeTiles);

int A[cntTiles][cntTiles][1 << sizeTiles][1 << sizeTiles];
int B[cntTiles][cntTiles][1 << sizeTiles][1 << sizeTiles];
int R[cntTiles][cntTiles][1 << sizeTiles][1 << sizeTiles];

int main()
{
	srand(147);

	for (int i = 0; i < cntTiles; ++i)
	{
		for (int j = 0; j < cntTiles; ++j)
		{
			for (int x = 0; x < (1 << sizeTiles); ++x)
			{
				for (int y = 0; y < (1 << sizeTiles); ++y)
				{
					A[i][j][x][y] = rand();
					B[i][j][x][y] = rand();
				}
			}
		}
	}

	
	for (int x = 0; x < size; ++x)
	{
		for (int y = 0; y < size; ++y)
		{
			for (int i = 0; i < size; ++i)
			{	
																				// прибавляю в координаты х / (1 << sizeTiles), y / (1 << sizeTiles),
																				// x % (1 << sizeTiles), y % (1 << sizeTiles). 
				R[x >> sizeTiles][y >> sizeTiles][x & MOD][y & MOD] +=			// Если непосредственно делить - замедляется в 2 раза
					A[x >> sizeTiles][i >> sizeTiles][x & MOD][i & MOD] * B[i >> sizeTiles][y >> sizeTiles][i & MOD][y & MOD];
			}
		}
	}

	return 0;
}