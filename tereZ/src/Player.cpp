#include "Player.h"
#include "GameSound.h"
#include "GameScene.h"
#include "res.h"

#include "SDL.h"
#include "SDL_keyboard.h"

#include <sstream>
#include "DebugActor.h"

Player::Player(b2World* world, const Vector2& pos, float scale): isDead(false), isWalking(false), frameTime(0.0f), currentFrame(0)
{
	animation = res::ui.getResAnim("waiting");
	this->setResAnim(animation);
	this->setAnchor(0.5f, 0.5f);
	this->setPosition(pos);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(pos.x / scale, pos.y / scale);

	b2Body* body = world->CreateBody(&bodyDef);
	body->SetFixedRotation(true);
	//b2MassData md;
	//md.mass = 10.0f;
	//md.center = b2Vec2(this->getWidth() / scale, this->getHeight() / scale);
	//log::messageln("%f %f", this->getWidth(), this->getHeight());
	//body->SetMassData(&md);

	this->setUserData(body);

	//b2PolygonShape shape;
	//shape.SetAsBox(this->getWidth() / 2.0f / scale, this->getHeight() / 2.0f / scale);
	b2CircleShape shape;
	shape.m_radius = getHeight() / 2.0f / scale;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;

	body->CreateFixture(&fixtureDef);
	body->SetUserData(this);
}

void Player::update(const UpdateState &us)
{
	Actor::update(us);
	const Uint8* data = SDL_GetKeyboardState(0);
	if (data[SDL_SCANCODE_RIGHT])
	{
		if (!isWalking && !isDead)
		{
			animation = res::ui.getResAnim("walking");
			currentFrame = 0;
			frameTime = 0.0f;
			isWalking = true;
			if (!said)
			{
				GameSound::play("voice");
				said = true;
			}
		}
	}
	else
	{
		if (isWalking && currentFrame == 0)
		{
			animation = res::ui.getResAnim("waiting");
			currentFrame = 0;
			frameTime = 0.0f;
			isWalking = false;
		}
	}

	if (!isDead)
	{
		b2Body* body = (b2Body *)this->getUserData();
		b2Vec2 vel = body->GetLinearVelocity();
		//body->ApplyForce(b2Vec2(0.0f, 50.0f), body->GetPosition(), true);
		if (isWalking)
		{
			vel.x = animation->getAttribute("speed").as_float() * this->getScaleX();
		}
		else
		{
			vel.x = 0;
		}
		body->SetLinearVelocity(vel);
	}

	float maxFrames = animation->getColumns();
	int framesPerSecond = animation->getAttribute("frames_per_second").as_int();
	float framesPerMilliSecond = framesPerSecond / 1000.0f;
	float animationDuration = maxFrames / framesPerMilliSecond;

	frameTime += us.dt;
	while (frameTime >= animationDuration)
	{
		frameTime -= animationDuration;
	}

	int newFrame = frameTime * framesPerMilliSecond;

	//std::ostringstream buff;
	//buff << us.dt;
	//DebugActor::instance->addDebugString(buff.str().c_str());
	if (currentFrame != newFrame && !isDead)
	{
		this->setAnimFrame(animation->getFrame(newFrame));
		currentFrame = newFrame;
	}
}

void Player::die()
{
	if (!this->isDead)
	{
		this->isDead = true;
		int type = 123;
		Event event(type);
		GameScene::instance->getView()->dispatchEvent(&event);
	}
}

void Player::win()
{
	int type = 124;
	Event event(type);
	GameScene::instance->getView()->dispatchEvent(&event);
}
