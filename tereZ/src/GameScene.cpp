#include "GameScene.h"
#include "MainMenuScene.h"
#include "MyButton.h"
#include "res.h"
#include <stdlib.h>

using namespace std;

spGameScene GameScene::instance;

GameScene::GameScene()
{
	//create game actor
	_game = new Game;
	_game->init();
	_game->attachTo(_view);

	//Game Actor would have own Clock.
	//clock is internal time of each Actor
	//by default own clock has only Stage
	//clock could be paused and all children of this Actor would be paused to
	_game->setClock(new Clock);

	spActor btn = 0;

	pause_button = initActor(new MyButton,
		arg_name = "pause",
		arg_resAnim = res::ui.getResAnim("pause_button"),
		arg_scale2 = _game->getScale(),
		arg_attachTo = _view);
	pause_button->setX(_game->getWidth() - _game->getScaleX() * pause_button->getWidth() * 1.0f);
	pause_button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameScene::onEvent));

	btn = initActor(new MyButton,
		arg_name = "retry",
		arg_resAnim = res::ui.getResAnim("retry_button"),
		arg_scale2 = _game->getScale(),
		arg_attachTo = _view);
	btn->setX(_game->getWidth() - _game->getScaleX() * btn->getWidth() * 2.0f);
	btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameScene::onEvent));

	btn = initActor(new MyButton,
		arg_name = "home",
		arg_resAnim = res::ui.getResAnim("home_button"),
		arg_scale2 = _game->getScale(),
		arg_attachTo = _view);
	btn->setX(_game->getWidth() - _game->getScaleX() * btn->getWidth() * 3.0f);
	btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameScene::onEvent));

	//subscribe to Hidden Event from GameMenu
	//GameMenu::instance->addEventListener(GameScene::HiddenEvent::EVENT, CLOSURE(this, &GameScene::onEvent));
}

void GameScene::onEvent(Event* ev)
{
	string id = ev->currentTarget->getName();

	if (id == "pause")
	{
		//menu button clicked
		//pause game by pausing it's clock
		if (_game->getClock()->getPauseCounter() == 0)
			_game->getClock()->pause();
		else
			_game->getClock()->resume();

		pause_button->setResAnim(_game->getClock()->getPauseCounter() == 0 ? res::ui.getResAnim("pause_button") : res::ui.getResAnim("pause_button_a"));
	}

	if (id == "retry")
	{
		spGameScene newGame = new GameScene();
		changeScene(newGame);
		GameScene::instance = newGame;
	}

	if (id == "home")
	{
		changeScene(MainMenuScene::instance);
	}

	/*
	if (ev->type == GameScene::HiddenEvent::EVENT)
	{
		//event from GameMenu called after GameMenu::instance->hide()
		const string& name = GameMenu::instance->getLastClicked();
		if (name == "Exit")
		{
			//if "Exit" button was clicked
			changeScene(MainMenuScene::instance);
		}
		else
		{
			//"Continue" button was clicked
			//dialog already hidden
			//just resume Clock to continue game
			_game->getClock()->resume();
		}
	}
	*/
}