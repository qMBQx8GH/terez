#include "Game.h"
#include "Player.h"
#include "res.h"

#include <sstream>
#include "DebugActor.h"

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

    //create background
    _office = new Sprite;
	_office->setResAnim(res::ui.getResAnim("office"));
	_office->attachTo(this);

	float hScale = this->getWidth() / _office->getWidth();
	this->setScaleX(hScale);
	float vScale = this->getHeight() / _office->getHeight();
	this->setScaleY(vScale);
	
	//create separate layer for elements virtual joystick and other UI in future
    _ui = new Actor;
    _ui->attachTo(this);
    //it would be higher than other actors with default priority = 0
    _ui->setPriority(1);

	_player = new Player();
	_player->setPosition(Vector2(_player->getWidth() / 2.0f, _office->getHeight() / 2.0f));
	_player->attachTo(this);

	spSprite floor_left = initActor(new Sprite,
		arg_resAnim = res::ui.getResAnim("floor_tile"),
		arg_position = Vector2(0.0f, _office->getHeight() / 2.0f),
		arg_attachTo = this);

	float floor_width = floor_left->getWidth();
	float floor_height = floor_left->getHeight();

	spSprite floor_right = initActor(new Sprite,
		arg_resAnim = res::ui.getResAnim("floor_tile"),
		arg_position = Vector2(floor_width * 15, _office->getHeight() / 2.0f),
		arg_attachTo = this);

	spDoor door;
	for (int i = 0; i < 7; i++)
	{
		door = initActor(new Door(),
			arg_position = Vector2(floor_width + i * floor_width * 2.0f, _office->getHeight() / 2.0f),
			arg_attachTo = this);
		door->startTimer(1 + 7000 * i, 16000, 7000);
		_doors.push_back(door);
	}
	cDoor = _doors.begin();
}

void Game::doUpdate(const UpdateState& us)
{
	//std::ostringstream buff;
	//buff << _player->getX() << "; " << (*cDoor)->getX() << "; " << (*cDoor)->getWidth();
	//DebugActor::instance->addDebugString(buff.str().c_str());

	if (_player->getX() >= _office->getWidth())
	{
		_player->win();
	}

	for (doors::iterator i = _doors.begin(); i != _doors.end(); i++)
	{
		spDoor door = *i;
		if (
			door->isOpen()
			&& _player->getX() > door->getX()
			&& _player->getX() < (door->getX() + door->getWidth())
			)
		{
			_player->die(door->getX(), door->getWidth(), _office->getHeight());
			break;
		}
	}
}
