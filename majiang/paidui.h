#ifndef __PAIDUI_H__
#define __PAIDUI_H__

#include"majiang.h"

class Paidui    //�ƶ���
{
public:
	//Ĭ�Ϲ��캯�������ɱ�׼��108����
	Paidui();
	//����ƶ���һ���Ƶ���Ϣ
	void getOne(int n, int m);
	//����ƶ���һ����
	Majiang getOne(int n);
	Majiang* getAll();
	//����������ӵ���
	void setShaizi(); 
	//�ƶ����ӵĵ���
	void setShaizi(int n);
	//������ӵĵ���
	int getShaizi();
	//����ƶѵ�����
	int showMargin();
	int getMargin();
	//���ƶ����ϴ��
	void xiPai();
	//ץ1�����齫
	Majiang throwOneMajiang(int n);
	//ץ��4���齫
	Majiang* throwMajiang(int n);

private:
	Majiang paidui[MAX_MAJIANG_NUM]; //�ƶ�����
	int m_margin = MAX_MAJIANG_NUM;//�ƶѵ�����
	int shaizi;//���ӵĵ���
};

#endif