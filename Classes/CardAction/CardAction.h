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
	bool shuffle();//ϴ��
	void deal();//����
	void sort();//������

};