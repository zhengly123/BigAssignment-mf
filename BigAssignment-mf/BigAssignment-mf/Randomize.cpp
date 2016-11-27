#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "MagicCube.h"

inline int ran(const int mod)
{
	return rand() % mod;
}

void MagicCube::randomize(int step, int output)
{
	for (int i = 0; i < step; ++i)
	{
		rotate(ran(6), ran(2), output);
	}
}