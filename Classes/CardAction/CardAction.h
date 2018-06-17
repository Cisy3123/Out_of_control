#pragma once
#include "cocos2d.h"
#include "CardSet.h"
#include <vector>
USING_NS_CC;
class CardAction
{
	friend class Player;
public:
	CardAction();
	~CardAction();
	bool shuffle();//洗牌
	void deal();//发牌
	void Sort(vector<int> &arr);//整理牌

	void ClearPutCard();//出牌后，清空原选中的牌
	void Arrange();//整理现有手牌
	CardGroupData NowCardGroup() //提供当前打出的牌的信息;
private:
	CardGroupData NowCardGroup;//当前打出牌的类型数据
	CardGroupData PutCardType;//选中的牌的类型数据
	vector<int> color_PutCard;//选中的牌
};