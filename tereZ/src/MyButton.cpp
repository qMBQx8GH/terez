#include "MyButton.h"

MyButton::MyButton()
{
    //pressed button should be RED
    addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &MyButton::onEvent));
    addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &MyButton::onEvent));
    addEventListener(TouchEvent::CLICK, CLOSURE(this, &MyButton::onEvent));
}

void MyButton::onEvent(Event* ev)
{
    TouchEvent* event = static_cast<TouchEvent*>(ev);

	if (ev->type == TouchEvent::TOUCH_DOWN)
	{
		addTween(Actor::TweenScale(0.95f), 300, 1, false);
	}

	if (ev->type == TouchEvent::TOUCH_UP)
	{
		addTween(Actor::TweenScale(1.0f), 300, 1, false);
	}

}