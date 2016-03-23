#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(Player, spPlayer);
class Player : public Actor
{
public:
	Player();
	void update(const UpdateState &us);
	void onDead(Event *a_event);
	void die(float door_x, float door_width, float depth);
	void win();

protected:
	spSprite sprite;
	int currentFrame;
	float frameTime;
	ResAnim *animation;
	bool isDead = false;
	bool isWalking = false;
};