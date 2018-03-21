#include "GameScene.h"
#include "GameOverScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
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

	// create borders
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	// create ground
	auto groundBody = PhysicsBody::createBox(Size(visibleSize.width, visibleSize.height / 10), PHYSICSBODY_MATERIAL_DEFAULT);
	groundBody->setDynamic(false);
	groundBody->setCollisionBitmask(GROUND_COLLISION_BITMASK);
	groundBody->setContactTestBitmask(true);

	auto groundNode = Node::create();
	groundNode->setPhysicsBody(groundBody);
	groundNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 50 + origin.y));

	this->addChild(groundNode);

	// football physics
	footballSprite = Sprite::create("football.png");
	footballSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	footballSprite->setScale(0.14f);

	auto footballBody = PhysicsBody::createCircle(footballSprite->getContentSize().width / 2, PhysicsMaterial(0, 1, 1));
	footballBody->setCollisionBitmask(FOOTBALL_COLLISION_BITMASK);
	footballBody->setContactTestBitmask(true);

	footballSprite->setPhysicsBody(footballBody);
	this->addChild(footballSprite);

	// handle input
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	// check collisions
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// set score display
	score = 0;
	__String *tempScore = __String::createWithFormat("%i", score);
	
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "grobold.ttf", visibleSize.height * SCORE_FONT_SIZE);
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->setPosition(Point(visibleSize.width / 10 + origin.x, visibleSize.height * 0.95 + origin.y));

	scoreLabelShadow = Label::createWithTTF(tempScore->getCString(), "grobold.ttf", visibleSize.height * SCORE_FONT_SIZE);
	scoreLabelShadow->setColor(Color3B::BLACK);
	scoreLabelShadow->setPosition(Point(visibleSize.width / 10 + origin.x, visibleSize.height * 0.945 + origin.y));
	
	this->addChild(scoreLabel, 100);
	this->addChild(scoreLabelShadow, 99);

    return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	Vec2 clickLocation = touch->getLocation();
	Vec2 footballLocation = footballSprite->getPhysicsBody()->getPosition();
	float x_force = footballLocation.x - clickLocation.x;

	if (footballLocation.y <= (Director::getInstance()->getVisibleSize().height / 3.5))
	{
		if (footballSprite->getBoundingBox().containsPoint(clickLocation))
		{
			footballSprite->getPhysicsBody()->setVelocity(Vec2(x_force * KICK_STRENGTH_X, KICK_STRENGTH_Y));

			score++;

			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
			scoreLabelShadow->setString(tempScore->getCString());
		}
	}

	return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) 
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((FOOTBALL_COLLISION_BITMASK == a->getCollisionBitmask() && GROUND_COLLISION_BITMASK == b->getCollisionBitmask()) || 
		(FOOTBALL_COLLISION_BITMASK == b->getCollisionBitmask() && GROUND_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

	return true;
}
