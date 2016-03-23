#include "EndScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "MyButton.h"
#include "res.h"
#include <stdlib.h>

using namespace std;

spEndScene EndScene::instance;

EndScene::EndScene(int stars)
{
	//create background
	spSprite office = new Sprite;
	office->setResAnim(res::ui.getResAnim("office"));
	float hScale = _view->getWidth() / office->getWidth();
	office->setScaleX(hScale);
	float vScale = _view->getHeight() / office->getHeight();
	office->setScaleY(vScale);
	office->attachTo(_view);

	spActor btn = 0;

	btn = initActor(new MyButton(res::ui.getResAnim("home_button"), res::ui.getResAnim("home_button_a")),
		arg_name = "home",
		arg_anchor = Vector2(1.0f, 0.0f),
		arg_position = Vector2(office->getWidth() / 2.0f, office->getHeight() / 2.0f),
		arg_attachTo = office);
	btn->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &EndScene::onEvent));

	btn = initActor(new MyButton(res::ui.getResAnim("retry_button"), res::ui.getResAnim("retry_button_a")),
		arg_name = "retry",
		arg_anchor = Vector2(0.0f, 0.0f),
		arg_position = Vector2(office->getWidth() / 2.0f, office->getHeight() / 2.0f),
		arg_attachTo = office);
	btn->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &EndScene::onEvent));

	btn = initActor(new MyButton(res::ui.getResAnim(stars > 0? "star_button_a": "star_button"), 0),
		arg_name = "star1",
		arg_anchor = Vector2(1.0f, 1.0f),
		arg_position = Vector2(office->getWidth() / 2.0f, office->getHeight() / 2.0f),
		arg_attachTo = office);
	btn = initActor(new MyButton(res::ui.getResAnim(stars > 1 ? "star_button_a" : "star_button"), 0),
		arg_name = "star2",
		arg_anchor = Vector2(0.5f, 1.0f),
		arg_position = Vector2(office->getWidth() / 2.0f, office->getHeight() / 2.0f),
		arg_attachTo = office);
	btn = initActor(new MyButton(res::ui.getResAnim(stars > 2 ? "star_button_a" : "star_button"), 0),
		arg_name = "star3",
		arg_anchor = Vector2(0.0f, 1.0f),
		arg_position = Vector2(office->getWidth() / 2.0f, office->getHeight() / 2.0f),
		arg_attachTo = office);

}

void EndScene::onEvent(Event* ev)
{
	string id = ev->currentTarget->getName();

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
}