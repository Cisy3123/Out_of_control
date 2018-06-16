#pragma once
#include "cocos2d.h"
#include "CardSet.h"
#include <vector>
USING_NS_CC;
class CardAction
{
public:
	CardAction();
	~CardAction();
	bool shuffle();//洗牌
	void deal();//发牌
	void Sort(vector<int> &arr);//整理牌
	CardGroupData  PutCardType;//玩家要打出去的牌的类型
	void ClearPutCard();//出牌后，清空原选中的牌
	void Arrange();//整理现有手牌

private:
	vector<int> color_CardList;//手牌序列，0~54
	int CardCount;//手牌个数
	vector<int> color_PutCard;//选中的牌
};