#pragma once
#include "cocos2d.h"
#include "CardAction.h"
USING_NS_CC;
class Player :public CCObject
{
public:
	Player();
	~Player();
	void call();//叫地主
private:
	CC_SYNTHESIZE(bool, m_isDiZhu, IsDiZhu);//是否为地主
	CC_SYNTHESIZE(bool, m_isCall, Call);//是否已叫地主
	CC_SYNTHESIZE(int, m_iCallNum, CallNum);//叫地主的分数
	CC_SYNTHESIZE(CCArray*, m_arrPk, ArrPk);//手里拥有的扑克牌
	CC_SYNTHESIZE(bool, m_isOutPk, IsOutPk);//玩家是否出牌true:出 false:不出
};