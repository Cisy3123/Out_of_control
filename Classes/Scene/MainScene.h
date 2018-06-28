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

	bool initPlayer();//��ʼ�������Ϣ
	bool initCall();//��ʼ���е�����ť
	Poker* selectPoker(int Suit, int num);//����һ����
	bool createPokers();//����һ����
	bool shuffle();//ϴ��
	void deal();//����
	void MovePk(Player* play, Poker* pk);//�ƶ�����
	void func(Node* pSender, void* pData);
	void Call(float dt);//�е���
	void Analyze(Player* npc);//�����������е���

private:
	CCArray* m_arrPokers;//���е���
	CC_SYNTHESIZE(Player*, m_player, Player);//���
	Player* m_npcOne;//����1
	Player* m_npcTwo;//����2
	bool m_isSend;//�Ƿ�����
	int m_iSendPk;//�ѷ����ڼ�����
	int m_iState;//��ǰ״̬ 0������״̬ 1���е���״̬ 2������״̬ 3�����״̬
	int m_iOutCard;//�۵�˭����
	Player* m_Three;//��ʾ����ʣ����
};

#endif // __HELLOWORLD_SCENE_H__
