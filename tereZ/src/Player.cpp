#include "Player.h"
#include "res.h"

#include "SDL.h"
#include "SDL_keyboard.h"

#include <sstream>
#include "DebugActor.h"

Player::Player(): isDead(false), isWalking(false), frameTime(0.0f), currentFrame(0)
{
	animation = res::ui.getResAnim("waiting");

	sprite = new Sprite;
	sprite->setResAnim(animation);
	sprite->attachTo(this);

	this->setSize(sprite->getSize());
	this->setAnchor(0.5f, 1.0f);
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

	if (isWalking && !isDead)
	{
		Vector2 pos = getPosition();
		pos.x += animation->getAttribute("speed").as_float() * this->getScaleX();
		setPosition(pos);
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
		sprite->setAnimFrame(animation->getFrame(newFrame));
		currentFrame = newFrame;
	}
}

void Player::die(float door_x, float door_width, float depth)
{
	if (!this->isDead)
	{
		this->isDead = true;
		//this->detach();
		spTween tween = this->addTween(Actor::TweenPosition(door_x + door_width / 2.0f, depth + this->getHeight()), 2000);
	}
}