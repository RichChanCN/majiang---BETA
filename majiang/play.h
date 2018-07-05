#ifndef __PLAY_H__
#define __PLAY_H__

#include<Windows.h>
#include<WinBase.h>
#include<iostream>

#include"configure.h"
#include"majiang.h"
#include"paidui.h"
#include"player.h"

class Play{
public:
	//���캯��
	Play();
	//����ׯ��
	void setZhuangjia(player p = null);
	//��õ�ǰׯ��
	player getZhuangjia();
	//���һ�����
	Player getPlayer(player p);
	//����ƶ�
	Paidui getPaidui();
	//�������
	int getIndex();
	//���ʣ������
	int getNumber();
	//���ÿ���������
	int getHuplayernum();
	//��ʼץ��֮ǰ��׼��
	int readyToGo(player p = null);
	//ץ4����
	void dividePai(player p);
	//��1����
	void giveOnePai(player p, bool li = !LIPAI_SWITCH);
	//����
	void chupai(player p);
	void chupai(player p,int n);
	//˭�ܺ�
	int whoCanHu(Majiang m);
	//˭����
	int whoCanPeng(Majiang m);
	//˭�ܸ�
	int whoCanGang(Majiang m);
	//��һ�׶�
	void go_FirstStep();
	//�ڶ��׶Σ�ѭ����
	void go_SecondStep();
	//��ҳ���
	int chuPaiAI(player n);
	void show();

	Player wanjia[5];
	Paidui paidui;
	Majiang keypai;//��ǰ�Ĺؼ���
	player zhuangjia = null;//��ǰ��ׯ��
	int m_index = 0;//��һ�ű�ץ�ߵ��齫����
	int m_number = MAX_MAJIANG_NUM;//�ƶ�ʣ����齫
};
#endif