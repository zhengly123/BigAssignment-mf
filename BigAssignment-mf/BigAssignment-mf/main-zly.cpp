﻿#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
#include <ctime>
#include "MagicCube.h"
using namespace std;
typedef pair<int, int> pii;
MagicCube a, b;

void simulation()//读入操作并模拟
{
	int t1, t2;
	while (cin >> t1 >> t2)
	{
		b = a;
		a.rotate(t1, t2);
		a.output_compare(b, 1);
	}
	a.output_detailed();
	//a.output_compare(b);
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
	//simulation();
	a.output_detailed();

}
//rel记录四周面的相邻两个面，rel[0]是面的前驱，[1]是面的后继
const int rel[2][6] = { { -1,4,1,2,3,-1, },{ -1, 2, 3, 4, 1, -1 } };
const int r[9] = { 2,1,1,2,-1,4,3,3,4 };//底层相关面
void solve_bottom_cross_one()
{
	pii cur = a.query(0, 1);
	int flag = 0;
	if (cur == make_pair(0, 1)) return;
	if (cur.first == 0)
		for (int i = 0; i < 2; ++i)
			a.rotate(r[cur.second], 0);
	cur = a.query(0, 1);
	if (0 < cur.first&&cur.first < 5)
	{
		if (cur.second == 1)
		{
			for (cur = a.query(0, 1); cur.first != 1; cur = a.query(0, 1)) a.rotate(5, 0);
			a.rotate(1, 0);
		}
		cur = a.query(0, 1);
		if (cur.second == 7) a.rotate(cur.first, 0);
		cur = a.query(0, 1);
		if (cur.second == 3 || cur.second == 5)
		{
			flag = (cur.second == 3);
			a.rotate(rel[flag][cur.first], 0);
			a.rotate(5, flag);
			a.rotate(rel[flag][cur.first], 1);
		}
	}
	for (cur = a.query(0, 1); cur.first == 5 && cur.second != 7; cur = a.query(0, 1))
	{
		a.rotate(5, 0);
	}
	if (cur.first == 5)
		for (int i = 0; i < 2; ++i) a.rotate(1, 0);
}

void solve_bottom_cross()
{
	for (int i = 0; i < 4; ++i)
	{
		solve_bottom_cross_one();
		if (a.query(0, 1) != make_pair(0, 1)) throw 1;//check
		a.rotate_direction();
	}
}

void solve_first_level_one()
{
#define C a.query(0,2)
	int t1;
	if (C == make_pair(0, 2)) return;
	if (C.first == 0 || (C.first < 5 && C.second>5))
	{
		if (C.first == 0) t1 = rel[0][r[C.second]];
		else
		{
			if (C.second == 8) t1 = rel[0][C.first];
			else t1 = C.first;
		}
		a.rotate(t1, 0);
		a.rotate(5, 0);
		a.rotate(t1, 1);
	}
	if (C.first == 5)
	{
		while (C.second != 8) a.rotate(5, 0);
		a.rotate(4, 0);
		a.rotate(5, 1);
		a.rotate(4, 1);
	}
	if (C.second == 2)
	{
		while (C.first != 1) a.rotate(5, 0);
		a.rotate(5, 0);
		a.rotate(4, 0);
		a.rotate(5, 1);
		a.rotate(4, 1);
	}
	if (C.second == 0)
	{
		while (C.first != 4) a.rotate(5, 0);
		a.rotate(4, 0);
		a.rotate(5, 0);
		a.rotate(4, 1);
	}
#undef C
}

void solve_first_level()
{
	for (int i = 0; i < 4; ++i)
	{
		solve_first_level_one();
		if (a.query(0, 2) != make_pair(0, 2)) throw 1;//check
		a.rotate_direction();
	}
}

void solve_second_level()
{
	for (int i = 0; i < 4; ++i)
	{
		//solve_second_level_one();
		if (a.query(0, 2) != make_pair(0, 2)) throw 1;//check
		a.rotate_direction();
	}
}

void solve()//recover the magiccube(only first level)
{
	solve_bottom_cross();
	solve_first_level();
	a.output();
}

void input()//input a magiccube(represent by chars(color))
{
	char in[6][20];
	for (int i = 0; i < 6; ++i) scanf("%s", in[i]);
	a.input(in);
	//a.output_detailed();//check
	//a.output_compare(b);//check
	//a.output_standard_format();//check
}

void ran_and_check()//debug code
{
	srand(time(0));
	auto fout = freopen("mf.in", "w", stdout);
	b.randomize();
	b.output_standard_format();
	fclose(fout);
	freopen("mf.in", "r", stdin);
	freopen("mf.out", "w", stdout);
	input();
	if (!b.accuracy_check()) throw runtime_error("Not accurate!");//check
}

/*int main()
{
	freopen("mf.in", "r", stdin);
	freopen("mf.out", "w", stdout);
	input();
	solve();
	//b.output_standard_format();
	//b.randomize(200, 1);
	//ran_and_check();
	return 0;
}*/