#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(Player, spPlayer);
class Player : public Actor
{
public:
	Player();
	void attachTo(spActor parent);
	void update(const UpdateState &us);

protected:
	spSprite sprite;
	int currentFrame;
	float frameTime;
	ResAnim *animation;
	bool isWalking = false;
};