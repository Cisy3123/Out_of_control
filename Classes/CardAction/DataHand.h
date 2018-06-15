#pragma once
#include<iostream>
#include<stddef.h>
#include<vector>
#include<algorithm>
#include"CardSet.h"
using namespace std;

class CardData
{
public:
	CardData(){}
	virtual ~CardData(){}
	vector<int> value_CardList;//手牌序列-无花色，3~17
	vector<int> color_CardList;//手牌序列-有花色
	int value_iCardList[18] = { 0 };//手牌序列-状态记录
	int CardCount = 17;//手牌个数
	CARD_TYPE PutCardType;//玩家要打出去的牌的类型
	vector<int> value_PutCard;//要打出去的牌-无花色
	vector<int> color_PutCard;//要打出去的牌-有花色
	void ClearPutCard();//清空要打出的牌
	void Sort(vector<int> &arr);//手牌排序，大牌靠前
	bool PutOneCard(int value_Card, int &clear_Card);//出一张牌，返回操作是否合法
	bool PutCards();//出一组牌，返回操作是否合法
	void get_valueCard();//通过有花色牌获取无花色牌
	void Init();//初始化
	
};

void CardData::ClearPutCard()
{
	color_PutCard.clear();
	value_PutCard.clear();
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
	value_CardList.clear();                               //清零
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
	value_CardList[value_Card]--;
	if (value_CardList[value_Card] < 0)
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
	int k = (value_Card - 3) * 4;
	for (vector<int>::iterator iter = color_CardList.begin(); iter != color_CardList.end(); iter++)
	{
		for (int i = k; i < k + 4; i++)
		{
			if (*iter == 1)
			{
				color_Card = 1;
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
