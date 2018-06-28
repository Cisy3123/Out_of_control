#include"HelloWorldScene.h"
#include"MainScene.h"
#include"SimpleAudioEngine.h"
USING_NS_CC;

MainScene::MainScene():m_isSend(true), m_iSendPk(0), m_iState(0), m_iOutCard(0)
{
	m_player = new Player();
	m_npcOne = new Player();
	m_npcTwo = new Player();
	m_arrPokers = CCArray::create();
	m_arrPokers->retain();
}

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
	return scene;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Welcome.mp3", true);
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/*auto closeItem = MenuItemImage::create(
		"play.png",
		"play.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'play.png' and 'play.png'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 8;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	*/


	// add "bg" splash screen"
	auto sprite = Sprite::create("bg.jpg");
	if (sprite == nullptr)
	{
		problemLoading("'bg.jpg'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}


	return true;
}

Poker* MainScene::selectPoker(int Suit, int num) {
	Poker* pk;
	if (Suit != joker)
		pk = Poker::create("poker.png", CCRect(num*CardWidth, Suit*CardHeight, CardWidth, CardHeight));
	else
		pk = Poker::create("poker.png", CCRect((num - jokerBlack)*CardWidth, Suit*CardHeight, CardWidth, CardHeight));
	pk->setSuit(Suit);
	pk->setNum(num);
	pk->setGameMain(this);
	return pk;
}

bool MainScene::createPokers() {
	bool isRet = false;
	do
	{
		Size size = Director::sharedDirector()->getVisibleSize();
		Poker* pk;
		//创建52个牌
		for (int i = 0; i<4; ++i)
		{
			for (int j = 0; j<13; ++j)
			{
				pk = selectPoker(i, j);
				pk->setPosition(ccp(size.width / 2/*+j*20*/, size.height / 2/*-i*20*/));
				pk->showLast();
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);
			}
		}
		//创建小鬼
		pk = selectPoker(joker, jokerBlack);
		pk->setPosition(ccp(size.width / 2, size.height / 2/*-4*20*/));
		pk->showLast();
		this->addChild(pk);
		this->m_arrPokers->addObject(pk);
		//创建大鬼
		pk = selectPoker(joker, jokerRed);
		pk->setPosition(ccp(size.width / 2/*+20*/, size.height / 2/*-4*20*/));
		pk->showLast();
		this->addChild(pk);
		this->m_arrPokers->addObject(pk);
		isRet = true;
	} while (0);
	return isRet;
}

bool MainScene::shuffle()//随机洗牌
{
	bool isRet = false;
	do
	{
		for (int i = 0; i<54; ++i)
		{
			Poker* pk1 = (Poker*)m_arrPokers->randomObject();
			Poker* pk2 = (Poker*)m_arrPokers->randomObject();
			m_arrPokers->exchangeObject(pk1, pk2);
		}
		isRet = true;
	} while (0);
	return isRet;
};

void MainScene::MovePk(Player* play, Poker* pk)
{
	CCMoveTo* move;
	CCCallFuncND* func;
	float time = 0.05;
	play->getArrPk()->addObject(pk);
	move = CCMoveTo::create(time, play->getPoint());
	func = CCCallFuncND::create(this, callfuncND_selector(MainScene::func), play);
	CCSequence* sequence = CCSequence::create(move, func, NULL);
	pk->runAction(sequence);
}

void MainScene::func(Node* pSender, void* pData) {
	Player* play = (Player*)pData;
	play->updatePkWeiZhi();
	m_isSend = true;
}

void MainScene::deal()//发牌
{
	Poker* pk;
	if (m_iSendPk<51 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		if (m_iSendPk % 3 == 0)//给玩家发牌
			MovePk(m_player, pk);
		else if (m_iSendPk % 3 == 1)//给电脑1发牌
			MovePk(m_npcOne, pk);
		else if (m_iSendPk % 3 == 2)//给电脑2发牌
			MovePk(m_npcTwo, pk);
		++m_iSendPk;
		m_isSend = false;
	}
	else if (m_iSendPk>50 && m_iSendPk<54 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		pk->showFront();
		MovePk(m_Three, pk);
		++m_iSendPk;
		m_isSend = false;
	}
	else if (m_iSendPk>53)
	{
		Analyze(m_npcOne);
		Analyze(m_npcTwo);
		m_iSendPk = 0;
		m_iState = 1;
	}
}

void MainScene::Call(float dt)
{
	if (!m_player->getCall())
	{

	}
}