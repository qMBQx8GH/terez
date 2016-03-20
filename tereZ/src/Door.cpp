#include "Door.h"
#include "res.h"


Door::Door(): _closed(true)
{
	_left = new Sprite;
	_left->setResAnim(res::ui.getResAnim("floor_tile"));
	_left->setPosition(Vector2(0, _left->getHeight()));
	_left->setAnchor(Vector2(0.0f, 1.0f));
	_left->attachTo(this);

	_right = new Sprite;
	_right->setResAnim(res::ui.getResAnim("floor_tile"));
	_right->setPosition(Vector2(_left->getWidth() + _right->getWidth(), _right->getHeight()));
	_right->setAnchor(Vector2(1.0f, 1.0f));
	_right->attachTo(this);

	this->setSize(_left->getWidth() + _right->getWidth(), _left->getHeight());
}

void Door::open()
{
	this->_closed = false;
	_left->addTween(
		Actor::TweenRotation(MATH_PI / 2.0f),
		250,
		1,
		false,
		0,
		Tween::ease_inSin
	);
	_right->addTween(
		Actor::TweenRotation(-MATH_PI / 2.0f),
		250,
		1,
		false,
		0,
		Tween::ease_inSin
	);
}

void Door::close()
{
	this->_closed = true;
	_left->addTween(
		Actor::TweenRotation(0.0f),
		250,
		1,
		false,
		0,
		Tween::ease_inSin
	);
	_right->addTween(
		Actor::TweenRotation(0.0f),
		250,
		1,
		false,
		0,
		Tween::ease_inSin
	);
}

bool Door::isClosed()
{
	return this->_closed;
}

bool Door::isOpen()
{
	return !this->_closed;
}