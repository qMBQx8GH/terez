#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(Trap, spTrap);
class Trap : public Sprite
{
public:
	Trap(ResAnim *resOpen, ResAnim *resClose);
	void update(const UpdateState &us);
	void startTimer(int offset, int interval, int open);
	void open();
	void close();
	bool isOpen();
	bool isClosed();
protected:
	ResAnim *_open;
	ResAnim *_close;
	bool _closed;
	timeMS _timer_start;
	timeMS _timer_offset;
	timeMS _timer_interval;
	timeMS _timer_open;
};