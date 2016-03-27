#pragma once
#include "oxygine-framework.h"
#include "Box2D/Box2D.h"

using namespace oxygine;

DECLARE_SMART(Player, spPlayer);
class Player : public Sprite
{
public:
	Player(b2World* world, const Vector2& pos, float scale);
	void update(const UpdateState &us);
	void die();
	void win();

protected:

	int currentFrame;
	float frameTime;
	ResAnim *animation;
	bool isDead = false;
	bool isWalking = false;
	bool said = false;
};