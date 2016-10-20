#pragma once
#define Magic_Cube
#ifndef Magic_Cube

#endif // !Magic_Cube
const int Face_Count = 6;
const int Block_Count = 9;
/*
魔方的六个面，0D，1F，2L，3B，4R，5U。每个面中心块的颜色编号即为面的编号。
*/
class MagicCube
{
public:
	int color[Face_Count][Block_Count];
	MagicCube();
	~MagicCube();
	//debug part
	void set_different_number();
	void output_check(const MagicCube & base, int hide = 0);
	bool accuracy_check();
	//operation part
	void rotate(const int face, const int dir = 0);
	//test part
	bool check_face(const int face);//判断一个面是否已经还原
	bool check_first_level();
	bool check_second_level();
	bool check_up_face();
	bool check_entire_cube();
	//IO part
	void output(const int face = 6);//输出魔方
private:
	bool check_certain_level(int level);
	void set_inv(int face);
};