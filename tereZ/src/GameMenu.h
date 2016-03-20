#pragma once
#include "oxygine-framework.h"
#include "Scene.h"

DECLARE_SMART(GameMenu, spGameMenu);
class GameMenu : public Scene
{
public:
	static spGameMenu instance;
	GameMenu();

private:
	void onEvent(Event* ev);
};