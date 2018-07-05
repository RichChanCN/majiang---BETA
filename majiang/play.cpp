#include"play.h"

Play::Play()
{
	wanjia[1] = Player(east);
	wanjia[2] = Player(south);
	wanjia[3] = Player(west);
	wanjia[4] = Player(nouth);
}


void Play::setZhuangjia(player p)
{
	if (p == null){
		srand(unsigned(time(NULL)));
		zhuangjia = player(rand() % 4 + 1);
	}
	else
		zhuangjia = p;		
}

player Play::getZhuangjia()
{
	return zhuangjia;
}

Player Play::getPlayer(player p)
{
	return wanjia[p];
}

Paidui Play::getPaidui()
{
	return paidui;
}

int Play::getIndex()
{
	return m_index;
}

int Play::getNumber()
{
	return m_number;
}

int Play::getHuplayernum()
{
	int num = 0;
	for (int i = 1; i < 5;++i)
	if (wanjia[i].getHupai() == false)
		num++;

	return num;
}

void Play::dividePai(player p)
{
	m_index = m_index % MAX_MAJIANG_NUM;  //����m_index,����107���0��ʼ
	if (m_index == (MAX_MAJIANG_NUM - 2)){  //�����������ŵ�ץ�Ƶ��ƶ�ֻʣ��������ʱ����������
		for (int i = 0; i < 4; ++i)
			giveOnePai(p);
	}
	else{
		wanjia[p].addPai(paidui.throwMajiang(m_index));
		m_index += 4;
		m_number -= 4;
	}


}

void Play::giveOnePai(player p, bool li)
{
	m_index = m_index % MAX_MAJIANG_NUM; //����m_index,����107���0��ʼ

	keypai = paidui.throwOneMajiang(m_index); //ץ��ʱ�ı�keypai
	
	wanjia[p].addPai(keypai,li);
	m_index += 1;
	m_number -= 1;
}

void Play::chupai(player p,int n)
{
	keypai = wanjia[p].throwPai(n);  //����ʱ�ı�keypai
}

void Play::chupai(player p)
{
	int n;
	n = chuPaiAI(p);
	keypai = wanjia[p].throwPai(n);  //����ʱ�ı�keypai
}

int Play::whoCanHu(Majiang m)
{
	for (int i = 1; i <= 5; ++i){
		if (wanjia[i].canHu(m))
			return i;
	}
	return 0;
}


int Play::whoCanPeng(Majiang m)
{

	for (int i = 1; i <= 5; ++i){
		if (wanjia[i].canPeng(m))
			return i;
	}

	return 0;
}


int Play::whoCanGang(Majiang m)
{
	int temp;
	for (int i = 1; i <= 5; ++i){
		temp = wanjia[i].canGang(m);
		if (temp){
				return i;
		}
	}

	return 0;
}

int Play::readyToGo(player p)
{
	int i = 1;
	setZhuangjia(p);
	//paidui.xiPai();
	paidui.setShaizi();
	int shaizi = paidui.getShaizi();
	m_index = (shaizi + zhuangjia - 2) % 4 * 26 + shaizi * 2; //�������ӵ�����ׯ�ҷ�������ô���ץ��

	return m_index;
}

void Play::go_FirstStep()
{
	int who = 0;
	for (int i = 0; i < 3; ++i){
		for (int j = 4; j > 0; --j){
			who = (zhuangjia - 1 + j) % 4 + 1;  //��ׯ�ҿ�ʼ����ץ�ƣ�����4�Ĵ�1��ʼ
			dividePai(player(who));
		}
	}

	
	for (int i = 4; i > 0; --i){   //���һ��һ����һ��
		who = (zhuangjia - 1 + i) % 4 + 1;
		giveOnePai(player(who), true);
	}


}

void Play::show()
{
	HANDLE   hStdout;
	//   ���λ��   
	COORD     cursorPos;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//  ����
	system("cls");
	

	//   ��5�����   
	cursorPos.X = 0;
	cursorPos.Y = 5;
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << "���ҵ����ƣ�";
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		getPlayer(east).getShoupai()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "���Ҵ�����ƣ�";
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i)
		getPlayer(east).getPaichi()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "���ҵ����ƣ�";
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i){
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; ++j)
			getPlayer(east).getZhuopai(i,j).showOne();
	}
	cout << endl << "======================================================" << endl;

	cout << "�ϼҵ����ƣ�";
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		getPlayer(south).getShoupai()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "�ϼҴ�����ƣ�";
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i)
		getPlayer(south).getPaichi()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "�ϼҵ����ƣ�";
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i){
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; ++j)
			getPlayer(south).getZhuopai(i,j).showOne();
	}
	cout << endl << "======================================================" << endl;

	cout << "���ҵ����ƣ�";
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		getPlayer(west).getShoupai()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "���Ҵ�����ƣ�";
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i)
		getPlayer(west).getPaichi()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "���ҵ����ƣ�";
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i){
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; ++j)
			getPlayer(west).getZhuopai(i,j).showOne();
	}
	cout << endl << "======================================================" << endl;

	cout << "���ҵ����ƣ�";
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		getPlayer(nouth).getShoupai()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "���Ҵ�����ƣ�";
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i)
		getPlayer(nouth).getPaichi()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "���ҵ����ƣ�";
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i){
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; ++j)
			getPlayer(nouth).getZhuopai(i,j).showOne();
	}
	cout << endl << "======================================================" << endl;

	cout << "�ƶ�ʣ�ࣺ" << getNumber() << endl;

	for (int i = 0; i < MAX_MAJIANG_NUM; ++i)
		getPaidui().getOne(i, 2);
	cout << endl << "��һ��Ҫץ��" << getIndex() << "�齫��Ϣ��";
}


void Play::go_SecondStep()
{

	int who;//��ʱ����who
	int current = zhuangjia;
	bool zhua = true;

	while (getHuplayernum() > MAJIANG_MOSHI)
	{
		while (!wanjia[current].getHupai())
		{
			if (zhua)
			{
				giveOnePai(player(current));

				show();//=======================================================================

				wanjia[current].getShoupai()[13].showOne(); cout << endl << current << "����";//xianshi

				if (wanjia[current].canHu())//�����ж�
				{
					if (wanjia[current].huPai())
					{
						current = current - 1 > 0 ? current - 1 : 4;
						zhua = true;
						continue;
					}


				}


				if (wanjia[current].gangPai_1(wanjia[current].canGang_1()))
				{
					show();//=======================================================================

					if (who > 4)
					{
						who = whoCanHu(keypai);

						if (who && who != current && wanjia[who].huPai(keypai))//���ܺ��ж�
						{
							current = who - 1 > 0 ? who - 1 : 4;
							zhua = true;
							continue;
						}
						else {
							zhua = true;
							continue;
						}
					}
					else{
						zhua = true;
						continue;
					}
				
				}

				if (wanjia[current].gangPai_2(wanjia[current].canGang_2()))
				{
					zhua = true;
					continue;
				}
				
			}
			
			chupai(player(current));

			who = whoCanHu(keypai);

			if (who && who !=current && wanjia[who].huPai(keypai))//�Ժ��ж�
			{
				show();//=======================================================================
				
				current = who - 1 > 0 ? who - 1 : 4;
				
				zhua = true;
				continue;
				
			}

			who = whoCanPeng(keypai);

			if (who && who != current && wanjia[who].pengPai(keypai))//�����ж�
			{
				show();//=======================================================================
				
				current = who;
				zhua = false;
				continue;
			}

			who = whoCanGang(keypai);

			if (who && who !=5 && who != current && wanjia[who].gangPai_Shou(keypai))//�����ж�
			{
				show();//=======================================================================

				current = who;
				zhua = true;
				continue;
			}

			wanjia[current].addPaichi(keypai);

			zhua = true;
			current = current - 1 > 0 ? current - 1 : 4;
			
			break;
		}
		
		show();//=======================================================================
	}

}

int Play::chuPaiAI(player n)
{
	int index = 0;
	int temp;
	int weight;
	int min_weight = 30;
	int shoupainum = wanjia[n].getPaiNum();
	for (int i = 0; i <shoupainum ; i++)
	{
		weight = 0;
		temp = wanjia[n].getShoupai()[i].getTypeValue();
		weight = wanjia[n].hasPaiNum(temp) * 10 + (bool)wanjia[n].hasPaiNum(temp - 1) * 10 + (bool)wanjia[n].hasPaiNum(temp + 1) * 10;
		if (min_weight > weight)
		{
			min_weight = weight;
			index = i;
		}
	}

	return index;
}