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
}

void GameScene::onEvent(Event* ev)
{
}
