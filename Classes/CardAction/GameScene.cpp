#include "GameScene.h"
#include "Poker.h"
#include "Player.h"
#include "vector"
#include<algorithm>
#include <string>
//#include <deque>
GameScene::GameScene():m_isSend(true),m_iSendPk(0),m_iState(0),
					   m_iCall(0),m_iCallTime(0),m_iOutCard(0),
					   m_type(ERROR_CARD),m_isChiBang(true){
	m_player1 = new Player();
	m_player2 = new Player();
	m_player3= new Player();
	m_Three = new Player();
	m_player1Out = new Player();
	m_plater2OneOut = new Player();
	m_player3Out = new Player();
	m_arrPlayerOut = CCArray::create();
	m_arrPlayerOut->retain();
	m_arrGenPk = CCArray::create();
	m_arrGenPk->retain();
	m_arrPokers = CCArray::create();
	m_arrPokers->retain();
	for(int i=0; i<3; ++i)
		m_bCall[i] = false;
	player1DiZhuLablePt = CCPointMake(100,100);
	player2DiZhuLablePt = CCPointMake(65+100,504);
	player3DiZhuLablePt = CCPointMake(735-100,504);
}
GameScene::~GameScene(){
	CC_SAFE_DELETE(m_player1);
	CC_SAFE_DELETE(m_player2);
	CC_SAFE_DELETE(m_player3);
	CC_SAFE_DELETE(m_Three);
	CC_SAFE_DELETE(m_player1Out);
	CC_SAFE_DELETE(m_player2Out);
	CC_SAFE_DELETE(m_player3Out);
	CC_SAFE_RELEASE(m_arrPokers);
	CC_SAFE_RELEASE(m_arrPlayerOut);
	CC_SAFE_RELEASE(m_arrGenPk);
}
Scene* GameScene::scene(){
	Scene* scene = Scene::create();
	GameScene * gameLayer = GameScene::create();
	scene->addChild(gameLayer);
	return scene;
}
bool GameScene::init(){
	CCLayer::init();
	bool isRet = false;
	do 
	{
		
		srand((unsigned)time(NULL));//初始化随机种子
		CC_BREAK_IF(!initBackGround());
		CC_BREAK_IF(!createPokers());
		CC_BREAK_IF(!initPlayer());
		CC_BREAK_IF(!xiPai());
		CC_BREAK_IF(!initAnNiu());
		CC_BREAK_IF(!InitNpcBuChuLable());
		//地主标签
		Dictionary * strings = Dictionary::createWithContentsOfFile("strings.xml");
		const char *str = ((String *)strings->objectForKey("dizhu"))->getCString();
		m_lableDiZhu = CCLabelTTF::create(str,"Helvetica-BoldOblique",20);
		m_lableDiZhu->setPosition(ccp(100,100));
		this->addChild(m_lableDiZhu,1);
		m_lableDiZhu->setVisible(false);
		scheduleUpdate();

		isRet = true;
	} while (0);
	return isRet;
}
void GameScene::onEnter()
{
	CCLayer::onEnter();

}
void GameScene::onExit()
{
	CCLayer::onExit();
}
bool GameScene::initBackGround()
{
	bool isRet = false;
	do 
	{	
		CCSprite* bk = CCSprite::create("bk.png");
		this->addChild(bk,0);
		bk->setAnchorPoint(ccp(0,0));

		isRet = true;
	} while (0);
	return isRet;
}
Poker* GameScene::selectPoker(int Suit,int num)
{
	Poker* pk;
	if(Suit != Gui)
		pk = Poker::create("poker.png",CCRect(num*pkWidth,huaSe*pkHeight,pkWidth,pkHeight));
	else
		pk = Poker::create("poker.png",CCRect((num-XiaoGui)*pkWidth,huaSe*pkHeight,pkWidth,pkHeight));
	pk->setHuaSe(Suit);
	pk->setNum(num);
	pk->setGameMain(this);
	return pk;
}
bool GameScene::createPokers(){
	bool isRet = false;
	do 
	{
		Size size = Director::sharedDirector()->getVisibleSize();
		Poker* pk;
		//创建52个牌
		for (int i=0; i<4; ++i)
		{
			for (int j=0; j<13; ++j)
			{
				pk = selectPoker(i,j);
				pk->setPosition(ccp(size.width/2/*+j*20*/,size.height/2/*-i*20*/));
				pk->showLast();
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);
			}
		}
		//创建小鬼
		pk = selectPoker(Gui,jokerBlack);
		pk->setPosition(ccp(size.width/2,size.height/2/*-4*20*/));
		pk->showLast();
		this->addChild(pk);
		this->m_arrPokers->addObject(pk);
		//创建大鬼
		pk = selectPoker(Gui,jokerRed);
		pk->setPosition(ccp(size.width/2/*+20*/,size.height/2/*-4*20*/));
		pk->showLast();
		this->addChild(pk);
		this->m_arrPokers->addObject(pk);
		isRet = true;
	} while (0);
	return isRet;
}


