#pragma once
#include<iostream>
#include<vector>
#include"CardSet.h"
#include"CardAction.h"
#include"Player.h"

using namespace std;
Player::Player() {}
Player::~Player(){}
void Player::call()//�е���
{

}


//����Ҫ�жϵ�vector����������������ݽṹ
CardGroupData Player:: CardsType(vector<int> color_PutCard)
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


	//��������  
	if (nCount == 1)
	{
		//������֤�ı���  
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
	//��������  
	if (nCount == 2)
	{
		//������֤�ı���  
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
	//������ 
	if (nCount == 3)
	{
		//������֤�ı���  
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
	//����һ��  
	if (nCount == 4)
	{
		//������֤�ı���  
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
	//����һ��  
	if (nCount == 5)
	{
		//������֤�ı���  
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
	//�Ĵ�����  
	if (nCount == 6)
	{
		//������֤�ı���  
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
	//�Ĵ�����  
	if (nCount == 8)
	{
		//������֤�ı���  
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
	//ը������-����ը
	if (nCount == 4)
	{
		//������֤�ı���  
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
	//��ը����  
	if (nCount == 2)
	{
		if (CardList[13] > 0 && CardList[14] > 0)
		{
			retCardGroupData.nMaxCard = 14;
			retCardGroupData.cType = KING_CARD;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount >= 5)
	{
		//������֤�ı���  
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
	//��������  
	if (nCount >= 6)
	{
		//������֤�ı���  
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
	//�ɻ�����  
	if (nCount >= 6)
	{
		//������֤�ı���  
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
	//�ɻ������� 
	if (nCount >= 8)
	{
		//������֤�ı���  
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
	//�ɻ�����������  
	if (nCount >= 10)
	{
		//������֤�ı���  
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