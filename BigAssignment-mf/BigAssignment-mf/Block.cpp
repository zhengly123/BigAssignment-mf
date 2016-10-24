#include <cstdio>
#include <cstdlib>
#include "MagicCube.h"

Block::Block()
{
	color = num = 0;
}

Block::Block(int _color, int _num)
{
	color = _color;
	num = _num;
}

Block::~Block()
{
}

bool operator==(const Block& a, const Block& b)
{
	return a.color == b.color;
}

bool operator!=(const Block& a, const Block& b)
{
	return !(a == b);
}
