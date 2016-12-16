#include"MagicCube.h"
#include<stdexcept>
//#include<utility>
typedef std::pair<int, int> pii;
using std::make_pair;

void MagicCube::set_edge_number()
{
	pii next[6][9];
	int map[6][6];
	//Under
	next[0][1] = make_pair(1, 7), next[0][3] = make_pair(2, 7);
	next[0][5] = make_pair(4, 7), next[0][7] = make_pair(3, 7);
	//Up
	next[5][1] = make_pair(3, 1), next[5][3] = make_pair(2, 1);
	next[5][5] = make_pair(4, 1), next[5][7] = make_pair(1, 1);
	//middle
	for (int i = 1; i < 5; ++i) next[i][3] = make_pair(i % 4 + 1, 5);
	//complete symmetric relationship
	for (int i = 0; i < 6; ++i)
		for (int j = 1; j < 9; j += 2)
			if (next[i][j] != make_pair(0, 0))
				next[next[i][j].first][next[i][j].second] = make_pair(i, j);
	//
	for (int i = 0; i < 6; ++i)
		for (int j = 1; j < 9; j += 2)
			map[i][next[i][j].first] = j;
	for (int i = 0; i < 6; ++i)
		for (int j = 1; j < 9; j += 2)
		{
			pii &nex = next[i][j];
			num[i][j] = map[color[i][j]][color[nex.first][nex.second]];
		}
}

pii MagicCube::get_color_and_num(const int _face, const int _num)
{
	return make_pair(color[_face][_num], num[_face][_num]);
}

cornerblock MagicCube::get_current_cornerblock(const int _face, const int _num)
{
	cornerblock ret;
	ret.push(get_color_and_num(_face, _num));
	if (_face == 0)
	{
		const int related[9] = { 1,-1,4,-1,-1,-1,2,-1,3 };
		ret.push(get_color_and_num(related[_num], 6));
		ret.push(get_color_and_num(related[_num] % 4 + 1, 8));
	}
	else if (_face == 5)
	{
		const int related[9] = { 2,-1,3,-1,-1,-1,1,-1,4 };
		ret.push(get_color_and_num(related[_num], 0));
		ret.push(get_color_and_num(related[_num] % 4 + 1, 2));
	}
	else
	{
		const int related[9] = { 2,-1,0,-1,-1,-1,8,-1,6 };
		if (_num == 0 || _num == 6)//侧面相邻块
			ret.push(get_color_and_num(_face % 4 + 1, related[_num]));
		else
			ret.push(get_color_and_num((_face + 4 - 2) % 4 + 1, related[_num]));

		int related2[5][9];
		related2[1][0] = related2[2][2] = 6, related2[2][0] = related2[3][2] = 0;
		related2[3][0] = related2[4][2] = 2, related2[4][0] = related2[1][2] = 8;
		related2[1][6] = related2[2][8] = 0, related2[2][6] = related2[3][8] = 6;
		related2[3][6] = related2[4][8] = 8, related2[4][6] = related2[1][8] = 2;
		if (_num == 0 || _num == 2)//顶面/底面相邻块
			ret.push(get_color_and_num(5,related2[_face][_num]));
		else
			ret.push(get_color_and_num(0, related2[_face][_num]));
	}
	ret.sort();
	return ret;
}

int MagicCube::get_standard_number(const int _face, const int _num)
{
	cornerblock cur = get_current_cornerblock(_face, _num);
	std::vector<cornerblock>::iterator p = std::find(standard.begin(), standard.end(), cur);
	return p->find(color[_face][_num]);
}

void MagicCube::set_corner_number()
{
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 9; j += 2)
		{
			if (j == 4) continue;
			num[i][j] = get_standard_number(i, j);
		}
}

void MagicCube::set_number()
{
	for (int i = 0; i < 6; ++i) num[i][4] = 4;//set_center_number
	set_edge_number();
	set_corner_number();
}

void MagicCube::set_color(const char input_data[][20])
{
	const int map_face[6] = { 1,3,4,2,5,0 };
	int map_color[100];//WRGBYO
	memset(map_color, -1, sizeof(map_color));
	memset(num, 0, sizeof(num));
	for (int i = 0; i < 6; ++i)
	{
		map_color[input_data[i][4]] = map_face[i];
	}
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 9; ++j)
		{
			color[map_face[i]][j] = map_color[input_data[i][j]];
		}
	for (int i = 0; i < 6; ++i)//check
		for (int j = 0; j < 9; ++j)
			if (color[i][j] < 0) throw 1;

}

void MagicCube::input(const char input_data[][20])
{
	set_color(input_data);
	set_number();
}