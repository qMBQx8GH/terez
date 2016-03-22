#include "MainMenuScene.h"
#include "res.h"
#include "GameSound.h"
#include "Sprite.h"
#include "initActor.h"
#include "MyButton.h"
#include "GameScene.h"
#include <stdlib.h>

using namespace std;

spMainMenuScene MainMenuScene::instance;

MainMenuScene::MainMenuScene()
{
	//create background
	office = new Sprite;
	office->setResAnim(res::ui.getResAnim("office"));
	float hScale = _view->getWidth() / office->getWidth();
	office->setScaleX(hScale);
	float vScale = _view->getHeight() / office->getHeight();
	office->setScaleY(vScale);
	office->attachTo(_view);

	//create play button at center
	main_button = initActor(new MyButton(res::ui.getResAnim("main_button"), res::ui.getResAnim("main_button_a")),
		arg_name = "play",
		arg_anchor = Vector2(0.5f, 0.0f),
		arg_pos = Vector2(office->getWidth() / 2.0f, 0.0f),
		arg_attachTo = office);

	//handle click to button
	main_button->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &MainMenuScene::onEvent));

	//create menu button
	speaker_button = initActor(new MyButton(res::ui.getResAnim("speaker_button"), res::ui.getResAnim("speaker_button_a")),
		arg_name = "speaker",
		//arg_resAnim = GameSound::isMuted()? : ,
		arg_anchor = Vector2(1.0f, 0.0f),
		arg_pos = Vector2(office->getWidth(), 0.0f),
		arg_attachTo = office);

	speaker_button->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &MainMenuScene::onEvent));
}

void MainMenuScene::onEvent(Event* ev)
{
	string id = ev->currentTarget->getName();

	if (id == "speaker")
	{
		if (GameSound::isMuted())
			GameSound::unmute();
		else
			GameSound::mute();
		speaker_button->setPressedState(GameSound::isMuted());
		//speaker_button->setResAnim(GameSound::isMuted() ? res::ui.getResAnim("speaker_button") : res::ui.getResAnim("speaker_button_a"));
	}

	if (id == "play")
	{
		//clicked to play button change scene
		GameScene::instance = new GameScene();
		changeScene(GameScene::instance);
	}
}