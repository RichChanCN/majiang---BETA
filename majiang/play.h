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
	//构造函数
	Play();
	//设置庄家
	void setZhuangjia(player p = null);
	//获得当前庄家
	player getZhuangjia();
	//获得一个玩家
	Player getPlayer(player p);
	//获得牌堆
	Paidui getPaidui();
	//获得索引
	int getIndex();
	//获得剩余牌数
	int getNumber();
	//获得每胡的玩家数
	int getHuplayernum();
	//开始抓牌之前的准备
	int readyToGo(player p = null);
	//抓4张牌
	void dividePai(player p);
	//摸1张牌
	void giveOnePai(player p, bool li = !LIPAI_SWITCH);
	//出牌
	void chupai(player p);
	void chupai(player p,int n);
	//谁能胡
	int whoCanHu(Majiang m);
	//谁能碰
	int whoCanPeng(Majiang m);
	//谁能杠
	int whoCanGang(Majiang m);
	//第一阶段
	void go_FirstStep();
	//第二阶段（循环）
	void go_SecondStep();
	//玩家出牌
	int chuPaiAI(player n);
	void show();

	Player wanjia[5];
	Paidui paidui;
	Majiang keypai;//当前的关键牌
	player zhuangjia = null;//当前的庄家
	int m_index = 0;//下一张被抓走的麻将索引
	int m_number = MAX_MAJIANG_NUM;//牌堆剩余的麻将
};
#endif