#include "MainMenuScene.h"
#include "Sprite.h"
#include "initActor.h"
#include "MyButton.h"

using namespace std;

spMainMenuScene MainMenuScene::instance;

MainMenuScene::MainMenuScene(Resources* res)
{
    //create background
    spSprite office = new Sprite;
	office->setResAnim(res->getResAnim("office"));
	office->setScaleX(_view->getWidth() / office->getWidth());
	office->setScaleY(_view->getHeight() / office->getHeight());
	office->attachTo(_view);

    /*
    'initActor' is syntax sugar for

    spSprite logo = new Sprite;
    logo->setResAnim(res::ui.getResAnim("logo2")),
    logo->attachTo(_view);
    */

    //create logo
    //spSprite logo = initActor(new Sprite,
    //                          arg_resAnim = res.getResAnim("logo2"),
    //                          arg_attachTo = _view);
    //logo->setPosition(_view->getSize() - logo->getSize());


	spSprite btn = 0;
	
    //create play button at center
    btn = initActor(new MyButton,
                             arg_name = "play",
                             arg_resAnim = res->getResAnim("start_button"),
                             arg_anchor = Vector2(0.5f, 1.5f),
                             arg_pos = _view->getSize() / 2,
                             arg_attachTo = _view);

    //handle click to button
    btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MainMenuScene::onEvent));

    //create menu button
    btn = initActor(new MyButton,
                    arg_name = "exit",
                    arg_resAnim = res->getResAnim("quit_button"),
                    arg_anchor = Vector2(0.5f, -0.5f),
					arg_pos = _view->getSize() / 2,
					arg_attachTo = _view);

    btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MainMenuScene::onEvent));
}

void MainMenuScene::onEvent(Event* ev)
{
    string id = ev->currentTarget->getName();
    if (id == "exit")
    {
        core::requestQuit();
    }

    if (id == "play")
    {
        //clicked to play button change scene
        ///TODO changeScene(GameScene::instance);
    }
}