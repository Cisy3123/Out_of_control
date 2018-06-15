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
	void sort();//整理牌
	bool aircraft();//是否飞机
	bool pair();//是否对子
	bool pairs();//是否连对
	bool straight();//是否顺子
	bool bomb();//是否炸弹

};