#pragma once
#include "oxygine-framework.h"
#include "Scene.h"

DECLARE_SMART(MainMenuScene, spMainMenuScene);
class MainMenuScene: public Scene
{
public:
    static spMainMenuScene instance;

    MainMenuScene(Resources* res);

private:
    void onEvent(Event* ev);
};