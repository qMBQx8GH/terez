#include "oxygine-framework.h"
#include "SoundPlayer.h"
#include "SoundSystem.h"
#include "SoundInstance.h"
#include "MainMenuScene.h"

#include <functional>
using namespace oxygine;

//it is our resources
//in real project you would have more than one Resources declarations.
//It is important on mobile devices with limited memory and you would load/unload them
Resources gameResources;
SoundPlayer splayer;

void example_preinit() {}

//called from main.cpp
void example_init()
{
	//initialize our sound system with 16 channels

	SoundSystem::create()->init(16);

	//initialize SoundPlayer
	SoundPlayer::initialize();
	splayer.setResources(&gameResources);
	
	//load xml file with resources definition
    gameResources.loadXML("xmls/ui.xml");

	splayer.play(gameResources.get("background"), PlayOptions().loop());

	MainMenuScene::instance = new MainMenuScene(&gameResources);
	getStage()->addChild(MainMenuScene::instance->getView());
}


//called each frame from main.cpp
void example_update()
{
	SoundSystem::instance->update();
	splayer.update();
}

//called each frame from main.cpp
void example_destroy()
{
	MainMenuScene::instance = 0;
    //free previously loaded resources
    gameResources.free();
}
