#include"paidui.h"

Paidui::Paidui()
{
	int n = 0;
	for (int i = 0; i < 4; ++i){//类型循环
		for (int j = 0; j < 9; ++j){//数值循环
			for (int k = 0; k < 4; ++k){//数量循环
				if (n < MAX_MAJIANG_NUM){
					paidui[n] = Majiang((i + 1)*10+j + 1);
					++n;
				}
			}
		}
	}
}

void Paidui::xiPai()
{

	int n = MAX_MAJIANG_NUM;
	Majiang tempArray[MAX_MAJIANG_NUM];
	for (int i = 0; i < n; i++)
		tempArray[i] = paidui[i];

	for (int i = 0; i < n; i++)
		paidui[MyArray::randomIndex(n)[i]] = tempArray[i];

}

void Paidui::getOne(int n, int m)
{
	if (m == 2)
		cout << paidui[n].getTypeValue();
}

Majiang Paidui::getOne(int n)
{
	return paidui[n];
}

Majiang* Paidui::getAll()
{
	return paidui;
}

int Paidui::showMargin()
{
	int margin = 0;
	for (int i = 0; i < MAX_MAJIANG_NUM; ++i)
	if (paidui[i].getTypeValue() != EMPTY)
		margin++;
		
	return margin;
}

int Paidui::getMargin()
{
	return m_margin;
}

void Paidui::setShaizi()
{
	srand(unsigned(time(NULL)));
	shaizi = rand() % 6 + 1;
}

void Paidui::setShaizi(int n)
{
	shaizi = n;
}

int Paidui::getShaizi()
{
	return shaizi;
}

Majiang Paidui::throwOneMajiang(int n)
{
	Majiang out;
	out = paidui[n];
	paidui[n].setTypeValue(EMPTY);
	--m_margin;

	return out;
}

Majiang* Paidui::throwMajiang(int n)
{
	Majiang *out = new Majiang[4];
	for (int i = 0; i < 4; i++)
	{
		out[i] = paidui[n + i];
		paidui[n + i].setTypeValue(EMPTY);
		--m_margin;
	}

	return out;
}