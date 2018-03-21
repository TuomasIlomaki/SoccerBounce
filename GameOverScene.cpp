#include "GameOverScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    return GameOverScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// create background
	auto backgroundSprite = Sprite::create("background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundSprite->setScale(0.5);

	this->addChild(backgroundSprite);

	// play button
	auto playItem = MenuItemImage::create("play_button.png", "play_button_clicked.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	playItem->setScale(0.8f);

	// quit button
	auto quitItem = MenuItemImage::create("quit_button.png", "quit_button_clicked.png", CC_CALLBACK_1(GameOverScene::QuitGame, this));
	quitItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
	quitItem->setScale(0.8f);

	auto menu = Menu::create(playItem, quitItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	// game over label
	gameOverLabel = Label::createWithTTF("GAME OVER", "grobold.ttf", visibleSize.height * GAME_OVER_FONT_SIZE);
	gameOverLabel->setColor(Color3B::WHITE);
	gameOverLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.8 + origin.y));

	gameOverLabelShadow = Label::createWithTTF("GAME OVER", "grobold.ttf", visibleSize.height * GAME_OVER_FONT_SIZE);
	gameOverLabelShadow->setColor(Color3B::BLACK);
	gameOverLabelShadow->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.79 + origin.y));

	auto gameoverSprite = Sprite::create("empty_button.png");
	gameoverSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.8 + origin.y));
	gameoverSprite->setScale(1.2f);

	this->addChild(gameOverLabel, 100);
	this->addChild(gameOverLabelShadow, 99);
	this->addChild(gameoverSprite, 98);

    return true;
}

void GameOverScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::QuitGame(cocos2d::Ref *sender)
{
	Director::getInstance()->end();
}
