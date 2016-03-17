#pragma once
#include "Scene.h"
#include "Player.h"
#include "Door.h"

DECLARE_SMART(GameScene, spGameScene);
class GameScene: public Scene
{
public:
	static spGameScene instance;
	GameScene();

private:
	void onEvent(Event* ev);
	spPlayer zombie;
	spSprite floor_left;
	spSprite floor_right;
	spDoor doors[7];
	int cDoor;
};
