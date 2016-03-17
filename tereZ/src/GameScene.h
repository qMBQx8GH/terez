#pragma once
#include "Scene.h"
#include "Player.h"

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
	spSprite left_doors[7];
	spSprite right_doors[7];
	int cDoor;
};
