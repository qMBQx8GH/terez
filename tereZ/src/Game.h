#pragma once
#include "oxygine-framework.h"
#include "Box2D/Box2D.h"
#include "Player.h"
#include "Trap.h"
using namespace oxygine;

DECLARE_SMART(Game, spGame);

class Game: public Actor
{
public:
    Game();
    ~Game();

    void init();
	float _scale = 1.0f;
	b2World* _world;

protected:
    friend class Trap;
    friend class Player;

	void onEvent(Event* ev);
    void doUpdate(const UpdateState& us);

    spActor _ui;
	spSprite _office;
    spPlayer _player;

	typedef std::list<spTrap> traps;
	traps _traps;
};