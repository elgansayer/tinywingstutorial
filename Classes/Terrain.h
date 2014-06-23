#ifndef _TERRAIN_H__
#define _TERRAIN_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

using namespace cocos2d;

#define kMaxHillKeyPoints 1000

class Terrain :
	public Node
{
public:
	Terrain();
	~Terrain();	

	static Terrain* create();
	bool init();

	void setStripes(Sprite *stripes);
	void setOffsetX(float nOffsetX);

	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
private:
	Sprite *_stripes;
	int _offsetX;
	Vec2 _hillKeyPoints[kMaxHillKeyPoints];

	void generateHills();
};

#endif	// _TERRAIN_H__