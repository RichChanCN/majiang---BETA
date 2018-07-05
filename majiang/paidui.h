#ifndef __PAIDUI_H__
#define __PAIDUI_H__

#include"majiang.h"

class Paidui    //牌堆类
{
public:
	//默认构造函数，生成标准的108张牌
	Paidui();
	//获得牌堆中一张牌的信息
	void getOne(int n, int m);
	//获得牌堆中一张牌
	Majiang getOne(int n);
	Majiang* getAll();
	//随机生成骰子点数
	void setShaizi(); 
	//制定骰子的点数
	void setShaizi(int n);
	//获得骰子的点数
	int getShaizi();
	//获得牌堆的余量
	int showMargin();
	int getMargin();
	//把牌堆随机洗乱
	void xiPai();
	//抓1张走麻将
	Majiang throwOneMajiang(int n);
	//抓走4张麻将
	Majiang* throwMajiang(int n);

private:
	Majiang paidui[MAX_MAJIANG_NUM]; //牌堆数组
	int m_margin = MAX_MAJIANG_NUM;//牌堆的余量
	int shaizi;//骰子的点数
};

#endif