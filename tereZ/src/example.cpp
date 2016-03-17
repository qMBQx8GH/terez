#include "oxygine-framework.h"
#include "GameSound.h"
#include "res.h"

#include "MainMenuScene.h"
#include "GameScene.h"

#include <functional>
using namespace oxygine;

void example_preinit() {}

//called from main.cpp
void example_init()
{
	//initialize our sound system with 16 channels

	GameSound::init(&res::ui);
	res::load();

	GameSound::playBackground("background");

	MainMenuScene::instance = new MainMenuScene();
	getStage()->addChild(MainMenuScene::instance->getView());

	GameScene::instance = new GameScene();
}


//called each frame from main.cpp
void example_update()
{
	GameSound::update();
}

//called each frame from main.cpp
void example_destroy()
{
	MainMenuScene::instance = 0;
	//free previously loaded resources
	res::free();
}
