#pragma once
#ifndef MagicCube_h
#define MagicCube_h

const int Face_Count = 6;
const int Block_Count = 9;
typedef int Arr[Face_Count][Block_Count];
/*
魔方的六个面，0D，1F，2L，3B，4R，5U。每个面中心块的颜色编号即为面的编号。
*/
class MagicCube
{
public:
	Arr color, num;
	MagicCube();
	~MagicCube();
	//debug part
	void set_different_number();
	bool accuracy_check();//判断是否可能存在
	//operation part
	void rotate(const int face, const int dir = 0);
	void randomize(int step = 200);//随机旋转若干次
	//check part
	bool check_face(const int face);//判断一个面是否已经还原
	bool check_first_level();
	bool check_second_level();
	bool check_up_face();
	bool check_entire_cube();
	//IO part
	void output(const int face = 6);
	void output_detailed(const int face = 6);
	void output_compare(const MagicCube & base, int hide = 1);//对比两个魔方的差异
	//输出魔方
private:
	void exchange(const int f1, const int b1, const int f2, const int b2);//交换两个块
	void set_inv(int face);//设置rotate时相邻的面和块信息
	bool check_certain_level(const int level);
};

#endif