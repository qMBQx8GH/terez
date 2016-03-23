#include "Door.h"
#include "res.h"


Door::Door(): _closed(true), _timer_start(0)
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

void Door::update(const UpdateState &us)
{
	Actor::update(us);
	if (this->_timer_start)
	{
		timeMS now = getTimeMS();
		timeMS passed = getTimeMS() - this->_timer_start;
		if (this->_timer_offset > 0)
		{
			if (passed > this->_timer_offset)
			{
				this->_timer_start = now;
				this->_timer_offset = 0;
				this->open();
			}
		}
		else if (this->isClosed() && (passed > this->_timer_interval))
		{
			this->_timer_start = now;
			this->open();
		}
		else if (this->isOpen() && (passed > this->_timer_open))
		{
			this->_timer_start = now;
			this->close();
		}
	}
}

void Door::startTimer(int offset, int interval, int open)
{
	this->_timer_offset = offset;
	this->_timer_interval = interval;
	this->_timer_open = open;
	this->_timer_start = getTimeMS();
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