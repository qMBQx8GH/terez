#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(Door, spDoor);
class Door : public Actor
{
public:
	Door();
	void update(const UpdateState &us);
	void startTimer(int offset, int interval, int open);
	void open();
	void close();
	bool isOpen();
	bool isClosed();
protected:
	spSprite _left;
	spSprite _right;
	bool _closed;
	timeMS _timer_start;
	timeMS _timer_offset;
	timeMS _timer_interval;
	timeMS _timer_open;
};