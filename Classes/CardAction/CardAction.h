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
	CardGroupData CardsType(vector<int> Card); //给出牌型组合
	void changeNowCard();//出牌后，更新当前打出的牌
	void ClearPutCard();//出牌后，清空原选中的牌
	void Arrange();//整理现有手牌
	void copyTOtemp();//把当前场上的copy到temp
	void tempTOput();//把temp传递到color_PutCard
	bool find_Cards();//找到对于当前牌的解决方案
	void getCardList();//由手牌序列得到状态数组
private:
	int CardCount;//手牌个数
	int HandCardList[15];//手牌状态数组
	vector<int> NowCard;//当前打出的牌
	vector<int> color_PutCard;//选中的牌
	vector<int> temp;//针对当前牌的临时解决方案
	vector<int> color_CardList;//手牌序列，0~54
};