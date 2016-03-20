#pragma once
#include "oxygine-framework.h"
#include "Player.h"
#include "Door.h"
using namespace oxygine;

DECLARE_SMART(Game, spGame);

class Game: public Actor
{
public:
    Game();
    ~Game();

    void init();

protected:
    friend class Door;
    friend class Player;

	void onEvent(Event* ev);
    void doUpdate(const UpdateState& us);

    spActor _ui;
	spSprite _office;
    spPlayer _player;

	typedef std::list<spDoor> doors;
	doors _doors;
	doors::iterator cDoor;
};