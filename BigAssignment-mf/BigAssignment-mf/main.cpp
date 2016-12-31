/*#include <iostream>
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
if (cur.second ==3||cur.second==5)
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

int main()
{
freopen("mf.in", "r", stdin);
freopen("mf.out", "w", stdout);
input();
a.output();
a.output_detailed();
a.output_standard_format();
a.output_compare(b);
//solve();
//b.output_standard_format();
//b.randomize(200, 1);
//ran_and_check();
a.randomize();
solve();
puts("GET TO GETCHAR()");
getchar(); getchar();
return 0;
}*/
//
//  main.cpp
//  大作业-魔方（12-20）
//
//  Created by zyl && lyc && zyw on 2016/12/20.
//  Copyright © 2016年 lyc. All rights reserved.
//
#include <iostream>
#include "MagicCube.h"
using namespace std;
int c_side_face_to_rotate = 0;
pii ppo;
MagicCube a, b, c;  // assume that cube is the cube that we are going to restore in function level 1 to 7

bool bts(int a1, int a2, int a3)  // bts = big to small
{
	if (a1>a2 && a2>a3)
		return 1;
	return 0;
}
bool b50(int a0)  // between 5 and 0
{
	if (5>a0 && a0>0)
		return 1;
	return 0;
}
struct line
{
	int direct, time;
};
bool cb(MagicCube *cube, int face, int color)  // cb = check block.
{
	if (cube->query(face, color) == make_pair(face, color))
		return 1;
	return 0;
}
pii mp(int first, int second)  //  mp is short for make_pair
{
	return make_pair(first, second);
}
void vlateralch(MagicCube * aimc, bool clockwise)  //  now use zhengliyan's version.
{
	aimc->rotate_direction(2 * clockwise - 1);
}
void rotc(int face, int clockwise)
{
	if (face != 0 && face != 5)
	{
		if (face + c_side_face_to_rotate > 4)
			face -= 4;
		c.rotate(face + c_side_face_to_rotate, clockwise);
	}
	else
		c.rotate(face, clockwise);
}
void rottim(int face, int clockwise, int time)  //  rotate c many times (with a little improvement).
{
	if (time<0)
		cout << "Rotate wrong.\n";
	time = time % 4;
	if (time == 2)
	{
		rotc(face, clockwise);
		rotc(face, clockwise);
	}
	else if (time == 1)
		rotc(face, clockwise);
	else if (time == 3)
		rotc(face, !clockwise);
}  //  preparative work completed

pii can_move_white_to_top(MagicCube prec)  //  返回顺时针旋转（first）这一面（second）次能把某一个白色方块 转到顶上，不能则返回(-1,-1)
{
	int face;
	int facel[3][4] = { { 2,3,4,1 },{ 0,0,0,0 },{ 4,1,2,3 } }, blockl[4] = { 1,3,7,5 };
	for (face = 1; face <= 4; face++)
	{
		if (prec.color[facel[0][face - 1]][5] == prec.color[0][4])
			return make_pair(face, 1);
		if (prec.color[0][blockl[face - 1]] == prec.color[0][4])
			return make_pair(face, 2);
		if (prec.color[facel[2][face - 1]][3] == prec.color[0][4])
			return make_pair(face, 3);
	}
	return make_pair(-1, -1);
}
int white_face_on_middle_layer(MagicCube prec)
{
	int face;
	for (face = 1; face <= 4; face++)
		if (prec.color[face][1] == prec.color[0][4] || prec.color[face][7] == prec.color[0][4])
			return face;
	cout << "\n white_face_on_middle_layer wrong. \n";
	return -1;
}
void avoid_white_on_top(int pos, MagicCube * cube)
{
	while (cube->color[5][pos] == cube->color[0][4])
		cube->rotate(5, 0);
}
void level1_move_white_to_top()
{
	int goal_position_ot[4] = { 7,3,1,5 }, j, i = 0, face_to_rot;
	pii can;
	for (j = 1; j <= 7; j += 2)
		i += (c.color[5][j] == c.color[0][4]);
	for (; i<4; i++)
	{
		can = can_move_white_to_top(c);
		if (can.first != -1)
		{
			avoid_white_on_top(goal_position_ot[can.first - 1], &c);
			rottim(can.first, 0, can.second);
		}
		else
		{
			face_to_rot = white_face_on_middle_layer(c);
			avoid_white_on_top(goal_position_ot[face_to_rot - 1], &c);
			rotc(face_to_rot, 0);
			can = can_move_white_to_top(c);
			avoid_white_on_top(goal_position_ot[can.first - 1], &c);
			rottim(can.first, 0, can.second);
		}
	}
}
void level1()  // 底层十字架
{
	level1_move_white_to_top();
	int face, goal_position_ot[4] = { 7,3,1,5 }, goal_position_ob[4] = { 1,3,7,5 };
	for (face = 1; face <= 4; face++)
	{
		while (c.query(0, goal_position_ob[face - 1]).second != goal_position_ot[face - 1])
			rottim(5, 0, 1);
		rottim(face, 0, 2);
	}
}  //  level 1 succeed.

void l2for()  //  level 2 formula.
{
	rotc(2, 1);
	rotc(5, 1);
	rotc(2, 0);
	rotc(5, 0);
}
void level2()  //  底角
{
	int i, rotatetime;
	pii ppo = c.query(0, 0);  //  ppo = present position.
	for (i = 0; i<9; i += 2)
	{
		if (i == 4)
			i = 6;
		while (c.color[0][0] != c.color[0][4] || c.color[1][6] != c.color[1][4] || c.color[2][8] != c.color[2][4])
		{
			ppo = c.query(0, 0);
			if (c.color[0][0] == c.color[0][4] && c.color[1][6] == c.color[1][4] && c.color[2][8] == c.color[2][4])  //  don't need rotate
				break;
			if ((ppo.first == 0) || (ppo.first<5 && ppo.second>5))  //  If ppo not on top level, move it to top;
			{
				rotatetime = 0;
				while (ppo != make_pair(1, 6) && ppo != make_pair(2, 8) && ppo != make_pair(0, 0))  //  白色不在（0，0）及其相邻位置时
				{
					rotatetime += 1;
					rotc(0, 0);
					ppo = c.query(0, 0);
				}
				l2for();
				rottim(0, 0, 4 - rotatetime);
				ppo = c.query(0, 0);
			}
			else  //  ppo on top
			{
				while (c.query(0, 0) != make_pair(5, 6) && c.query(0, 0) != make_pair(1, 0) && c.query(0, 0) != make_pair(2, 2))
					rotc(5, 0);  //  白色不在（5，6）及其相邻位置时
				ppo = c.query(0, 0);
				while (c.color[0][0] != c.color[0][4] || c.color[1][6] != c.color[1][4] || c.color[2][8] != c.color[2][4])  //  当转到顶上
				{
					l2for();
					ppo = c.query(0, 0);
				}
			}
		}
		vlateralch(&c, 1);
	}
}  //  level 2 succeed.

void l3for(bool right)  //  right means move the block on top to right
{
	if (right)
	{
		rotc(5, 0);
		rotc(4, 0);
		rotc(5, 1);
		rotc(4, 1);
		rotc(5, 1);
		rotc(1, 1);
		rotc(5, 0);
		rotc(1, 0);
	}
	else
	{
		rotc(5, 1);
		rotc(2, 1);
		rotc(5, 0);
		rotc(2, 0);
		rotc(5, 0);
		rotc(1, 0);
		rotc(5, 1);
		rotc(1, 1);
	}
}
bool isib(MagicCube cu, int num) //  isib = is side block. Can be used only when the aim block is on face NO.1 and num must be 3 or 5.
{
	if ((num == 3 && b50(cu.color[1][3]) && b50(cu.color[2][5])) || (num == 5 && b50(cu.color[1][5]) && b50(cu.color[4][3])))
		return 1;
	return 0;
}
void level3()
{
	pii ppo;
	int i, finish = 0, face, top_list[4] = { 7,3,1,5 };
	for (i = 1; i <= 4; i++)  //  把中间层全部移到顶上
	{
		if (isib(c, 3))
		{
			while (b50(c.color[1][1]) && b50(c.color[5][7]))  //  b50 means between 5 & 0.
				rotc(5, 0);
			l3for(false);
		}
		vlateralch(&c, true);
	}
	//c.output();//check
	while (finish<4)
	{
		bool find = 0;
		for (face = 1; face<5; face++)
			if (c.color[face][1] == c.color[face][4] && b50(c.color[5][top_list[face - 1]]))
			{
				find = 1;
				break;
			}
		if (find)
		{
			for (i = 1; i<face; i++)
				vlateralch(&c, 0);
			if (c.color[5][7] == c.color[2][4])
				l3for(0);
			else
				l3for(1);
			vlateralch(&c, 1);
			finish++;
		}
		else
			rotc(5, 0);
	}
}  // level 3 completed

void l4for1()  //  f,u,r,ui,ri,fi
{
	rotc(1, 0);
	rotc(5, 0);
	rotc(4, 0);
	rotc(5, 1);
	rotc(4, 1);
	rotc(1, 1);
}
void l4for2()  //  f,r,u,ri,ui,fi
{
	rotc(1, 0);
	rotc(4, 0);
	rotc(5, 0);
	rotc(4, 1);
	rotc(5, 1);
	rotc(1, 1);
}
int yline(MagicCube cube)  //  yellow line. If there is yellow blocks in (5,1) (5,7), return 1. The other kind of yellow line return 2. If no yellow line, return 0.
{
	if (cube.color[5][1] == c.color[5][4] && cube.color[5][7] == c.color[5][4])
		return 1;
	if (cube.color[5][3] == c.color[5][4] && cube.color[5][5] == c.color[5][4])
		return 2;
	return 0;
}
int ycor(MagicCube cube)  //  yellow corner. If (5,1)(5,3) return 1. If (5,3)(5,7) return 2.
{
	if (cube.color[5][1] == c.color[5][4] && cube.color[5][3] == c.color[5][4])
		return 1;
	if ((cube.color[5][3] == c.color[5][4] && cube.color[5][7] == c.color[5][4]) ||
		(cube.color[5][7] == c.color[5][4] && cube.color[5][5] == c.color[5][4]) ||
		(cube.color[5][5] == c.color[5][4] && cube.color[5][1] == c.color[5][4]))
		return 2;
	return 0;
}
bool l4cross()
{
	int i;
	for (i = 1; i <= 7; i += 2)
		if (c.color[5][i] != c.color[5][4])
			return 0;
	return 1;
}
void level4cross()
{
	if (l4cross())
		return;
	while (!yline(c) && !ycor(c))
		l4for1();
	if (yline(c) == 1)
		rotc(5, 0);
	if (yline(c) == 2)
	{
		l4for2();
		return;
	}
	if (ycor(c))
	{
		while (ycor(c) != 1)
			rotc(5, 0);
		l4for1();
		return;
	}
}

void l4for3(int fish)  //  r,b,ri,b,r,b,b,ri
{
	if (fish == 1)
	{
		rotc(4, 1);
		rotc(5, 1);
		rotc(4, 0);
		rotc(5, 1);
		rotc(4, 1);
		rotc(5, 1);
		rotc(5, 1);
		rotc(4, 0);
	}
	else if (fish == 2)
	{
		rotc(1, 0);
		rotc(5, 0);
		rotc(1, 1);
		rotc(5, 0);
		rotc(1, 0);
		rotc(5, 1);
		rotc(5, 1);
		rotc(1, 1);
	}
}
///////////////////
void level4corner()  //1:顺小鱼。2:逆小鱼。
{
	int finish = 0, i;
	for (i = 0; i <= 8; i += 2)
	{
		if (i == 4)
			i = 6;
		finish += (c.color[5][i] == c.color[5][4]);
	}
	//c.output();//check
	switch (finish)
	{
	case 4:
	{
		break;
	}
	case 1:
	{
		while (c.color[5][0] != c.color[5][4])
			rotc(5, 0);
		if (c.color[3][0] == c.color[5][4] && c.color[1][0] == c.color[5][4] && c.color[4][0] == c.color[5][4])
			l4for3(1);
		else if (c.color[4][2] == c.color[5][4] && c.color[1][2] == c.color[5][4] && c.color[2][2] == c.color[5][4])
			l4for3(2);
		break;
	}
	case 2:
	{
		while (c.color[3][2] != c.color[5][4])
			rotc(5, 0);
		l4for3(1);
		level4corner();
		break;
	}
	case 0:
	{
		while (c.color[2][0] != c.color[5][4])
			rotc(5, 0);
		//c.output();//check
		l4for3(1);
		level4corner();
		break;
	}
	default:
	{
		cout << "level 4 wrong or bad cube.\n";
		break;
	}
	}
}

bool checkblock1()
{
	bool is;
	is = (c.color[1][0] == 1) && (c.color[2][2] == 2);
	return is;
}

bool checkblock2()
{
	bool is;
	is = (c.color[4][0] == 4) && (c.color[1][2] == 1);
	return is;
}

bool checkblock3()
{
	bool is;
	is = (c.color[3][0] == 3) && (c.color[4][2] == 4);
	return is;
}

bool checkblock4()
{
	bool is;
	is = (c.color[2][0] == 2) && (c.color[3][2] == 3);
	return is;
}



int find_right_place()
{
	for (int i = 0; i <= 3; i++)
	{
		int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
		if (checkblock1())
		{
			s1++;
			s4++;
		}
		if (checkblock2())
		{
			s1++;
			s2++;
		}
		if (checkblock3())
		{
			s2++;
			s3++;
		}
		if (checkblock4())
		{
			s3++;
			s4++;
		}
		if (s1 + s2 + s3 + s4 == 8)
			return 4;
		else {
			if (s1 == 2)
			{
				c.rotate_direction(1);
				c.rotate_direction(1);
				return 1;
			}
			else {
				if (s2 == 2)
				{
					c.rotate_direction(-1);
					return 1;
				}
				else {
					if (s3 == 2)
						return 1;
					else {
						if (s4 == 2)
						{
							c.rotate_direction(1);                   //////
							return 1;
						}
						else {
							if (checkblock1() && checkblock3())
								return 13;
							else {
								if (checkblock2() && checkblock4())
									return 24;
								else c.rotate(5, 0);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

void level5corner()
{
	int m = find_right_place();
	if (m == 4)
		;
	else {
		if (m == 1)
		{
			c.rotate(4, 1);
			c.rotate(1, 0);
			c.rotate(4, 1);
			c.rotate(3, 0);
			c.rotate(3, 0);
			c.rotate(4, 0);
			c.rotate(1, 1);
			c.rotate(4, 1);
			c.rotate(3, 0);
			c.rotate(3, 0);
			c.rotate(4, 0);
			c.rotate(4, 0);
			c.rotate(5, 1);
		}
		else {
			c.rotate(4, 1);
			c.rotate(1, 0);
			c.rotate(4, 1);
			c.rotate(3, 0);
			c.rotate(3, 0);
			c.rotate(4, 0);
			c.rotate(1, 1);
			c.rotate(4, 1);
			c.rotate(3, 0);
			c.rotate(3, 0);
			c.rotate(4, 0);
			c.rotate(4, 0);
			c.rotate(5, 1);
			level5corner();
		}
	}
}

int how_many_right()
{
	int m = 0;
	for (int i = 1; i <= 4; i++)
		if (c.color[i][1] == i)
			m++;
	if (m == 4) return 4;
	if (m == 0)  return 0;
	if (m == 1)
	{
		if (c.color[1][1] == 1)
		{
			c.rotate_direction(1);
			c.rotate_direction(1);
			return 1;
		}
		if (c.color[4][1] == 4)
		{
			c.rotate_direction(-1);
			return 1;
		}
		if (c.color[2][1] == 2)
		{
			c.rotate_direction(1);
			return 1;
		}
		return 1;
	}
	return 99;
}

void level5side()
{
	int x = how_many_right();
	if (x == 4)
		;
	else {
		if (x == 1)
		{
			if (c.color[1][1] == 2)
			{
				c.rotate(1, 0);
				c.rotate(1, 0);
				c.rotate(5, 0);
				c.rotate(2, 0);
				c.rotate(4, 1);
				c.rotate(1, 0);
				c.rotate(1, 0);
				c.rotate(2, 1);
				c.rotate(4, 0);
				c.rotate(5, 0);
				c.rotate(1, 0);
				c.rotate(1, 0);
			}
			else {
				c.rotate(1, 0);
				c.rotate(1, 0);
				c.rotate(5, 1);
				c.rotate(2, 0);
				c.rotate(4, 1);
				c.rotate(1, 0);
				c.rotate(1, 0);
				c.rotate(2, 1);
				c.rotate(4, 0);
				c.rotate(5, 1);
				c.rotate(1, 0);
				c.rotate(1, 0);
			}
		}
		else {
			c.rotate(1, 0);
			c.rotate(1, 0);
			c.rotate(5, 0);
			c.rotate(2, 0);
			c.rotate(4, 1);
			c.rotate(1, 0);
			c.rotate(1, 0);
			c.rotate(2, 1);
			c.rotate(4, 0);
			c.rotate(5, 0);
			c.rotate(1, 0);
			c.rotate(1, 0);
			level5side();
		}
	}
}

void input()//input a magiccube(represent by chars(color))
{
	char in[6][20];
	for (int i = 0; i < 6; ++i) scanf("%s", in[i]);
	c.input(in);
	//a.output_detailed();//check
	//a.output_compare(b);//check
	//a.output_standard_format();//check
}

void solve()
{
	level1();
	level2();
	level3();
	level4cross();
	level4corner();
	//c.output();
	level5corner();
	//c.output();
	level5side();
}

int main()
{
	freopen("mf.in", "r", stdin);
	freopen("mf.out", "w", stdout);
	//int randtime;
	//cout << "Please input randmize rotate time.\n";  //  test
	//cin >> randtime;//test
	//c.randomize(randtime);  //  test
	input();
	solve();
	/*for (int i = 1; i <= 99999999; ++i)//dp
	{
		c.randomize();
		c.main = 0;
		solve();
		if (c.check_entire_cube()) printf("%9d:AC",i);
		else throw 1;
	}*/
	return 0;
}