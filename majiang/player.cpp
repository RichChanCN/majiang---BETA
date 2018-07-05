#include"player.h"

Player::Player()
{
	p_fanshu = 0;
	p_wanjia = null;
}

Player::Player(player p){
	p_fanshu = 1;
	p_wanjia = p;
	for (int i = 0; i < MAX_MAJIANG_SHOU; i++)
		shoupai[i] = Majiang(p);

	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; i++)
		for (int j = 0; j < MAJIANG_ZHUOJIAO_ROWS; j++)
			zhuopai[i][j] = Majiang(p, zhuojiao);

	for (int i = 0; i < MAX_MAJIANG_PAICHI; i++)
		paichi[i] = Majiang(p, chizhong);
}

void Player::setFanshu(int f)
{
	p_fanshu = f;
}

void Player::setHupai(bool h)
{
	hule = h;
}

bool Player::getHupai()
{
	return hule;
}

int Player::getFanshu()
{
	return p_fanshu;
}

player Player::getWanjia()
{
	return p_wanjia;
}

int Player::getPaiNum()
{
	int num = 0;
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i){
		if (shoupai[i].getTypeValue()!=EMPTY)
			num++;
	}
	
	return num;
}

int Player::getPaiNum(Majiang n)
{
	int num = 0;
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
	{
		if (n.getTypeValue() != EMPTY && shoupai[i].mjVTequal(n))
			num++;
	}

	return num;
}

int Player::hasPaiNum(int m)
{
	int num = 0;
	for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
	{
		if (shoupai[i].getTypeValue() == m)
			num++;
	}

	return num;
}

int Player::getTypeNum(int n)
{
	int painum = getPaiNum();
	int num = 0;
	
	for (int i = 0; i < painum; ++i){
		if (shoupai[i].getTypeValue() / (n * 10) == 1)
			num++;
	}


	return num;
}

int Player::getTypeNum()
{
	int painum = getPaiNum();
	int num = 0;
	int type = 0;
	if (shoupai[0].getTypeValue() / 10 == 1)
		type += 1;
	if (shoupai[painum - 1].getTypeValue() / 30 == 1)
		type += 1;
	for (int i = 0; i < painum; ++i){
		if (shoupai[i].getTypeValue() / 20 == 1);
		num++;
	}
	if (num != 0)
		type += 1;


	return type;
}


Majiang* Player::getShoupai()
{
	return shoupai;
}

int Player::getZJcols()
{
	int num = 0;
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS;++i)
	if (zhuopai[i][0].getTypeValue() != EMPTY)
		++num;

	return num;
}

int Player::getZJcols(Majiang m)
{
	int num = 0;
	for (int i = 0; i < MAJIANG_ZHUOJIAO_COLS; ++i)
	if (zhuopai[i][0].mjVTequal(m))
		num=i;

	return num;
}


const Majiang& Player::getZhuopai(int i, int j)
{
	return zhuopai[i][j];
}

Majiang Player::throwPai(int n)
{
	while (n<0 || n>13 || shoupai[n].getTypeValue() == EMPTY) //如果错误选值那就重选
		cin >> n;   

	Majiang out = shoupai[n];

	shoupai[n].setTypeValue(EMPTY);

	if (LIPAI_SWITCH)
		liPai();

	return out;
}

void Player::addPai(Majiang* m,int n)
{
	int index = getPaiNum();
	for (int i = 0; i < 4; i++){
		shoupai[index + i].mjVTcopy(m[i]);
	}
	
	if (LIPAI_SWITCH)
		liPai();

	delete[] m;
}

void Player::addPai(Majiang m, bool li)
{
	if (m.getTypeValue() != EMPTY)
		shoupai[getPaiNum()].mjVTcopy(m);
	else 
		cout << "抓的牌不是有效的！";

	if (li)
		liPai();
}


void Player::addPaichi(Majiang m)
{
	if (m.getTypeValue() != EMPTY)
		paichi[getPaichiNum()].mjVTcopy(m);
	else
		;

}

const Majiang* Player::getPaichi()
{
	return paichi;
}

int Player::getPaichiNum()
{
	int num = 0;
	for (int i = 0; i < MAX_MAJIANG_PAICHI; ++i){
		if (paichi[i].getTypeValue() != EMPTY)
			num++;
	}

	return num;
}

int Player::mjCompare(const void *a, const void *b)
{
	Majiang* pa, *pb;
	pa = (Majiang*)a;
	pb = (Majiang*)b;

	return pa->getTypeValue() - pb->getTypeValue();

}


void Player::liPai()
{
	try{
		qsort(shoupai, MAX_MAJIANG_SHOU, sizeof(Majiang), mjCompare);//comp函数如果在类内那么要声明为静态
	}
	catch (...){
		cout << "理牌失败！" << endl;
	}
}

//碰牌专区===========================================================================================碰牌专区

bool Player::canPeng(Majiang m)
{
	if (m.getTypeValue() == EMPTY)
		return false;

	if (getWanjia() == 0){
		return false;
	}

	if (getPaiNum(m) > 1)
		return true;
	
	return false;
}

bool Player::pengPai(Majiang m,bool peng)
{
	if (getWanjia() == 0)
		return false;

	if (peng){
		int n = 0;
		int index = this->getZJcols();
		for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		{
			if (shoupai[i].mjVTequal(m) && n < 2)
			{
				shoupai[i].setTypeValue(EMPTY);
				n++;
			}
		}

		for (int i = 0; i < 3; ++i)
		{
			zhuopai[index][i].mjVTcopy(m);
		}

		if (LIPAI_SWITCH)
			liPai();

		return true;
	}
	else
		return false;
}

bool Player::pengPai(Majiang m)
{
	if (getWanjia() == 0)
		return false;

	bool peng;

	if (MAJIANG_AI)
	{
		peng = true;
	}
	else
	{
		cout << getWanjia() << "peng？";
		cin >> peng;
	}

	if (peng){
		int n = 0;
		int index = this->getZJcols();
		for (int i = 0; i < MAX_MAJIANG_SHOU; ++i)
		{
			if (shoupai[i].mjVTequal(m) && n < 2)
			{
				shoupai[i].setTypeValue(EMPTY);
				n++;
			}
		}

		for (int i = 0; i < 3; ++i)
		{
			zhuopai[index][i].mjVTcopy(m);
		}

		if (LIPAI_SWITCH)
			liPai();

		return true;
	}
	else
		return false;
}

//杠牌专区===========================================================================================杠牌专区

int Player::canGang(Majiang m)
{
	if (m.getTypeValue() == EMPTY)
		return false;


	if (getWanjia() == 0){   //没有人可以杠
		return false;
	}

	if (getPaiNum(m) == 3)  //全在手里可以杠
		return true;
	
	return false;

}

int* Player::canGang_1()
{
	Majiang temp;

	int *out = new int[4];
	for (int i = 0; i < 4;++i)
	{
		out[i] = 0;
	}

	int n = 0;

	for (int i = 0; i < 4; ++i)
	{  //手中，桌上，延迟杠牌
		temp = zhuopai[i][0];
		if (temp.getTypeValue() != EMPTY && hasPaiNum(temp.getTypeValue()))
		{
			out[n] = i;
			n++;
		}
	}

	return out;

}

const Majiang* Player::canGang_2()
{
	Majiang temp;
	Majiang *out = new Majiang[3];
	int n = 0;
	for (int i = 0; i < getPaiNum(); i++)
	{
		temp = shoupai[i];
		if (temp.getTypeValue() != EMPTY
			&& getPaiNum(temp) == 4
			&& n < 3
			&& temp.getTypeValue() != out[0].getTypeValue()
			&& temp.getTypeValue() != out[1].getTypeValue()
			&& temp.getTypeValue() != out[2].getTypeValue()
			&& temp.getTypeValue() != out[3].getTypeValue())
		{
			out[n] = temp;
			++n;

		}
	}

	return out;
}

bool Player::gangPai_1(int *m)
{
	if (m[0] + m[1] + m[2] + m[3] == 0)
		return false;

	bool gang;

	if (MAJIANG_AI)
	{
		gang = true;
	}
	else
	{
		cout << getWanjia() << "杠？";
		cin >> gang;
	}

	if (gang){

		int n = 0;

		while (n < 4)
		{
			if (m[n] == 0)
				continue;

			cout << getWanjia() << "杠" << zhuopai[m[n]][0].getTypeValue() << "?";
			cin >> gang;
			if (gang){
				p_fanshu = p_fanshu * 2;

				Majiang temp = zhuopai[m[n]][0];

				zhuopai[m[n]][3].mjVTcopy(temp);

				for (int i = 0; i < getPaiNum(); ++i)
				{
					if (shoupai[i].mjVTequal(temp)){
						shoupai[i].setTypeValue(EMPTY);
					}
				}

				delete[]m;

				return true;
			}

			n++;
		}

	}

	return false;
}

bool Player::gangPai_1(int *m, bool gang)
{
	if (m[0] + m[1] + m[2] + m[3] == 0)
		return false;

	if (gang){

		int n = 0;

		while (n < 4)
		{
			if (m[n] == 0)
				continue;

			cout << getWanjia() << "杠" << zhuopai[m[n]][0].getTypeValue() << "?";
			cin >> gang;
			if (gang){
				p_fanshu = p_fanshu * 2;

				Majiang temp = zhuopai[m[n]][0];

				zhuopai[m[n]][3].mjVTcopy(temp);

				for (int i = 0; i < getPaiNum(); ++i)
				{
					if (shoupai[i].mjVTequal(temp)){
						shoupai[i].setTypeValue(EMPTY);
					}
				}

				delete[]m;

				return true;
			}

			n++;
		}

	}

	return false;
}

bool Player::gangPai_2(const Majiang * m)
{
	if (m[0].getTypeValue() == EMPTY && m[1].getTypeValue() == EMPTY && m[2].getTypeValue() == EMPTY)
		return false;

	bool gang;
	if (MAJIANG_AI)
	{
		gang = true;
	}
	else
	{
		cout << getWanjia() << "杠？";
		cin >> gang;
	}

	if (gang){

		int n = 0;

		while (n < 3)
		{
			if (m[n].getTypeValue() == EMPTY)
				continue;

			cout << getWanjia() << "杠" << m[n].getTypeValue() << "?";
			cin >> gang;
			if (gang){
				p_fanshu = p_fanshu * 2;

				int index = getZJcols();
				int num = 0;
				for (int i = 0; i < MAX_MAJIANG_SHOU; ++i){
					if (shoupai[i].mjVTequal(m[n]) && num < 4){
						shoupai[i].setTypeValue(EMPTY);
						num++;
					}
				}

				for (int i = 0; i < 4; ++i){
					zhuopai[index][i].mjVTcopy(m[n]);
				}

				if (LIPAI_SWITCH)
					liPai();

				delete[]m;

				return true;
			}

			n++;
		}
		
	}


	return false;
}

bool Player::gangPai_2(const Majiang * m,bool gang)
{
	if (m[0].getTypeValue() == EMPTY && m[1].getTypeValue() == EMPTY && m[2].getTypeValue() == EMPTY)
		return false;

	if (gang){

		int n = 0;

		while (n < 3)
		{
			if (m[n].getTypeValue() == EMPTY)
				continue;

			cout << getWanjia() << "杠" << m[n].getTypeValue() << "?";
			cin >> gang;
			if (gang){
				p_fanshu = p_fanshu * 2;

				int index = getZJcols();
				int num = 0;
				for (int i = 0; i < MAX_MAJIANG_SHOU; ++i){
					if (shoupai[i].mjVTequal(m[n]) && num < 4){
						shoupai[i].setTypeValue(EMPTY);
						num++;
					}
				}

				for (int i = 0; i < 4; ++i){
					zhuopai[index][i].mjVTcopy(m[n]);
				}

				if (LIPAI_SWITCH)
					liPai();

				delete[]m;

				return true;
			}

			n++;
		}

	}


	return false;
}

bool Player::gangPai_Shou(Majiang m)
{
	if (getWanjia() == 0)
		return false;

	bool gang;

	if (MAJIANG_AI)
	{
		gang = true;
	}
	else
	{
		cout << getWanjia() << "杠？";
		cin >> gang;
	}

	if (gang)
	{
		int n = 0;
		p_fanshu = p_fanshu * 2;
		int index = this->getZJcols();
		for (int i = 0; i < MAX_MAJIANG_SHOU; ++i){
			if (shoupai[i].mjVTequal(m) && n < 3){
				shoupai[i].setTypeValue(EMPTY);
				n++;
			}
		}

		for (int i = 0; i < 4; ++i){
			zhuopai[index][i].mjVTcopy(m);
		}

		if (LIPAI_SWITCH)
			liPai();

		return true;
	}
	
	
	return false;
}

bool Player::gangPai_Shou(Majiang m, bool gang)
{
	if (getWanjia() == 0)
		return false;

	if (gang)
	{
		int n = 0;
		p_fanshu = p_fanshu * 2;
		int index = this->getZJcols();
		for (int i = 0; i < MAX_MAJIANG_SHOU; ++i){
			if (shoupai[i].mjVTequal(m) && n < 3){
				shoupai[i].setTypeValue(EMPTY);
				n++;
			}
		}

		for (int i = 0; i < 4; ++i){
			zhuopai[index][i].mjVTcopy(m);
		}

		if (LIPAI_SWITCH)
			liPai();

		return true;
	}


	return false;
}

bool Player::gangPai_Zhuo(Majiang m)
{
	if (getWanjia() == 0)
		return false;

	bool gang;
	if (MAJIANG_AI)
	{
		gang = true;
	}
	else
	{
		cout << getWanjia() << "杠？";
		cin >> gang;
	}
	

	if (gang){
		p_fanshu = p_fanshu * 2;
		int index = getZJcols(m);
		zhuopai[index][3].mjVTcopy(m);

		shoupai[getPaiNum()].setTypeValue(EMPTY);  //不是很好

		//for (int i = 0; i < getPaiNum(); ++i)
		//{
		//	if (shoupai[i].mjVTequal(m)){
		//		shoupai[i].setTypeValue(EMPTY);
		//	}
		//}

		return true;
	}
	

	return false;
}

//胡牌专区===========================================================================================胡牌专区

bool Player::canHu(Majiang m)
{
	addPai(m);
	int painum = getPaiNum();
	int temp;
	int keytype = 0;

	bool flag = false;
	if (painum == 2){
		if (getPaiNum(shoupai[0]) == 2)
		{
			throwPai(painum - 1);
			return true;
		}
			
		else
		{
			throwPai(painum - 1);
			return false;
		}
			
	}

	for (int i = 1; i < 4; ++i)
	{
		temp = getTypeNum(i);
		if (temp % 3 == 2)
		{
			flag = true;
			keytype = i;
		}
		else if (temp % 3 == 0)
			flag = true;
		else
			flag = false;
	}

	if (flag = true && keytype != 0)
	{
		vector<int> duizi;
		vector<int> result;

		int *a = new int[painum];
		for (int i = 0; i < painum; i++)
		{
			a[i] = shoupai[i].getTypeValue();
		}
		sort(a, a + painum);

		MyArray::repeatElement(a, painum, keytype, duizi);
		for (int i = 0; i < duizi.size(); i++)
		{
			MyArray::removeELement(a, painum, duizi[i], 2, result);
			if (MyArray::judge(result))
			{
				delete[]a;
				throwPai(painum-1);
				return true;
			}
		}

		delete[]a;
	}

	if (painum == 14){
		vector<int> qidui;
		for (int i = 0; i < painum; i++)
		{
			qidui.push_back(shoupai[i].getTypeValue());
		}
		sort(qidui.begin(), qidui.end());
		vector<int> redundancy(unique(qidui.begin(), qidui.end()), qidui.end());
		redundancy.erase(unique(redundancy.begin(), redundancy.end()), redundancy.end());

		if (redundancy.size() == 7)
		{
			throwPai(painum - 1);
			return true;
		}

	}

	throwPai(painum - 1);
	return false;
}

bool Player::canHu()
{
	int painum = getPaiNum();
	int temp;
	int keytype = 0;

	bool flag = false;
	if (painum == 2){
		if (getPaiNum(shoupai[0]) == 2)
			return true;
		else
			return false;
	}

	for (int i = 1; i < 4; ++i)
	{
		temp = getTypeNum(i);
		if (temp % 3 == 2)
		{
			flag = true;
			keytype = i;
		}
		else if (temp % 3 == 0)
			flag = true;
		else
			flag = false;
	}

	if (flag = true && keytype != 0)
	{
		vector<int> duizi;
		vector<int> result;

		int *a = new int[painum];
		for (int i = 0; i < painum; i++)
		{
			a[i] = shoupai[i].getTypeValue();
		}
		sort(a, a+painum);
		
		MyArray::repeatElement(a, painum, keytype, duizi);
		for (int i = 0; i < duizi.size(); i++)
		{
			MyArray::removeELement(a, painum, duizi[i], 2, result);
			if (MyArray::judge(result))
			{
				delete[]a;
				return true;
			}
		}

		delete[]a;
	}

	if (painum == 14)
	{
		vector<int> qidui;
		for (int i = 0; i < 14; i++)
		{
			qidui.push_back(shoupai[i].getTypeValue());
		}
		sort(qidui.begin(), qidui.end());
		for (int j = 0; j < 14; j = j + 2)
		{
			if (qidui[j] != qidui[j + 1])
				return false;
		}
		return true;
	}
	
	

	return false;
}

bool Player::huPai(bool x)
{
	if (x){
		hule = true;
		return true;
	}
	else
		return false;
}
bool Player::huPai()
{
	if (MAJIANG_AI){
		hule = true;
		return true;
	}
	else
		
		return false;
}

bool Player::huPai(Majiang m,bool x)
{
	if (x){
		addPai(m);
		hule = true;
		return true;
	}
	else
		return false;
}

bool Player::huPai(Majiang m)
{
	if (MAJIANG_AI){
		addPai(m);
		hule = true;
		return true;
	}
	else
		return false;
}