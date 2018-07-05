#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#define MAX_MAJIANG_NUM 108 //四川麻将的麻将最大数量
#define MAX_MAJIANG_SHOU 14 //麻将在手里的最大数量
#define MAJIANG_ZHUOJIAO_COLS 4//桌角的最大行数量
#define MAJIANG_ZHUOJIAO_ROWS 4//桌角的最大列数量
#define MAX_FANSHU 8 //牌的最大番数
#define MAX_MAJIANG_PAICHI 27 //每个打出的牌的最大数量  极少情况超过27
#define LIPAI_SWITCH true //每个牌操作后洗牌的开关
#define EMPTY 40 //空牌的数值
#define MAJIANG_MOSHI 3  //剩下多少人没胡就结束 1代表血战
#define ZHUO_SHOU 5  //桌上手牌返回值

#define ZHUO_SHOU_DELAY 6 //桌手延迟杠牌
#define SHOU_DELAY 7 //手上延时杠牌


#define RESIZE_RATE 10 //物体缩放比例
#define MAX_CHAR 128

#define MAJIANG_AI true//AI开关

#define DONOT -1//什么都不做
#define ZHUAPAI 1//抓牌
#define CHUPAI 2//出牌
#define PENGPAI 3//碰牌
#define GANGPAI 4//刚牌
#define HUPAI 5//胡牌
#define JIANCE 6//检测
#define CANHU 7//能胡
#define CANPENG 8//能碰
#define CANGANG 9//能杠

#define RUNNING 1
#define OVER 0

#define PLAYER 1

#define GAMESPEED 1000

#define DELAY 50


enum state   //麻将所处的位置
{
	duili = 1, //牌堆里面
	chizhong, //牌池中（打出去没人要的）
	shouli, //在自己手里
	zhuojiao //在桌角（碰、杠）
};

enum player //玩家的方位，也是牌的所属
{
	null,
	east,//东
	south,//南
	west,//西
	nouth//北
};

//====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====

#endif