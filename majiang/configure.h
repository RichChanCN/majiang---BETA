#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#define MAX_MAJIANG_NUM 108 //�Ĵ��齫���齫�������
#define MAX_MAJIANG_SHOU 14 //�齫��������������
#define MAJIANG_ZHUOJIAO_COLS 4//���ǵ����������
#define MAJIANG_ZHUOJIAO_ROWS 4//���ǵ����������
#define MAX_FANSHU 8 //�Ƶ������
#define MAX_MAJIANG_PAICHI 27 //ÿ��������Ƶ��������  �����������27
#define LIPAI_SWITCH true //ÿ���Ʋ�����ϴ�ƵĿ���
#define EMPTY 40 //���Ƶ���ֵ
#define MAJIANG_MOSHI 3  //ʣ�¶�����û���ͽ��� 1����Ѫս
#define ZHUO_SHOU 5  //�������Ʒ���ֵ

#define ZHUO_SHOU_DELAY 6 //�����ӳٸ���
#define SHOU_DELAY 7 //������ʱ����


#define RESIZE_RATE 10 //�������ű���
#define MAX_CHAR 128

#define MAJIANG_AI true//AI����

#define DONOT -1//ʲô������
#define ZHUAPAI 1//ץ��
#define CHUPAI 2//����
#define PENGPAI 3//����
#define GANGPAI 4//����
#define HUPAI 5//����
#define JIANCE 6//���
#define CANHU 7//�ܺ�
#define CANPENG 8//����
#define CANGANG 9//�ܸ�

#define RUNNING 1
#define OVER 0

#define PLAYER 1

#define GAMESPEED 1000

#define DELAY 50


enum state   //�齫������λ��
{
	duili = 1, //�ƶ�����
	chizhong, //�Ƴ��У����ȥû��Ҫ�ģ�
	shouli, //���Լ�����
	zhuojiao //�����ǣ������ܣ�
};

enum player //��ҵķ�λ��Ҳ���Ƶ�����
{
	null,
	east,//��
	south,//��
	west,//��
	nouth//��
};

//====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====OpenGL====

#endif