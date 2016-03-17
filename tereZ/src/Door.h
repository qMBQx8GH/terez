#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(Door, spDoor);
class Door : public Actor
{
public:
	Door(float width, float height);
	void open();
	void close();
	bool isClosed();
protected:
	spSprite _left;
	spSprite _right;
	bool _closed;
};