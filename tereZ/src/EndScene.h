#pragma once
#include "Scene.h"
#include "Game.h"
#include "MyButton.h"

DECLARE_SMART(EndScene, spEndScene);
class EndScene : public Scene
{
public:
	static spEndScene instance;
	EndScene(int stars);

private:
	void onEvent(Event* ev);
};
