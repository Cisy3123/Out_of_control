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

void CardData::get_valueCard()
{
	value_CardList.clear();                               //清零
	memset(value_iCardList, 0, sizeof(value_iCardList));
	for (vector<int>::iterator iter = color_CardList.begin(); iter != color_CardList.end(); iter++)
	{
		int i = (*iter / 13) < 4 ? *iter % 13 : *iter - 39;
		value_CardList.push_back(i);
		value_iCardList[i]++;
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
	value_iCardList[value_Card]--;//value状态数组处理
	if (value_iCardList[value_Card] < 0)
	{
		return false;
	}
	for (vector<int>::iterator iter = value_CardList.begin(); iter != value_CardList.end(); iter++)//value列表数组处理
	{
		if (*iter == value_Card)
		{
			value_CardList.erase(iter);
			ret = true;
			break;
		}
	}
	for (vector<int>::iterator iter = color_CardList.begin(); iter != color_CardList.end(); iter++)//color列表数据处理
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
