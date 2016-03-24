#include "Trap.h"
#include "res.h"

Trap::Trap(ResAnim *resOpen, ResAnim *resClose): _closed(true), _timer_start(0)
{
	_open = resOpen;
	_close = resClose;
}

void Trap::update(const UpdateState &us)
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

void Trap::startTimer(int offset, int interval, int open)
{
	this->_timer_offset = offset;
	this->_timer_interval = interval;
	this->_timer_open = open;
	this->_timer_start = getTimeMS();
}

void Trap::open()
{
	this->_closed = false;
	this->addTween(TweenAnim(_open), _open->getNode().attribute("duration").as_int());
}

void Trap::close()
{
	this->_closed = true;
	this->addTween(TweenAnim(_close), _close->getNode().attribute("duration").as_int());
}

bool Trap::isClosed()
{
	return this->_closed;
}

bool Trap::isOpen()
{
	return !this->_closed;
}