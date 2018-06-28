#include"HelloWorldScene.h"
#include"MainScene.h"
#include"SimpleAudioEngine.h"

USING_NS_CC;

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

auto jiaodizhu = MenuItemImage::create(
		"jiaodizhu.png",
		"jiaodizhu.png",
		CC_CALLBACK_1(MainScene::menuJiaodizhu, this));

	if (jiaodizhu == nullptr ||
		jiaodizhu->getContentSize().width <= 0 ||
		jiaodizhu->getContentSize().height <= 0)
	{
		problemLoading("'jiaodizhu.png' and 'jiaodizhu.png'");
	}
	else
	{
		float x = (visibleSize.width / 8)*3;
		float y = visibleSize.height / 3;
		jiaodizhu->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(jiaodizhu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto bujiao = MenuItemImage::create(
		"bujiao.png",
		"bujiao.png",
		CC_CALLBACK_1(MainScene::menubujiao, this));

	if (bujiao == nullptr ||
		bujiao->getContentSize().width <= 0 ||
		bujiao->getContentSize().height <= 0)
	{
		problemLoading("'bujiao.png' and 'bujiao.png'");
	}
	else
	{
		float x = (visibleSize.width / 8)*5;
		float y = visibleSize.height / 3;
		bujiao->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu1 = Menu::create(bujiao, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

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

	for (int i = 0; i < 17; ++i)
	{
		auto  npc1Card = Sprite::create("npc_card.png");
		if (npc1Card == nullptr)
		{
			problemLoading("npc_card.png");
		}
		else
		{
			// position the sprite on the center of the screen
			npc1Card->setPosition(Vec2(visibleSize.width /10+origin.x, visibleSize.height/3+20*i ));

			// add the sprite as a child to this layer
			this->addChild(npc1Card, 0);
		}
	}

	for (int j= 0; j< 17; ++j)
	{
		auto  npc2Card = Sprite::create("npc_card.png");
		if (npc2Card == nullptr)
		{
			problemLoading("npc_card.png");
		}
		else
		{
			// position the sprite on the center of the screen
			npc2Card->setPosition(Vec2(9*(visibleSize.width / 10) - origin.x, visibleSize.height / 3 + 20 * j));

			// add the sprite as a child to this layer
			this->addChild(npc2Card, 0);
		}
	}

	for (int k= 3; k<=5; ++k)
	{
		auto  lordCard = Sprite::create("lord_card.png");
		if (lordCard == nullptr)
		{
			problemLoading("lord_card.png");
		}
		else
		{
			// position the sprite on the center of the screen
			lordCard->setPosition(Vec2(k*(visibleSize.width / 8)+ origin.x, visibleSize.height / 2+80));

			// add the sprite as a child to this layer
			this->addChild(lordCard, 0);
		}
	}

	auto player = Sprite::create("touxiang_nan.png");
	if (player == nullptr)
	{
		problemLoading("touxiang_nan.png");
	}
	else
	{
		// position the sprite on the center of the screen
		player->setPosition(Vec2(visibleSize.width / 16 + origin.x, (visibleSize.height / 8) + origin.y));

		// add the sprite as a child to this layer
		this->addChild(player, 0);
	}


	auto npc1 = Sprite::create("touxiang_nan.png");
	if (npc1 == nullptr)
	{
		problemLoading("touxiang_nan.png");
	}
	else
	{
		// position the sprite on the center of the screen
		npc1->setPosition(Vec2(visibleSize.width / 16 + origin.x, 7*(visibleSize.height / 8)+ origin.y));

		// add the sprite as a child to this layer
		this->addChild(npc1, 0);
	}

	auto npc2 = Sprite::create("touxiang_nv.png");
	if (npc2== nullptr)
	{
		problemLoading("touxiang_nv.png");
	}
	else
	{
		// position the sprite on the center of the screen
		npc2->setPosition(Vec2(15*(visibleSize.width / 16 )+ origin.x, 7 * (visibleSize.height / 8) + origin.y));

		// add the sprite as a child to this layer
		this->addChild(npc2, 0);
	}

	auto  lord = Sprite::create("lord.png");
	if (lord == nullptr)
	{
		problemLoading("lord.png");
	}
	else
	{
		// position the sprite on the center of the screen
		lord->setPosition(Vec2(visibleSize.width /2+ origin.x, (visibleSize.height / 3) + origin.y));

		// add the sprite as a child to this layer
		this->addChild(lord, 0);
	}
	return true;
}

void MainScene::menuJiaodizhu(Ref* pSender)
{
	MoveTo* move = MoveTo::create(1.0f, ccp(480, 160));
	lord->runAction(move);


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


 
void MainScene::menubujiao(Ref* pSender)
{

	MoveTo* move = MoveTo::create(1.0f, ccp(480, 160));
	lord->runAction(move);
	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}



