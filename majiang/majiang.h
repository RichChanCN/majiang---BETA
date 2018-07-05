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

class Majiang //麻将类
{
public:
	//默认构造函数 默认是空白、不可见、在牌堆里、不在任一玩家手中
	Majiang();
	//牌堆构造函数
	Majiang(int tv);
	//手牌构造函数
	Majiang(player p);
	//桌角牌构造函数
	Majiang(player p, state s);

	//get
	//获得麻将的值
	int getTypeValue() const;
	//获得麻将的可见性
	bool getVisibility();
	//获得麻将的状态
	state getState();
	//获得麻将的所属
	player getPlayer();
	//set
	//改变麻将的值
	void setTypeValue(int m);
	//改变麻将的可见性
	void setVisibility(bool v);
	//改变麻将的位置
	void setState(state s);
	//改变麻将的所属
	void setPlayer(player p);
	

	//重载“=”号 全相等
	void operator=(const Majiang mj) 
	{ 
		m_typevalue = mj.m_typevalue;
		m_visibility = mj.m_visibility;
		m_state = mj.m_state;
		m_player = mj.m_player;

	};
	//麻将的值和类型的传递
	void mjVTcopy(Majiang m);
	//判断麻将的值和类型相等
	bool mjVTequal(Majiang m);
	//显示一张麻将
	void showOne() const;

private:

	int m_typevalue; //麻将的值
	bool m_visibility;//麻将的可见性
	state m_state;//麻将的位置
	player m_player;//麻将的所属

};


#endif