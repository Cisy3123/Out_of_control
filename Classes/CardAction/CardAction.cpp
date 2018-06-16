#include"CardAction.h"
#include"Poker.h"
#include"Player.h"
#include<time.h> 
#include<stdlib.h>
#include<vector>
USING_NS_CC;

CardAction::CardAction();
CardAction::~CardAction();
bool CardAction::shuffle()//���ϴ��
{
	bool isRet = false;
	do
	{
		for (int i = 0; i<54; ++i)
		{
			Poker* pk1 = (Poker*)m_arrPokers->randomObject();
			Poker* pk2 = (Poker*)m_arrPokers->randomObject();
			m_arrPokers->exchangeObject(pk1, pk2);
		}
		isRet = true;
	} while (0);
	return isRet;
};
void CardAction::deal()//����
{
	Poker* pk;
	if (m_iSendPk<51 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		if (m_iSendPk % 3 == 0)//�����1����
			MovePk(m_player1, pk);
		else if (m_iSendPk % 3 == 1)//�����2����
			MovePk(m_player2, pk);
		else if (m_iSendPk % 3 == 2)//�����3����
			MovePk(m_player3, pk);
		++m_iSendPk;
		m_isSend = false;
	}
	else if (m_iSendPk>50 && m_iSendPk<54 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		pk->showFront();
		MovePk(m_Three, pk);
		++m_iSendPk;
		m_isSend = false;
	}
	else if (m_iSendPk>53)
	{
		FenChaiNpcPai(m_npcOne);
		FenChaiNpcPai(m_npcTwo);
		m_iSendPk = 0;
		m_iState = 1;
	}
}
void CardAction::sort()//������
{

};
bool aircraft()//�Ƿ�ɻ�
{

}

bool pair()//�Ƿ����
{

}

bool pairs()//�Ƿ�����
{

}

bool straight()//�Ƿ�˳��
{

}
bool bomb()//�Ƿ�ը��
{

}