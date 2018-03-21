#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(StartScene);


private:
	void GoToGameScene(cocos2d::Ref *sender);
	void QuitGame(cocos2d::Ref *sender);

	cocos2d::Label *titleLabel;
	cocos2d::Label *titleLabelShadow;
};


#endif // __START_SCENE_H__
 