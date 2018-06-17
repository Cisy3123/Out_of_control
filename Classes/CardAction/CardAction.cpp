#include"CardAction.h"
#include"Poker.h"
#include"Player.h"
#include<time.h> 
#include<stdlib.h>
#include<vector>
#include<algorithm>
USING_NS_CC;

CardAction::CardAction();
CardAction::~CardAction();

CardAction::CardAction()
{
}

CardAction::~CardAction()
{
}

bool CardAction::shuffle()//随机洗牌
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

void CardAction::deal()//发牌
{
	Poker* pk;
	if (m_iSendPk<51 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		if (m_iSendPk % 3 == 0)//给玩家1发牌
			MovePk(m_player1, pk);
		else if (m_iSendPk % 3 == 1)//给玩家2发牌
			MovePk(m_player2, pk);
		else if (m_iSendPk % 3 == 2)//给玩家3发牌
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

bool cmp(int a, int b)
{
	int i = (a / 13)<4 ? a % 13 : a - 39;
	int j = (b / 13)<4 ? b % 13 : b - 39;
	return a>b;
}

void CardAction::Sort(vector<int> &arr)//整理牌
{
	sort(arr.begin(), arr.end(), cmp);
}

//输入要判断的vector，返回牌型组合数据结构
CardGroupData CardAction::CardsType(vector<int> color_PutCard)
{
	int CardList[15] = { 0 };
	for (vector<int>::iterator iter = color_PutCard.begin(); iter != color_PutCard.end(); iter++)
	{
		int i = (*iter / 13) < 4 ? *iter % 13 : *iter - 39;
		CardList[i]++;
	}
	int nCount = 0;
	for (int i = 0; i < 15; i++)
	{
		nCount += CardList[i];
	}

	CardGroupData retCardGroupData;
	retCardGroupData.nCount = nCount;


	//单牌类型  
	if (nCount == 1)
	{
		//用于验证的变量  
		int prov = 0;
		for (int i = 0; i < 15; i++)
		{
			if (CardList[i] == 1)
			{
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cType = SINGLE_CARD;
			return retCardGroupData;
		}
	}
	//对牌类型  
	if (nCount == 2)
	{
		//用于验证的变量  
		int prov = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 2)
			{
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cType = DOUBLE_CARD;
			return retCardGroupData;
		}
	}
	//三不带 
	if (nCount == 3)
	{
		//用于验证的变量  
		int prov = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 3)
			{
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cType = THREE_CARD;
			return retCardGroupData;
		}
	}
	//三带一单  
	if (nCount == 4)
	{
		//用于验证的变量  
		int prov1 = 0;
		int prov2 = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 3)
			{
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (CardList[i] == 1)
			{
				prov2++;
			}

		}
		if (prov1 == 1 && prov2 == 1)
		{
			retCardGroupData.cType = THREE_ONE_CARD;
			return retCardGroupData;
		}
	}
	//三带一对  
	if (nCount == 5)
	{
		//用于验证的变量  
		int prov1 = 0;
		int prov2 = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 3)
			{
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (CardList[i] == 2)
			{
				prov2++;

			}
		}
		if (prov1 == 1 && prov2 == 1)
		{
			retCardGroupData.cType = THREE_TWO_CARD;
			return retCardGroupData;
		}
	}
	//四带两单  
	if (nCount == 6)
	{
		//用于验证的变量  
		int prov1 = 0;
		int prov2 = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 4)
			{
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (CardList[i] == 1)
			{
				prov2 += CardList[i];
			}
		}

		if (prov1 == 1 && prov2 == 2)
		{
			retCardGroupData.cType = BOMB_TWO_CARD;
			return retCardGroupData;
		}
	}
	//四带两对  
	if (nCount == 8)
	{
		//用于验证的变量  
		int prov1 = 0;
		int prov2 = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 4)
			{
				prov1++;
				retCardGroupData.nMaxCard = i;
			}
			if (CardList[i] == 2)
			{
				prov2 += CardList[i];

			}
		}
		if (prov1 == 1 && prov2 == 4)
		{
			retCardGroupData.cType = BOMB_TWO_CARD;
			return retCardGroupData;
		}
	}
	//炸弹类型-非王炸
	if (nCount == 4)
	{
		//用于验证的变量  
		int prov = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 4)
			{
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cType = BOMB_CARD;
			return retCardGroupData;
		}
	}
	//王炸类型  
	if (nCount == 2)
	{
		if (CardList[13] > 0 && CardList[14] > 0)
		{
			retCardGroupData.nMaxCard = 14;
			retCardGroupData.cType = KING_CARD;
			return retCardGroupData;
		}
	}
	//单连类型  
	if (nCount >= 5)
	{
		//用于验证的变量  
		int prov = 0;
		int i = 0;
		for (; i < 12; i++)
		{
			if (CardList[i] == 1)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}

		if (prov == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = CONNECT_CARD;
			return retCardGroupData;
		}
	}
	//对连类型  
	if (nCount >= 6)
	{
		//用于验证的变量  
		int prov = 0;
		int i;
		for (i = 0; i < 12; i++)
		{
			if (CardList[i] == 2)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}

		if (prov * 2 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = COMPANY_CARD;
			return retCardGroupData;
		}
	}
	//飞机不带  
	if (nCount >= 6)
	{
		//用于验证的变量  
		int prov = 0;

		int SumValue = 0;
		int i;
		for (i = 0; i < 12; i++)
		{
			if (CardList[i] == 3)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}

		if (prov * 3 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = AIRCRAFT_CARD;
			return retCardGroupData;
		}
	}
	//飞机带单牌 
	if (nCount >= 8)
	{
		//用于验证的变量  
		int prov1 = 0;
		int prov2 = 0;
		int i, j;
		for (i = 0; i < 12; i++)
		{
			if (CardList[i] == 3)
			{
				prov1++;
			}
			else
			{
				if (prov1 != 0)
				{
					break;
				}

			}
		}
		for (j = 0; j < 13; j++)
		{
			if (CardList[j] == 1)
			{
				prov2 += CardList[j];
			}
		}

		if (prov1 = prov2 && prov1 * 4 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = AIRCRAFT_SINGLE_CARD;
			return retCardGroupData;
		}

	}
	//飞机带对子类型  
	if (nCount >= 10)
	{
		//用于验证的变量  
		int prov1 = 0;
		int prov2 = 0;
		int i, j;
		for (i = 0; i < 12; i++)
		{
			if (CardList[i] == 3)
			{
				prov1++;
			}
			else
			{
				if (prov1 != 0)
				{
					break;
				}
			}
		}
		for (j = 0; j < 13; j++)
		{
			if (CardList[j] == 2)
			{
				prov2 += CardList[j] / 2;
			}
		}

		if (prov1 == prov2 && prov1 * 5 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = AIRCRAFT_DOUBLE_CARD;
			return retCardGroupData;
		}
	}

	retCardGroupData.cType = ERROR_CARD;
	return retCardGroupData;
}

void CardAction::changeNowCard()
{
	NowCardGroup.cType = PutCardType.cType;
	NowCardGroup.nCount = PutCardType.nCount;
	NowCardGroup.nMaxCard = PutCardType.nMaxCard;
}

void CardAction::ClearPutCard()//出牌后，清空原选中的牌
{
	color_PutCard.clear();
	PutCardType.cType = ERROR_CARD;
	PutCardType.nMaxCard = -1;
	PutCardType.nCount = 0;
}

void CardAction::Arrange()//整理现有手牌
{
	Sort(color_CardList);
	CardCount = color_CardList.size();
}

bool CardAction::find_Cards(CardGroupData temp)
{
	return false;
}

CardGroupData CardAction:: NowCardGroup()
{
	return NowCardGroup;
}