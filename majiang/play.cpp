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
	m_index = m_index % MAX_MAJIANG_NUM;  //处理m_index,超出107后从0开始
	if (m_index == (MAX_MAJIANG_NUM - 2)){  //处理四张四张的抓牌到牌堆只剩下两张牌时候的溢出错误
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
	m_index = m_index % MAX_MAJIANG_NUM; //处理m_index,超出107后从0开始

	keypai = paidui.throwOneMajiang(m_index); //抓牌时改变keypai
	
	wanjia[p].addPai(keypai,li);
	m_index += 1;
	m_number -= 1;
}

void Play::chupai(player p,int n)
{
	keypai = wanjia[p].throwPai(n);  //出牌时改变keypai
}

void Play::chupai(player p)
{
	int n;
	n = chuPaiAI(p);
	keypai = wanjia[p].throwPai(n);  //出牌时改变keypai
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
	m_index = (shaizi + zhuangjia - 2) % 4 * 26 + shaizi * 2; //根据骰子点数和庄家方向算出该从哪抓牌

	return m_index;
}

void Play::go_FirstStep()
{
	int who = 0;
	for (int i = 0; i < 3; ++i){
		for (int j = 4; j > 0; --j){
			who = (zhuangjia - 1 + j) % 4 + 1;  //从庄家开始轮着抓牌，超过4的从1开始
			dividePai(player(who));
		}
	}

	
	for (int i = 4; i > 0; --i){   //最后一轮一人摸一张
		who = (zhuangjia - 1 + i) % 4 + 1;
		giveOnePai(player(who), true);
	}


}

void Play::show()
{
	HANDLE   hStdout;
	//   光标位置   
	COORD     cursorPos;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//  清屏
	system("cls");
	

	//   第5行输出   
	cursorPos.X = 0;
	cursorPos.Y = 5;
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << "东家的手牌：";
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		getPlayer(east).getShoupai()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "东家打出的牌：";
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i)
		getPlayer(east).getPaichi()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "东家的桌牌：";
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i){
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; ++j)
			getPlayer(east).getZhuopai(i,j).showOne();
	}
	cout << endl << "======================================================" << endl;

	cout << "南家的手牌：";
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		getPlayer(south).getShoupai()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "南家打出的牌：";
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i)
		getPlayer(south).getPaichi()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "南家的桌牌：";
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i){
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; ++j)
			getPlayer(south).getZhuopai(i,j).showOne();
	}
	cout << endl << "======================================================" << endl;

	cout << "西家的手牌：";
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		getPlayer(west).getShoupai()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "西家打出的牌：";
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i)
		getPlayer(west).getPaichi()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "西家的桌牌：";
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i){
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; ++j)
			getPlayer(west).getZhuopai(i,j).showOne();
	}
	cout << endl << "======================================================" << endl;

	cout << "北家的手牌：";
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		getPlayer(nouth).getShoupai()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "北家打出的牌：";
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i)
		getPlayer(nouth).getPaichi()[i].showOne();
	cout << endl << "------------------------------------------------------" << endl;
	cout << "北家的桌牌：";
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i){
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; ++j)
			getPlayer(nouth).getZhuopai(i,j).showOne();
	}
	cout << endl << "======================================================" << endl;

	cout << "牌堆剩余：" << getNumber() << endl;

	for (int i = 0; i < MAX_MAJIANG_NUM; ++i)
		getPaidui().getOne(i, 2);
	cout << endl << "下一张要抓：" << getIndex() << "麻将信息：";
}


void Play::go_SecondStep()
{

	int who;//临时储存who
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

				wanjia[current].getShoupai()[13].showOne(); cout << endl << current << "打牌";//xianshi

				if (wanjia[current].canHu())//自摸判断
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

						if (who && who != current && wanjia[who].huPai(keypai))//抢杠胡判断
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

			if (who && who !=current && wanjia[who].huPai(keypai))//吃胡判断
			{
				show();//=======================================================================
				
				current = who - 1 > 0 ? who - 1 : 4;
				
				zhua = true;
				continue;
				
			}

			who = whoCanPeng(keypai);

			if (who && who != current && wanjia[who].pengPai(keypai))//碰牌判断
			{
				show();//=======================================================================
				
				current = who;
				zhua = false;
				continue;
			}

			who = whoCanGang(keypai);

			if (who && who !=5 && who != current && wanjia[who].gangPai_Shou(keypai))//杠牌判断
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