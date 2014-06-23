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
	CustomCommand _stripes_command;
	CustomCommand _gradient_command;
	CustomCommand _tophighlight_command;

	Terrain *_terrain;

	Sprite* spriteWithColor(Color4F bgColor, float textureWidth, float textureHeight);
	Color4F randomBrightColor();
	void genBackground();
	void onDrawGradient(float textureWidth, float textureHeight);

	Sprite* stripedSpriteWithColor(Color4F c1, Color4F c2, float textureWidth, float textureHeight, int nStripes);
	void onDrawStripes(Color4F c2, float textureWidth, float textureHeight, int nStripes);
	void onDrawTopHighlight(float textureWidth, float textureHeight);

	void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
