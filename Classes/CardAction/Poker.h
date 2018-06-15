#pragma once                             //同一个文件不会被包含多次.
#include "cocos2d.h"                     //cocos2dx 声明的函数、头文件包含的函数可以被使用
#include "CardSet.h"                     //见CardSet.h
class GameScene;                         //GameScene 的前置声明
USING_NS_CC;                             //使用了cocos2d的命名空间
class Poker : public Sprite              //Sprite 精灵类
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
	void showFront();//显示正面
	void showLast();//显示背面
	Poker* copy();//拷贝
	void setTouchPriority(int num);
	void SelectPkLuTou();//如果选择了牌就露出头
	void SelectPkSuoTou();//如果选择了牌就缩头
private:
	CC_SYNTHESIZE(bool, m_isSelect, Select);//是否已选
	CC_SYNTHESIZE(GameScene*, m_gameMain, GameMain);
	CC_SYNTHESIZE(bool, m_isDianJi, DianJi);//是否能被点击
	CC_SYNTHESIZE(int, m_huaSe, Suit);//花色
	CC_SYNTHESIZE(int, m_num, Num);//牌值
	EventListenerTouchOneByOne* touchListener;
};

