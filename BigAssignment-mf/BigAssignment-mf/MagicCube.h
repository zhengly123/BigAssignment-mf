#pragma once
#ifndef MagicCube_h
#define MagicCube_h

#include<vector>
const int Face_Count = 6;
const int Block_Count = 9;
typedef int Arr[Face_Count][Block_Count];//用于储存6个面的信息数据类型
typedef std::pair<int, int> pii;
/*
魔方的六个面，0D，1F，2L，3B，4R，5U。每个面中心块的颜色编号即为面的编号。
*/
class MagicCube
{
public:
	Arr color, num;//color储存某一块的颜色，num储存某一块的初始面内编号
	bool main = 1;//标记是否为主魔方，缺省值为1（表示是主魔方）；若不为主魔方，rotate默认不输出操作
	MagicCube();
	~MagicCube();
	//debug part
	void set_different_number();
	bool accuracy_check();//判断是否可能存在
	//operation part
	//旋转 dir缺省值0代表顺时针，1逆时针 output缺省值-1默认 1输出操作，0不输出操作
	void rotate(const int face, const int dir = 0, const int output = -1);
	void randomize(int step = 200);//随机旋转若干次
	//query part
	pii query(int _color, int _num);
	//check part
	bool check_face(const int face);//判断一个面是否已经还原
	bool check_first_level();
	bool check_second_level();
	bool check_up_face();
	bool check_entire_cube();
	//IO part
	void output(const int face = 6);//输出颜色
	void output_detailed(const int face = 6);//输出颜色及编号
	void output_compare(const MagicCube & base, int hide = 1);//对比两个魔方的差异
private:
	void exchange(const int f1, const int b1, const int f2, const int b2);//交换两个块
	void set_inv(int face);//设置rotate时相邻的面和块信息
	bool check_certain_level(const int level);
};

#endif