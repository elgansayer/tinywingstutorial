
#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_background = nullptr;

	return true;
}

Sprite* HelloWorld::spriteWithColor(Color4F bgColor, float textureWidth, float textureHeight)
{
	// 1: Create new RenderTexture
	RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);

	// 2: Call RenderTexture:begin
	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

	// 3: Draw into the texture

	//// gradient
	_command.init(rt->getGlobalZOrder());
	_command.func = CC_CALLBACK_0(HelloWorld::onDrawGradient, this);
	auto renderer = Director::getInstance()->getRenderer();
	renderer->addCommand(&_command);

	//// noise cloud
	Sprite *noise = Sprite::create("Noise.png");
	noise->setBlendFunc(BlendFunc{ GL_DST_COLOR, GL_ZERO });
	noise->setPosition(Vec2(textureWidth / 2, textureHeight / 2));
	noise->visit();

	// 4: Call CCRenderTexture:end
	rt->end();

	// 5: Create a new Sprite from the texture
	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

void HelloWorld::onDrawGradient()
{
	setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
	getGLProgram()->use();
	getGLProgram()->setUniformsForBuiltins();

	Size winSize = Director::getInstance()->getWinSize();

	float gradientAlpha = 0.7f;

	int nVertices = 0;
	std::vector<Vec2> vertices;
	std::vector<Color4F> colors;

	vertices.push_back(Vec2(0, 0));
	colors.push_back(Color4F{ 0, 0, 0, 0 });

	vertices.push_back(Vec2(winSize.width, 0));
	colors.push_back(Color4F{ 0, 0, 0, 0 });

	vertices.push_back(Vec2(0, winSize.height));
	colors.push_back(Color4F{ 0, 0, 0, gradientAlpha });

	vertices.push_back(Vec2(winSize.width, winSize.height));
	colors.push_back(Color4F{ 0, 0, 0, gradientAlpha });

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)vertices.size());
}

Color4F HelloWorld::randomBrightColor()
{
	while (true) {
		float requiredBrightness = 192;
		Color4B randomColor =
			Color4B(rand() % 255,
			rand() % 255,
			rand() % 255,
			255);
		if (randomColor.r > requiredBrightness ||
			randomColor.g > requiredBrightness ||
			randomColor.b > requiredBrightness) {
			return Color4F(randomColor);
		}
	}
}

void HelloWorld::genBackground()
{
	if (_background) {
		_background->removeFromParentAndCleanup(true);
	}

	Color4F bgColor = randomBrightColor();
	_background = spriteWithColor(bgColor, 512, 512);
	
	Size winSize = Director::getInstance()->getWinSize();
	_background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	addChild(_background, -1);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	genBackground();

	// Enable Touches/Mouse.
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	genBackground();
}
