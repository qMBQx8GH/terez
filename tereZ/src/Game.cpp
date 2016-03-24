#include "Game.h"
#include "Player.h"
#include "res.h"
#include "LevelRes.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
    //scene layer would have size of display
    setSize(getStage()->getSize());

	LevelRes* level = safeCast<LevelRes*>(res::ui.get("level1"));
	level->load();

	//create background
	for (pugi::xml_node t : level->getNode().children("background"))
	{
		_office = new Sprite;
		_office->setResAnim(res::ui.getResAnim(t.attribute("image").as_string()));
		_office->attachTo(this);
		break;
	}
	
	float hScale = this->getWidth() / _office->getWidth();
	this->setScaleX(hScale);
	float vScale = this->getHeight() / _office->getHeight();
	this->setScaleY(vScale);
	
	//create separate layer for elements virtual joystick and other UI in future
    _ui = new Actor;
    _ui->attachTo(this);
    //it would be higher than other actors with default priority = 0
    _ui->setPriority(1);

	for (pugi::xml_node t : level->getNode().children("player"))
	{
		_player = new Player();
		_player->setPosition(Vector2(t.attribute("position-x").as_float(), t.attribute("position-y").as_float()));
		_player->attachTo(this);
		break;
	}

	for (pugi::xml_node t : level->getNode().children("tile"))
	{
		spSprite tile = initActor(new Sprite,
			arg_resAnim = res::ui.getResAnim(t.attribute("image").as_string()),
			arg_position = Vector2(t.attribute("position-x").as_float(), t.attribute("position-y").as_float()),
			arg_attachTo = this);
	}

	spSprite floor_left = initActor(new Sprite,
		arg_resAnim = res::ui.getResAnim("floor_tile"),
		arg_position = Vector2(0.0f, _office->getHeight() / 2.0f),
		arg_attachTo = this);

	float floor_width = floor_left->getWidth();
	float floor_height = floor_left->getHeight();

	spTrap door;
	for (pugi::xml_node t : level->getNode().children("trap"))
	{
		door = initActor(new Trap(
				res::ui.getResAnim(t.attribute("sprite-open").as_string()),
				res::ui.getResAnim(t.attribute("sprite-close").as_string())
			),
			arg_resAnim = res::ui.getResAnim(t.attribute("sprite-open").as_string()),
			arg_position = Vector2(t.attribute("position-x").as_float(), t.attribute("position-y").as_float()),
			arg_attachTo = this);
		door->startTimer(
			t.attribute("timer-offset").as_int(),
			t.attribute("timer-interval").as_int(),
			t.attribute("timer-open").as_int()
		);
		_traps.push_back(door);
	}
}

void Game::doUpdate(const UpdateState& us)
{
	if (_player->getX() >= _office->getWidth())
	{
		_player->win();
	}

	for (traps::iterator i = _traps.begin(); i != _traps.end(); i++)
	{
		spTrap trap = *i;
		if (
			trap->isOpen()
			&& _player->getX() > trap->getX()
			&& _player->getX() < (trap->getX() + trap->getWidth())
			)
		{
			_player->die(trap->getX(), trap->getWidth(), _office->getHeight());
			break;
		}
	}
}
