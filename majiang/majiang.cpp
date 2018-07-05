#include"majiang.h"
#include <time.h>

using namespace std;

Majiang::Majiang()
{
	m_typevalue = EMPTY;
	m_visibility = false;
	m_state = duili;
	m_player = null;
}

Majiang::Majiang(int tv)
{
	{
		if (tv < 11 || tv > EMPTY)
		cout << "majiang's value is wrong , it should between 1-9!";
		else{
			m_typevalue = tv;
			m_visibility = false;
			m_state = duili;
			m_player = null;
		}
	}
}

Majiang::Majiang(player p)
{
	m_typevalue = EMPTY;
	m_visibility = true;
	m_state = shouli;
	m_player = p;

}

Majiang::Majiang(player p,state s)
{
	m_typevalue = EMPTY;
	m_visibility = true;
	m_state = s;
	m_player = p;
}


int Majiang::getTypeValue() const
{
	return m_typevalue;
}

bool Majiang::getVisibility()
{
	return m_visibility;
}

state Majiang::getState()
{
	return m_state;
}

player Majiang::getPlayer()
{
	return m_player;
}

void Majiang::setTypeValue(int tv)
{
	m_typevalue = tv;
}

void Majiang::setVisibility(bool v)
{
	m_visibility = v;
}

void Majiang::setState(state s)
{
	m_state = s;
}

void Majiang::setPlayer(player p)
{
	m_player = p;
}

void Majiang::mjVTcopy(Majiang m)
{
	m_typevalue = m.m_typevalue;
}

bool Majiang::mjVTequal(Majiang m)
{
	if (m_typevalue == m.m_typevalue)
		return true;
	else
		return false;
}

void Majiang::showOne() const
{
	
	if (m_typevalue != 40){
		cout << m_typevalue << " ";
	}
		

}