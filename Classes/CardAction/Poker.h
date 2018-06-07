#pragma once                             //ͬһ���ļ����ᱻ�������.
#include "cocos2d.h"                     //cocos2dx �����ĺ�����ͷ�ļ������ĺ������Ա�ʹ��
#include "CardSet.h"                      //��Global.h
class GameScene;                         //GameScene ��ǰ������
USING_NS_CC;                             //ʹ����cocos2d�������ռ�
class Poker : public Sprite              //Sprite ������
{
public:
	Poker();
	~Poker();
	static Poker* create(const char *pszFileName, const CCRect& rect);
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	void showFront();//��ʾ����
	void showLast();//��ʾ����
	Poker* copy();//����
	void setTouchPriority(int num);
	void SelectPkLuTou();//���ѡ�����ƾ�¶��ͷ
	void SelectPkSuoTou();//���ѡ�����ƾ���ͷ
private:
	CC_SYNTHESIZE(bool, m_isSelect, Select);//�Ƿ���ѡ
	CC_SYNTHESIZE(GameScene*, m_gameMain, GameMain);
	CC_SYNTHESIZE(bool, m_isDianJi, DianJi);//�Ƿ��ܱ����
	CC_SYNTHESIZE(int, m_huaSe, HuaSe);//��ɫ
	CC_SYNTHESIZE(int, m_num, Num);//��ֵ
	EventListenerTouchOneByOne* touchListener;
};

