#pragma once
#ifndef __Main_SCENE_H__
#define __Main_SCENE_H__

#include "cocos2d.h"
#include"HelloWorldScene.h"
#include"CardAction.h"
#include"CardSet.h"
#include"Player.h"
#include"Poker.h"

class MainScene : public cocos2d::Layer
{
public:
	MainScene();
	~MainScene();
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

	bool initPlayer();//初始化玩家信息
	bool initCall();//初始化叫地主按钮
	Poker* selectPoker(int Suit, int num);//生成一张牌
	bool createPokers();//创建一副牌
	bool shuffle();//洗牌
	void deal();//发牌
	void MovePk(Player* play, Poker* pk);//移动发牌
	void func(Node* pSender, void* pData);
	void Call(float dt);//叫地主
	void Analyze(Player* npc);//分析电脑手中的牌

private:
	CCArray* m_arrPokers;//所有的牌
	CC_SYNTHESIZE(Player*, m_player, Player);//玩家
	Player* m_npcOne;//电脑1
	Player* m_npcTwo;//电脑2
	bool m_isSend;//是否发完牌
	int m_iSendPk;//已发出第几张牌
	int m_iState;//当前状态 0：发牌状态 1：叫地主状态 2：出牌状态 3：结果状态
	int m_iOutCard;//论到谁出牌
	Player* m_Three;//显示三张剩余牌
};

#endif // __HELLOWORLD_SCENE_H__
