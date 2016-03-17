#include "GameScene.h"
#include "MainMenuScene.h"
#include "res.h"
#include "Player.h"

spGameScene GameScene::instance;

GameScene::GameScene()
{
	//create background
	spSprite office = new Sprite;
	office->setResAnim(res::ui.getResAnim("office"));
	float hScale = _view->getWidth() / office->getWidth();
	office->setScaleX(hScale);
	float vScale = _view->getHeight() / office->getHeight();
	office->setScaleY(vScale);
	office->attachTo(_view);

	zombie = new Player();
	zombie->setPosition(Vector2(zombie->getWidth() / 2.0f, _view->getHeight() / 2.0f));
	zombie->setScaleX(hScale);
	zombie->setScaleY(vScale);
	zombie->attachTo(_view);

	floor_left = initActor(new Sprite,
		arg_resAnim = res::ui.getResAnim("floor_tile"),
		arg_anchor = Vector2(0.0f, 0.0f),
		arg_scaleX = hScale,
		arg_scaleY = vScale,
		arg_position = Vector2(0.0f, _view->getHeight() / 2.0f),
		arg_attachTo = _view);

	float floor_width = floor_left->getWidth() * hScale;
	float floor_height = floor_left->getHeight() * vScale;
	floor_right = initActor(new Sprite,
		arg_resAnim = res::ui.getResAnim("floor_tile"),
		arg_anchor = Vector2(0.0f, 0.0f),
		arg_scaleX = hScale,
		arg_scaleY = vScale,
		arg_position = Vector2(floor_width * 15, _view->getHeight() / 2.0f),
		arg_attachTo = _view);
	
	for (int i = 0; i < 7; i++)
	{
		left_doors[i] = initActor(new Sprite,
			arg_resAnim = res::ui.getResAnim("floor_tile"),
			arg_scaleX = hScale,
			arg_scaleY = vScale,
			arg_anchor = Vector2(0.0f, 1.0f),
			arg_position = Vector2(floor_width + floor_width * i * 2, _view->getHeight() / 2.0f + floor_height),
			arg_attachTo = _view);
		right_doors[i] = initActor(new Sprite,
			arg_resAnim = res::ui.getResAnim("floor_tile"),
			arg_scaleX = hScale,
			arg_scaleY = vScale,
			arg_anchor = Vector2(1.0f, 1.0f),
			arg_position = Vector2(floor_width * 3 + floor_width * i * 2, _view->getHeight() / 2.0f + floor_height),
			arg_attachTo = _view);
	}
	
    //handle click to menu
    office->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameScene::onEvent));

    //floor_left = new Sprite;
	//floor_left->setResAnim(res::ui.getResAnim("floor_tile"));
	//floor_left->setScaleX(hScale);
	//floor_left->setScaleY(vScale);
	//floor_left->attachTo(_view);
}

void GameScene::onEvent(Event* ev)
{
	left_doors[this->cDoor]->setRotation(left_doors[this->cDoor]->getRotation() + 0.1f);
	spTween tween = left_doors[this->cDoor]->addTween(
		Actor::TweenRotation(MATH_PI / 2.0f),
		250,
		1,
		false,
		0,
		Tween::ease_inSin
	);
	tween = right_doors[this->cDoor]->addTween(
		Actor::TweenRotation(-MATH_PI / 2.0f),
		250,
		1,
		false,
		0,
		Tween::ease_inSin
	);
	//right_doors[0]->setRotation(right_doors[0]->getRotation() - 0.1f);
	this->cDoor++;
}
