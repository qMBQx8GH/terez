#include "GameMenu.h"
#include "res.h"
#include "Sprite.h"
#include "initActor.h"
#include "MyButton.h"
#include "MainMenuScene.h"
#include "GameScene.h"

using namespace std;

spGameMenu GameMenu::instance;

GameMenu::GameMenu()
{
	//create background
	spSprite office = new Sprite;
	office->setResAnim(res::ui.getResAnim("office"));
	office->setScaleX(_view->getWidth() / office->getWidth());
	office->setScaleY(_view->getHeight() / office->getHeight());
	office->attachTo(_view);

	spSprite btn = 0;

	//create play button at center
	btn = initActor(new MyButton,
		arg_name = "resume",
		arg_resAnim = res::ui.getResAnim("resume_button"),
		arg_anchor = Vector2(0.5f, 1.5f),
		arg_pos = _view->getSize() / 2,
		arg_attachTo = _view);

	//handle click to button
	btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameMenu::onEvent));

	//create menu button
	btn = initActor(new MyButton,
		arg_name = "menu",
		arg_resAnim = res::ui.getResAnim("menu_button"),
		arg_anchor = Vector2(0.5f, -0.5f),
		arg_pos = _view->getSize() / 2,
		arg_attachTo = _view);

	btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameMenu::onEvent));
}

void GameMenu::onEvent(Event* ev)
{
	string id = ev->currentTarget->getName();
	if (id == "resume")
	{
		changeScene(GameScene::instance);
		GameScene::instance->_game->getClock()->resume();
	}

	if (id == "menu")
	{
		//clicked to play button change scene
		changeScene(MainMenuScene::instance);
	}
}