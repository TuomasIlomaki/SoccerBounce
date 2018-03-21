#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameOverScene);

private:

	void GoToGameScene(cocos2d::Ref *sender);
	void QuitGame(cocos2d::Ref *sender);

	cocos2d::Label *gameOverLabel;
	cocos2d::Label *gameOverLabelShadow;
};

#endif // __GAME_OVER_SCENE_H__
