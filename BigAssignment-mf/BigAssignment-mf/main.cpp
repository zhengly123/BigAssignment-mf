#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
#include "MagicCube.h"
using namespace std;

MagicCube a, b;

void simulation()//读入操作并模拟
{
	int t1, t2;
	while (cin >> t1 >> t2)
	{
		a.rotate(t1, t2);
	}
	a.output();
}

void check_rotate()//debug旋转
{
	b.set_different_number();
	for (int i = 0; i < Face_Count; ++i)
	{
		a.set_different_number();
		a.rotate(i, 0);
		//a.output_check(b, 1);
		//if (!a.accuracy_check()) puts("ERR");

		a.set_different_number();
		a.rotate(i, 1);
		//a.output_check(b, 1);
		//if (!a.accuracy_check()) puts("ERR");
	}
}

void work()
{

}

int main()
{
	freopen("mf.in", "r", stdin);
	freopen("mf.out", "w", stdout);

	work();
	
	return 0;
}