#ifndef __MAJIANG_H__

#define __MAJIANG_H__

#include<vector>
#include<string>
#include<string.h>
#include<iostream>
#include<stack>
#include"MyArray.h"
#include"configure.h"

using namespace std;

class Majiang //�齫��
{
public:
	//Ĭ�Ϲ��캯�� Ĭ���ǿհס����ɼ������ƶ��������һ�������
	Majiang();
	//�ƶѹ��캯��
	Majiang(int tv);
	//���ƹ��캯��
	Majiang(player p);
	//�����ƹ��캯��
	Majiang(player p, state s);

	//get
	//����齫��ֵ
	int getTypeValue() const;
	//����齫�Ŀɼ���
	bool getVisibility();
	//����齫��״̬
	state getState();
	//����齫������
	player getPlayer();
	//set
	//�ı��齫��ֵ
	void setTypeValue(int m);
	//�ı��齫�Ŀɼ���
	void setVisibility(bool v);
	//�ı��齫��λ��
	void setState(state s);
	//�ı��齫������
	void setPlayer(player p);
	

	//���ء�=���� ȫ���
	void operator=(const Majiang mj) 
	{ 
		m_typevalue = mj.m_typevalue;
		m_visibility = mj.m_visibility;
		m_state = mj.m_state;
		m_player = mj.m_player;

	};
	//�齫��ֵ�����͵Ĵ���
	void mjVTcopy(Majiang m);
	//�ж��齫��ֵ���������
	bool mjVTequal(Majiang m);
	//��ʾһ���齫
	void showOne() const;

private:

	int m_typevalue; //�齫��ֵ
	bool m_visibility;//�齫�Ŀɼ���
	state m_state;//�齫��λ��
	player m_player;//�齫������

};


#endif