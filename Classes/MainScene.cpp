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




