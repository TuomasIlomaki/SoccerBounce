#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);

private:

	void SetPhysicsWorld(cocos2d::PhysicsWorld *world)
	{
		sceneWorld = world;
	}

	bool onContactBegin(cocos2d::PhysicsContact &contact);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	unsigned int score;

	cocos2d::PhysicsWorld *sceneWorld;
	cocos2d::Sprite *footballSprite;
	cocos2d::Label *scoreLabel;
	cocos2d::Label *scoreLabelShadow;
};

#endif // __GAME_SCENE_H__
