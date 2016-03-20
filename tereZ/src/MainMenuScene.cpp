#include "MainMenuScene.h"
#include "res.h"
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

	//spTween tween;
	//tween = office->addTween(Actor::TweenScale(Vector2(hScale*1.2f, vScale*1.2f)), 5000, 0, true);
	//tween = office->addTween(TweenDummy(), 5000);
	//tween->addEventListener(TweenEvent::DONE, CLOSURE(this, &MainMenuScene::onEvent));

	spSprite btn = 0;

	//create play button at center
	btn = initActor(new MyButton,
		arg_name = "play",
		arg_resAnim = res::ui.getResAnim("start_button"),
		arg_anchor = Vector2(0.5f, 1.5f),
		arg_pos = _view->getSize() / 2,
		arg_attachTo = _view);

	//handle click to button
	btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MainMenuScene::onEvent));

	//create menu button
	btn = initActor(new MyButton,
		arg_name = "exit",
		arg_resAnim = res::ui.getResAnim("quit_button"),
		arg_anchor = Vector2(0.5f, -0.5f),
		arg_pos = _view->getSize() / 2,
		arg_attachTo = _view);

	btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MainMenuScene::onEvent));
}

void MainMenuScene::onEvent(Event* ev)
{
	/*
	if (ev->type == TweenEvent::DONE)
	{
		float offsetX = -rand() / (RAND_MAX / (_view->getWidth()*0.1f));
		float offsetY = -rand() / (RAND_MAX / (_view->getHeight()*0.1f));
		log::messageln("x: %f; y: %f", offsetX, offsetY);
		spTween tween;
		tween = office->addTween(Actor::TweenPosition(Vector2(
			offsetX,
			offsetY
		)), 5000, 1, true);
		tween->addEventListener(TweenEvent::DONE, CLOSURE(this, &MainMenuScene::onEvent));

	}
	*/
	string id = ev->currentTarget->getName();
	if (id == "exit")
	{
		core::requestQuit();
	}

	if (id == "play")
	{
		//clicked to play button change scene
		GameScene::instance = new GameScene();
		changeScene(GameScene::instance);
	}
}