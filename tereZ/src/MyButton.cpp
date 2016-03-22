#include "MyButton.h"
#include "res.h"

MyButton::MyButton(const ResAnim *normal, const ResAnim *pressed):_pressed(false)
{
	this->_normalState = 0;
	if (normal != 0)
	{
		this->_normalState = initActor(new Sprite());
		this->_normalState->setResAnim(normal),
		this->_normalState->setAlpha(255);
		this->_normalState->attachTo(this);
		this->setSize(this->_normalState->getSize());
	}

	this->_pressedState = 0;
	if (pressed != 0)
	{
		this->_pressedState = initActor(new Sprite());
		this->_pressedState->setResAnim(pressed),
		this->_pressedState->setAlpha(0);
		this->_pressedState->attachTo(this);
		this->setSize(this->_pressedState->getSize());
	}

	this->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &MyButton::onEvent));
	this->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &MyButton::onEvent));
}

void MyButton::setPressedState(bool pressed)
{
	this->_pressed = pressed;
}

void MyButton::onEvent(Event* ev)
{
	TouchEvent* event = static_cast<TouchEvent*>(ev);

	if (this->_normalState)
	{
		if (
			(ev->type == TouchEvent::TOUCH_DOWN && !this->_pressed)
			|| (ev->type == TouchEvent::TOUCH_UP && this->_pressed)
		)
		{
			this->_normalState->addTween(Actor::TweenAlpha(0), 300);
		}
		else if (
			(ev->type == TouchEvent::TOUCH_DOWN && this->_pressed)
			|| (ev->type == TouchEvent::TOUCH_UP && !this->_pressed)
		)
		{
			this->_normalState->addTween(Actor::TweenAlpha(255), 300);
		}
	}

	if (this->_pressedState)
	{
		if (
			(ev->type == TouchEvent::TOUCH_DOWN && !this->_pressed)
			||(ev->type == TouchEvent::TOUCH_UP && this->_pressed)
		)
		{
			this->_pressedState->addTween(Actor::TweenAlpha(255), 300);
		}
		else if (
			(ev->type == TouchEvent::TOUCH_DOWN && this->_pressed)
			|| (ev->type == TouchEvent::TOUCH_UP && !this->_pressed)
		)
		{
			this->_pressedState->addTween(Actor::TweenAlpha(0), 300);
		}
	}
}