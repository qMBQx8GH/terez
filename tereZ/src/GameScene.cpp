#include "GameScene.h"
#include "MainMenuScene.h"
#include "EndScene.h"
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

	pause_button = initActor(new MyButton(res::ui.getResAnim("pause_button"), res::ui.getResAnim("pause_button_a")),
		arg_name = "pause",
		arg_scale2 = _game->getScale(),
		arg_attachTo = _view);
	pause_button->setX(_game->getWidth() - _game->getScaleX() * pause_button->getWidth() * 1.0f);
	pause_button->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &GameScene::onEvent));

	btn = initActor(new MyButton(res::ui.getResAnim("retry_button") , res::ui.getResAnim("retry_button_a")),
		arg_name = "retry",
		arg_scale2 = _game->getScale(),
		arg_attachTo = _view);
	btn->setX(_game->getWidth() - _game->getScaleX() * btn->getWidth() * 2.0f);
	btn->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &GameScene::onEvent));

	btn = initActor(new MyButton(res::ui.getResAnim("home_button"), res::ui.getResAnim("home_button_a")),
		arg_name = "home",
		arg_scale2 = _game->getScale(),
		arg_attachTo = _view);
	btn->setX(_game->getWidth() - _game->getScaleX() * btn->getWidth() * 3.0f);
	btn->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &GameScene::onEvent));

	_view->addEventListener(123, CLOSURE(this, &GameScene::onEvent));
	_view->addEventListener(124, CLOSURE(this, &GameScene::onEvent));
#if _DEBUG
	_debugDraw = new Box2DDraw;
	_debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	_debugDraw->attachTo(this->_view);
	_debugDraw->setWorld(this->_game->_scale * this->_game->getScaleX(), this->_game->_world);
	_debugDraw->setPriority(1);
#endif
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
		pause_button->setPressedState(_game->getClock()->getPauseCounter() != 0);
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

	if (ev->type == 123)
	{
		EndScene::instance = new EndScene(0);
		changeScene(EndScene::instance);
	}

	if (ev->type == 124)
	{
		EndScene::instance = new EndScene(3);
		changeScene(EndScene::instance);
	}
}
