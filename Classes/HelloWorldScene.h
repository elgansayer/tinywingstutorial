#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Terrain.h"
#include "GLES-Render.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelloWorld);
		
	virtual void onEnter();
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);

private:
	Sprite *_background;
	CustomCommand _command;

	Sprite* spriteWithColor(Color4F bgColor, float textureWidth, float textureHeight);
	Color4F randomBrightColor();
	void genBackground();
};

#endif // __HELLOWORLD_SCENE_H__