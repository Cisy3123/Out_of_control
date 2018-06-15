#pragma once
#include"CardSet.h"

class CardData
{
public:
	CardData(){}
	virtual ~CardData(){}
	CardGroupData  PutCardType;//玩家要打出去的牌的类型
	void ClearPutCard();//清空要打出的牌
	void Sort(vector<int> &arr);//手牌排序，大牌靠前
	bool PutOneCard(int value_Card, int &clear_Card);//出一张牌，返回操作是否合法
	bool PutCards();//出一组牌，返回操作是否合法
	void get_valueCard();//通过有花色牌获取无花色牌
	void Init();//初始化
private:
	vector<int> value_CardList;//手牌序列-无花色，0~14
	vector<int> color_CardList;//手牌序列-有花色，0~54
	int value_iCardList[15] = { 0 };//手牌序列-状态记录，记录每张牌的数目
	int CardCount = 17;//手牌个数
	vector<int> value_PutCard;//要打出去的牌-无花色
	vector<int> color_PutCard;//要打出去的牌-有花色
};