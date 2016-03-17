#include "GameScene.h"
#include "MainMenuScene.h"
#include "res.h"
#include "Player.h"
#include "Door.h"

spGameScene GameScene::instance;

GameScene::GameScene():cDoor(0)
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
		arg_scaleX = hScale,
		arg_scaleY = vScale,
		arg_position = Vector2(0.0f, _view->getHeight() / 2.0f),
		arg_attachTo = _view);

	float floor_width = floor_left->getWidth() * hScale;
	float floor_height = floor_left->getHeight() * vScale;
	floor_right = initActor(new Sprite,
		arg_resAnim = res::ui.getResAnim("floor_tile"),
		arg_scaleX = hScale,
		arg_scaleY = vScale,
		arg_position = Vector2(floor_width * 15, _view->getHeight() / 2.0f),
		arg_attachTo = _view);
	
	for (int i = 0; i < 7; i++)
	{
		doors[i] = new Door(floor_width, floor_height);
		doors[i]->setPosition(Vector2(floor_width * 2.0f + i * floor_width * 2.0f, _view->getHeight() / 2.0f));
		doors[i]->setScaleX(hScale);
		doors[i]->setScaleY(vScale);
		doors[i]->attachTo(_view);
	}
	
    //handle click to menu
    office->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameScene::onEvent));
}
void GameScene::onEvent(Event* ev)
{
	if (doors[this->cDoor]->isClosed())
		doors[this->cDoor]->open();
	else
		doors[this->cDoor]->close();

	this->cDoor++;
	if (this->cDoor >= 7)
		this->cDoor = 0;
}
