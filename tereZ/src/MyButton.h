#pragma once
#include "Sprite.h"

using namespace oxygine;

DECLARE_SMART(MyButton, spMyButton);
class MyButton: public Actor
{
public:
	MyButton(const ResAnim *normal, const ResAnim *pressed);
	void setPressedState(bool pressed);
private:
	void onEvent(Event*);
	bool _pressed;
	spSprite _normalState;
	spSprite _pressedState;
};