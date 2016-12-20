#pragma once
#ifndef MagicCube_h
#define MagicCube_h

#include<vector>
#include<algorithm>
const int Face_Count = 6;
const int Block_Count = 9;
typedef int Arr[Face_Count][Block_Count];//store detailed informatin of face���ڴ���6�������Ϣ��������
typedef std::pair<int, int> pii;
/*
ħ���������棬0D��1F��2L��3B��4R��5U��ÿ�������Ŀ����ɫ��ż�Ϊ��ı�š�
Magiccube's six faces��0D��1F��2L��3B��4R��5U��The color of center represent the number of face 
*/
//class cornerblock;
class cornerblock
{
public:
	pii block[3];
	void sort()
	{
		std::sort(block, block + 3);
	}
	int find(int color)
	{
		for (int i = 0; i < 3; ++i)
			if (block[i].first == color) return block[i].second;
		throw std::runtime_error("the color doesn't exist in the blocks");
	}
	void push(pii a)
	{
		if (num >= 3)  throw std::runtime_error("too many blocks");
		block[num++] = a;
	}
	friend bool operator== (const cornerblock &a, const cornerblock &b)
	{
		for (int i = 0; i < 3; ++i)
			if (a.block[i].first != b.block[i].first)
				return 0;
		return 1;
	}
private:
	int num = 0;
};
class MagicCube
{
public:
	Arr color;//"color" store the color of blocks����ĳһ�����ɫ
	Arr num;//"num" store the number of blocks����ĳһ��ĳ�ʼ���ڱ��
	bool main = 1;//1 refers to main magiccube(will output the rotation),0 refers to non~����Ƿ�Ϊ��ħ����ȱʡֵΪ1����ʾ����ħ����������Ϊ��ħ����rotateĬ�ϲ��������
	int rot = 0;//the number of position changes(clockwise)ħ��������ת�Ĵ�����˳ʱ�룩
	char map_face_to_color[6];//store the color of faces
	MagicCube();
	~MagicCube();
	//debug part
	void set_different_number();
	bool accuracy_check();//jugde whether the current situtation is feasible�ж��Ƿ���ܴ���
	
	//operation part
	//��ת dirȱʡֵ0����˳ʱ�룬1��ʱ�� outputȱʡֵ-1Ĭ�� 1���������0���������
	//dir has default value 0(clockwise),and 1 is counter-clockwise
	//output has default value -1(depend on the var "main"),1 print,0 not print
	void rotate(const int face, const int dir = 0, const int output = -1);
	void rotate_direction(int dir = 1, int output = 0);//1(-1) refer to rotate clockwise(counter-)����Ϊ˳ʱ����ת��ĸ���������Ϊ��ʱ�루�������¿���
	void randomize(int step = 200, int output = 0);//rotate several times randomly�����ת���ɴ�
	//query part
	pii query(int _color, int _num);//query by the color and number of the block,get its current position
	//check part
	bool check_face(const int face);//judge whether a face is recovered�ж�һ�����Ƿ��Ѿ���ԭ
	bool check_first_level();
	bool check_second_level();
	bool check_up_face();
	bool check_entire_cube();
	//IO part
	void input(const char a[][20]);//magiccube standard input��׼ħ������
	void output(const int face = 6);//only output color�����ɫ
	void output_detailed(const int face = 6);//output color and number�����ɫ�����
	void output_compare(const MagicCube & base, int hide = 1);//compare two cubes' differences�Ա�����ħ���Ĳ���
	void output_standard_format();//output following the style of input 

private://this part of code can't be used in programming.You can skip them
	static std::vector<cornerblock> standard;
	void exchange(const int f1, const int b1, const int f2, const int b2);//����������
	void set_number();
	//set the num array from input data
	void set_color(const char input_data[][20]);
	void set_edge_number();
	void set_corner_number();
	cornerblock get_current_cornerblock(const int _face, const int _num);//get 3 related blockss
	int get_standard_number(const int _face, const int _num);//get standard number of this block
	pii get_color_and_num(const int _face, const int _num);//get color and number of this block

	void rotate_direction_one();
	void rotate_direction_change_color();

	void set_inv(int face);//����rotateʱ���ڵ���Ϳ���Ϣ
	void print_rotation(int _face, const int direction);
	bool check_certain_level(const int level);
};

#endif