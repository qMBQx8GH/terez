#pragma once
#include "Scene.h"
#include "Player.h"

DECLARE_SMART(GameScene, spGameScene);
class GameScene: public Scene
{
public:
    static spGameScene instance;
    GameScene();


private:
    void onEvent(Event* ev);
    spPlayer zombie;
};
