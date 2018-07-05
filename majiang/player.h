#ifndef __PLAYER_H__

#define __PLAYER_H__

#include"majiang.h"

class Player //玩家类
{
public:
	// 默认构造函数
	Player();
	//玩家构造函数，初始化手牌和桌牌
	Player(player p);

	//设置番数
	void setFanshu(int n);
	//设置胡牌状态
	void setHupai(bool h);
	//获得胡牌状态
	bool getHupai();
	//获得番数
	int getFanshu();
	//获得玩家的方向
	player getWanjia();
	//获得实际手牌数量
	int getPaiNum();
	//获得某种牌的数量
	int getPaiNum(Majiang m);
	int hasPaiNum(int n);
	//获得桌角区的使用情况,返回空着的行数
	int getZJcols();
	//获得和这张牌相同的桌角行数
	int getZJcols(Majiang m);
	//获得手牌中类型数量
	int getTypeNum(int n);
	int getTypeNum();
	//获得手牌里数量是
	//获得手牌
	Majiang* getShoupai();
	//获得桌角牌
	const Majiang& getZhuopai(int i,int j);
	//出一张牌
	Majiang throwPai(int n); 
	//抓牌（4张）
	void addPai(Majiang* m,int lenth=4);
	//摸牌（1张）默认理牌
	void addPai(Majiang m, bool li = !LIPAI_SWITCH);
	//把出的牌放到自己前面的牌池
	void addPaichi(Majiang m);
	//获得牌池
	const Majiang* getPaichi();
	//计算牌池的可用索引
	int getPaichiNum();
	//牌比较
	static int mjCompare(const void* a, const void* b);
	//理牌
	void liPai();
	//能碰吗
	bool canPeng(Majiang m);
	//碰牌
	bool pengPai(Majiang m);
	bool pengPai(Majiang m,bool peng);
	//能杠吗
	int canGang(Majiang m);
	//能杠吗延时
	int* canGang_1();
	const Majiang* canGang_2();
	//杠牌，延时
	bool gangPai_1(int *n,bool gang);
	bool gangPai_1(int *n);
	bool gangPai_2(const Majiang* m,bool gang);
	bool gangPai_2(const Majiang* m);
	//杠牌从手中杠
	bool gangPai_Shou(Majiang m,bool gang);
	bool gangPai_Shou(Majiang m);
	//杠牌从桌角杠
	bool gangPai_Zhuo(Majiang m,bool gang);
	bool gangPai_Zhuo(Majiang m);
	//判断能胡牌吗（重点难点）
	bool canHu(Majiang m);
	bool canHu();
	//胡牌
	bool huPai();
	bool huPai(bool x);
	bool huPai(Majiang n);
	bool huPai(Majiang n , bool x);
	//重载玩家相等
	//void operator=(const Player &mj)
	//{
	//	*this = mj;

	//};

	int p_fanshu;  //牌的番数
	Majiang zhuopai[MAJIANG_ZHUOJIAO_COLS][MAJIANG_ZHUOJIAO_ROWS]; //碰杠的牌
private:
	player p_wanjia; //玩家的方位
	bool hule = false;//判断玩家是否胡了
	Majiang shoupai[MAX_MAJIANG_SHOU]; //手里的牌
	Majiang paichi[MAX_MAJIANG_PAICHI];//面前自己打出的牌
};

#endif