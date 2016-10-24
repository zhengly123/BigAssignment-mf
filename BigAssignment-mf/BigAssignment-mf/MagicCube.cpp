#include <cstdio>
#include <iostream>
#include "MagicCube.h"
const int _new[Block_Count] = { 1,2,3,8,0,4,7,6,5};
const int _old[Block_Count * 2] = { 4,0,1,2,5,8,7,6,3,0,1,2,5,8,7,6,3 };
const int mod4[9] = { 0,1,2,3,4,1,2,3,4 };
const int INF = 999999999;
int involved_face[4] = { -INF,5,-INF,0 };
int involved_block[4][3] = { { 8,5,2 },{},{ 0,3,6 },{} };//顺时针

inline void swap(int& a, int &b)
{
	int t = b;
	b = a, a = t;
}

inline void MagicCube::exchange(const int f1, const int b1, const int f2, const int b2)
{
	swap(color[f1][b1], color[f2][b2]);
	swap(num[f1][b1], num[f2][b2]);
}

inline void MagicCube::set_inv(int face)//
{
	involved_face[0] = involved_face[2] = -INF;
	if (face == 1)
	{
		involved_face[0] = 2, involved_face[2] = 4;
		involved_block[1][0] = 6, involved_block[1][1] = 7, involved_block[1][2] = 8;
		involved_block[3][0] = 2, involved_block[3][1] = 1, involved_block[3][2] = 0;
	}
	else if (face == 2)
	{
		involved_face[0] = 3, involved_face[2] = 1;
		involved_block[1][0] = 0, involved_block[1][1] = 3, involved_block[1][2] = 6;
		involved_block[3][0] = 0, involved_block[3][1] = 3, involved_block[3][2] = 6;
	}
	else if (face == 3)
	{
		involved_face[0] = 4, involved_face[2] = 2;
		involved_block[1][0] = 2, involved_block[1][1] = 1, involved_block[1][2] = 0;
		involved_block[3][0] = 6, involved_block[3][1] = 7, involved_block[3][2] = 8;
	}
	else if (face == 4)
	{
		involved_face[0] = 1, involved_face[2] = 3;
		involved_block[1][0] = 8, involved_block[1][1] = 5, involved_block[1][2] = 2;
		involved_block[3][0] = 8, involved_block[3][1] = 5, involved_block[3][2] = 2;
	}
}

MagicCube::MagicCube()
{
	for (int i = 0; i < Face_Count; ++i)
		for (int j = 0; j < Block_Count; ++j)
		{
			color[i][j] = i;
			num[i][j] = j;
		}
}

MagicCube::~MagicCube()
{
}

void MagicCube::set_different_number()
{
	int cnt = 0;
	for (int i = 0; i < Face_Count; ++i)
		for (int j = 0; j < Block_Count; ++j)
			color[i][j] = ++cnt;
	//output();
}

void MagicCube::output_compare(const MagicCube& base, int hide)
{
	puts("-----------分割线-----------");
	int cnt = 0;
	for (int i = 0; i < Face_Count; ++i)
	{
		printf("---Face %d\n", i);
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
				printf((k == 2) ? "%3d\t" : "%3d", base.color[i][j * 3 + k]);
			for (int k = 0; k < 3; ++k)
			{
				if (!hide || base.color[i][j * 3 + k] != color[i][j * 3 + k] || base.num[i][j * 3 + k] != num[i][j * 3 + k])
					printf((k == 2) ? "%3d,%d\n" : "%3d,%d", color[i][j * 3 + k], num[i][j * 3 + k]);
				else printf((k == 2) ? "    _\n" : "    _");
				cnt += (base.color[i][j * 3 + k] == color[i][j * 3 + k]);
			}
		}
	}
	printf(cnt == 54 ? "-----------SAME-----------\n" : "-----------%dCHANGED--------\n", 54 - cnt);
	//printf("%d", num);
	//if (num != 34) puts("ERR");
}

bool MagicCube::accuracy_check()
{
	bool used[Block_Count*Face_Count + 1] = {}, accr = 1;
	for (int i = 0; i < Face_Count; ++i)
		for (int j = 0; j < Block_Count; ++j)
		{
			if (color[i][j] > Block_Count*Face_Count || color[i][j] <= 0)
				return false;
			if (used[color[i][j]])
				return false;
			used[color[i][j]] = 1;
		}
	return true;
}

/// <summary>
/// 旋转魔方的一个面
/// </summary>
/// <param name="face">操作的面的编号</param>
/// <param name="dir">旋转的方向，0为顺时针(默认)，否则为逆时针</param>
void MagicCube::rotate(const int face, const int dir)
{
	printf("%d %d\n", face, dir);//debug
	int tmp[9] = {}, tmp2[9] = {}, k = (dir) ? 6 : 2, t;

	for (int i = 0; i < Block_Count; ++i)
		if (i != 4)
		{
			tmp[_old[_new[i] + k]] = color[face][i];
			tmp2[_old[_new[i] + k]] = num[face][i];
		}
	tmp[4] = color[face][4];
	tmp2[4] = num[face][4];
	for (int i = 0; i < Block_Count; ++i)
	{
		color[face][i] = tmp[i];
		num[face][i] = tmp2[i];
	}

	if (face == 0 || face == 5)
	{
		int st, ed;
		k = ((dir == 0) ^ (face == 0)) ? 3 : 1;//底面顶面旋转相反
		st = (face == 0) ? 6 : 0, ed = (face == 0) ? 9 : 3;
		for (int i = 1; mod4[i + k] != 1; i = mod4[i + k])
			for (int j = st; j < ed; ++j) exchange(i, j, mod4[i + k], j);
	}
	else
	{
		k = (dir) ? 1 : -1;
		set_inv(face);
		for (int i = 0; i < 3; ++i)
		{
			tmp[i] = color[involved_face[0]][involved_block[0][i]];
			tmp2[i] = num[involved_face[0]][involved_block[0][i]];
		}
		for (int i = 0; ; i = t)
		{
			t = i + k;
			if (t >= 4) t -= 4;
			if (t == 0)//one circle
			{
				t = i;
				break;
			}
			if (t < 0) t += 4;
			for (int j = 0; j < 3; ++j)
			{
				color[involved_face[i]][involved_block[i][j]] = color[involved_face[t]][involved_block[t][j]];
				num[involved_face[i]][involved_block[i][j]] = num[involved_face[t]][involved_block[t][j]];
			}
		}
		for (int j = 0; j < 3; ++j)
		{
			color[involved_face[t]][involved_block[t][j]] = tmp[j];
			num[involved_face[t]][involved_block[t][j]] = tmp2[j];
		}
	}
}

pii MagicCube::query(int _color, int _num)
{
	for (int i = 0; i<Face_Count; ++i)
		for (int j = 0; j < Block_Count; ++j)
		{
			if (color[i][j] == _color&&num[i][j] == _num) return std::make_pair(i, j);
		}
	std::cerr << "ERROR MagicCube::query";
	return std::make_pair(-1, -1);
}

bool MagicCube::check_face(const int face)
{
	for (int i=0;i<Block_Count;++i)
		if (color[face][i]!=face) return false;
	return true;
}

bool MagicCube::check_first_level()
{
	if (!check_face(0)) return false;
	if (!check_certain_level(1)) return false;
	return true;
}

bool MagicCube::check_second_level()
{
	if (!check_face(0)) return false;
	if (!check_certain_level(1)) return false;
	if (!check_certain_level(2)) return false;
	return true;
}

bool MagicCube::check_up_face()
{
	if (!check_face(0)) return false;
	if (!check_certain_level(1)) return false;
	if (!check_certain_level(2)) return false;
	return check_face(5);
}

bool MagicCube::check_entire_cube()
{
	for (int i=0;i<Face_Count;++i)
		if (!check_face(i)) return false;
	return true;
}

void MagicCube::output(const int face)
{
	puts("-----------分割线-----------");
	for (int i = 0; i < Face_Count; ++i)
	{
		if (face < Face_Count&&face != i) continue;
		printf("---Face %d\n", i);
		for (int j = 0; j < Block_Count; ++j)
			printf((j % 3 == 2) ? "%3d\n" : "%3d", color[i][j]);
	}
	puts("---");
}

void MagicCube::output_detailed(const int face)
{
	puts("-----------分割线-----------");
	for (int i = 0; i < Face_Count; ++i)
	{
		if (face < Face_Count&&face != i) continue;
		printf("---Face %d\n", i);
		for (int j = 0; j < Block_Count; ++j)
			printf((j % 3 == 2) ? "%3d,%d\n" : "%3d,%d", color[i][j], num[i][j]);
	}
	puts("---");
}

bool MagicCube::check_certain_level(const int level)
{
	for (int i = 1; i < 5; ++i)
		for (int j = 9 - level * 3; j < 12 - level * 3; ++j)
			if (color[i][j]!=i) return false;
	return true;
}