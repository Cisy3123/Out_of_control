#include<stddef.h>
#include<vector>
#include<algorithm>
#include"DataHand.h"

void CardData::ClearPutCard()
{
	color_PutCard.clear();
	value_PutCard.clear();
	PutCardType.cType = ERROR_CARD;
	PutCardType.nMaxCard = -1;
	return;
}
int cmp(int a, int b)
{
	return a > b ? 1 : 0;
}
void CardData::Sort(vector<int> &arr)
{
	sort(arr.begin(), arr.end(), cmp);
	return;
}

void CardData::get_valueCard()
{
	value_CardList.clear();                               //����
	memset(value_iCardList, 0, sizeof(value_iCardList));
	for (vector<int>::iterator iter = color_CardList.begin(); iter != color_CardList.end(); iter++)
	{
		value_CardList.push_back((*iter / 4) + 3);
		value_iCardList[(*iter / 4) + 3]++;
	}
}

void CardData::Init()
{
	get_valueCard();
	Sort(color_CardList);
	Sort(value_CardList);
	CardCount = value_CardList.size();
}

bool CardData::PutOneCard(int value_Card, int &color_Card)
{
	bool ret = false;
	value_iCardList[value_Card]--;//value״̬���鴦��
	if (value_iCardList[value_Card] < 0)
	{
		return false;
	}
	for (vector<int>::iterator iter = value_CardList.begin(); iter != value_CardList.end(); iter++)//value�б����鴦��
	{
		if (*iter == value_Card)
		{
			value_CardList.erase(iter);
			ret = true;
			break;
		}
	}
	for (vector<int>::iterator iter = color_CardList.begin(); iter != color_CardList.end(); iter++)//color�б����ݴ���
	{
		if (value_Card == 13 || value_Card == 14)
		{
			if (*iter == 39 + value_Card)
			{
				color_Card = *iter;
				color_CardList.erase(iter);
				return ret;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (*iter == 13 * i + value_Card)
			{
				color_Card = *iter;
				color_CardList.erase(iter);
				return ret;
			}
		}
	}
	return false;

}

bool CardData::PutCards()
{
	for (vector<int>::iterator iter = value_PutCard.begin(); iter != value_PutCard.end(); iter++)
	{
		int color_Card = -1;
		if (PutOneCard(*iter, color_Card))
		{
			color_PutCard.push_back(color_Card);
		}
		else
		{
			return false;
		}
	}
	CardCount -= value_PutCard.size();
	return true;
}
