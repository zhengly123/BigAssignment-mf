#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
#include "MagicCube.h"
using namespace std;

MagicCube a, b;

void simulation()
{
	//char   buffer[500];
	//_getcwd(buffer, 500);
	//printf("directory   is:   %s ", buffer);
	int t1, t2; 
	while (cin >> t1 >> t2)
	{
		a.rotate(t1, t2);
		a.output();
	}
}

void check_rotate()
{
	for (int i = 0; i < Face_Count; ++i)
	{
		for (int j = 0; j < 2; ++j) a.rotate(i, 0);
		cout << a.check_entire_cube() << endl;
		for (int j = 0; j < 2; ++j) a.rotate(i, 1);
		cout << a.check_entire_cube() << endl;
	}
}

void work()
{
	//simulation();
	//cout << a.face_solve(0) << a.first_level_solve() << a.second_level_solve() << a.up_face_solve() << a.cube_solve();
	//check_rotate();
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

int main()
{
	freopen("mf.in", "r", stdin);
	freopen("mf.out", "w", stdout);

	work();

	system("pause");
	return 0;
}