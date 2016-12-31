#pragma once
#ifndef MagicCube_h
#define MagicCube_h

const int Face_Count = 6;
const int Block_Count = 9;
typedef int Arr[Face_Count][Block_Count];
/*
ħ���������棬0D��1F��2L��3B��4R��5U��ÿ�������Ŀ����ɫ��ż�Ϊ��ı�š�
*/
class MagicCube
{
public:
	Arr color, num;
	MagicCube();
	~MagicCube();
	//debug part
	void set_different_number();
	bool accuracy_check();//�ж��Ƿ���ܴ���
	//operation part
	void rotate(const int face, const int dir = 0);
	void randomize(int step = 200);//�����ת���ɴ�
	//check part
	bool check_face(const int face);//�ж�һ�����Ƿ��Ѿ���ԭ
	bool check_first_level();
	bool check_second_level();
	bool check_up_face();
	bool check_entire_cube();
	//IO part
	void output(const int face = 6);
	void output_detailed(const int face = 6);
	void output_compare(const MagicCube & base, int hide = 1);//�Ա�����ħ���Ĳ���
	//���ħ��
private:
	void exchange(const int f1, const int b1, const int f2, const int b2);//����������
	void set_inv(int face);//����rotateʱ���ڵ���Ϳ���Ϣ
	bool check_certain_level(const int level);
};

#endif