#pragma once
#include "oxygine-framework.h"
#include "Scene.h"
#include "MyButton.h"

DECLARE_SMART(MainMenuScene, spMainMenuScene);
class MainMenuScene: public Scene
{
public:
	static spMainMenuScene instance;
	MainMenuScene();

private:
	void onEvent(Event* ev);
	spSprite office;
	spMyButton main_button;
	spMyButton speaker_button;
};