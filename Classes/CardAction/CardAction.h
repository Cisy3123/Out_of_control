#pragma once
#include "cocos2d.h"
#include "CardSet.h"
#include"Player.h"
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
	CardGroupData CardsType(vector<int> color_PutCard); //给出牌型组合
	void changeNowCard();//出牌后，改变当前打出的牌的类型数据
	void ClearPutCard();//出牌后，清空原选中的牌
	void Arrange();//整理现有手牌
	CardGroupData NowCardGroup() //提供当前打出的牌的信息;
	bool find_Cards(CardGroupData temp);//找到对于当前牌的解决方案
private:
	CardGroupData NowCardGroup;//当前打出牌的类型数据
	CardGroupData PutCardType;//选中的牌的类型数据
	vector<int> color_PutCard;//选中的牌
	int CardCount;//手牌个数
	CardGroupData temp;//针对当前牌的临时解决方案
	vector<int> color_CardList;//手牌序列，0~54
};