#pragma once
#include "Scene.h"
#include "Game.h"
#include "MyButton.h"

#include "Box2DDebugDraw.h"

DECLARE_SMART(GameScene, spGameScene);
class GameScene : public Scene
{
public:
	static spGameScene instance;
	GameScene();
	spGame _game;

private:
	void onEvent(Event* ev);
	spMyButton pause_button;

	spBox2DDraw _debugDraw;
};
