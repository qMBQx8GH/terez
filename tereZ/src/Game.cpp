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

	this->_scale = level->getAttribute("scale").as_float();
	this->_world = new b2World(b2Vec2(0.0f, 9.8f));

	//create separate layer for elements virtual joystick and other UI in future
    _ui = new Actor;
    _ui->attachTo(this);
    //it would be higher than other actors with default priority = 0
    _ui->setPriority(1);

	for (pugi::xml_node t : level->getNode().children("player"))
	{
		_player = new Player(
			_world,
			Vector2(t.attribute("position-x").as_float(), t.attribute("position-y").as_float()),
			_scale
		);
		_player->attachTo(this);
		break;
	}

	for (pugi::xml_node t : level->getNode().children("tile"))
	{
		spSprite tile = initActor(new Sprite,
			arg_resAnim = res::ui.getResAnim(t.attribute("image").as_string()),
			arg_anchor = Vector2(0.5f, 0.5f),
			arg_position = Vector2(t.attribute("position-x").as_float(), t.attribute("position-y").as_float()),
			arg_attachTo = this);

		b2BodyDef groundBodyDef;
		groundBodyDef.position = b2Vec2(tile->getX() / _scale, tile->getY() / _scale);

		b2Body* groundBody = _world->CreateBody(&groundBodyDef);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(tile->getWidth() / 2.0f / _scale, tile->getHeight() / 2.0f / _scale);
		groundBody->CreateFixture(&groundBox, 0.0f);
	}

	spTrap door;
	for (pugi::xml_node t : level->getNode().children("trap"))
	{
		door = new Trap(
			t.attribute("sprite-open").as_string(),
			_world,
			Vector2(t.attribute("position-x").as_float(), t.attribute("position-y").as_float()),
			_scale,
			res::ui.getResAnim(t.attribute("sprite-open").as_string()),
			res::ui.getResAnim(t.attribute("sprite-close").as_string())
			);
		door->attachTo(this);

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
	_world->Step(us.dt / 1000.0f, 6, 2);
	//update each body position on display
	b2Body* body = _world->GetBodyList();
	while (body)
	{
		Actor* actor = (Actor*)body->GetUserData();
		b2Body* next = body->GetNext();
		if (actor)
		{
			const b2Vec2& pos = body->GetPosition();
			actor->setPosition(Vector2(pos.x * _scale, pos.y * _scale));
			actor->setRotation(body->GetAngle());

			//remove fallen bodies
			if (actor->getY() > _office->getHeight() + 200)
			{
				body->SetUserData(0);
				_world->DestroyBody(body);
				_player->die();
			}
		}

		body = next;
	}

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
			//_player->die(trap->getX(), trap->getWidth(), _office->getHeight());
			break;
		}
	}
}
