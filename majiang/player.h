#ifndef __PLAYER_H__

#define __PLAYER_H__

#include"majiang.h"

class Player //�����
{
public:
	// Ĭ�Ϲ��캯��
	Player();
	//��ҹ��캯������ʼ�����ƺ�����
	Player(player p);

	//���÷���
	void setFanshu(int n);
	//���ú���״̬
	void setHupai(bool h);
	//��ú���״̬
	bool getHupai();
	//��÷���
	int getFanshu();
	//�����ҵķ���
	player getWanjia();
	//���ʵ����������
	int getPaiNum();
	//���ĳ���Ƶ�����
	int getPaiNum(Majiang m);
	int hasPaiNum(int n);
	//�����������ʹ�����,���ؿ��ŵ�����
	int getZJcols();
	//��ú���������ͬ����������
	int getZJcols(Majiang m);
	//�����������������
	int getTypeNum(int n);
	int getTypeNum();
	//���������������
	//�������
	Majiang* getShoupai();
	//���������
	const Majiang& getZhuopai(int i,int j);
	//��һ����
	Majiang throwPai(int n); 
	//ץ�ƣ�4�ţ�
	void addPai(Majiang* m,int lenth=4);
	//���ƣ�1�ţ�Ĭ������
	void addPai(Majiang m, bool li = !LIPAI_SWITCH);
	//�ѳ����Ʒŵ��Լ�ǰ����Ƴ�
	void addPaichi(Majiang m);
	//����Ƴ�
	const Majiang* getPaichi();
	//�����ƳصĿ�������
	int getPaichiNum();
	//�ƱȽ�
	static int mjCompare(const void* a, const void* b);
	//����
	void liPai();
	//������
	bool canPeng(Majiang m);
	//����
	bool pengPai(Majiang m);
	bool pengPai(Majiang m,bool peng);
	//�ܸ���
	int canGang(Majiang m);
	//�ܸ�����ʱ
	int* canGang_1();
	const Majiang* canGang_2();
	//���ƣ���ʱ
	bool gangPai_1(int *n,bool gang);
	bool gangPai_1(int *n);
	bool gangPai_2(const Majiang* m,bool gang);
	bool gangPai_2(const Majiang* m);
	//���ƴ����и�
	bool gangPai_Shou(Majiang m,bool gang);
	bool gangPai_Shou(Majiang m);
	//���ƴ����Ǹ�
	bool gangPai_Zhuo(Majiang m,bool gang);
	bool gangPai_Zhuo(Majiang m);
	//�ж��ܺ������ص��ѵ㣩
	bool canHu(Majiang m);
	bool canHu();
	//����
	bool huPai();
	bool huPai(bool x);
	bool huPai(Majiang n);
	bool huPai(Majiang n , bool x);
	//����������
	//void operator=(const Player &mj)
	//{
	//	*this = mj;

	//};

	int p_fanshu;  //�Ƶķ���
	Majiang zhuopai[MAJIANG_ZHUOJIAO_COLS][MAJIANG_ZHUOJIAO_ROWS]; //���ܵ���
private:
	player p_wanjia; //��ҵķ�λ
	bool hule = false;//�ж�����Ƿ����
	Majiang shoupai[MAX_MAJIANG_SHOU]; //�������
	Majiang paichi[MAX_MAJIANG_PAICHI];//��ǰ�Լ��������
};

#endif