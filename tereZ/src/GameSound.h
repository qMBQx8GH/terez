#pragma once
#include "oxygine-framework.h"
#include "SoundPlayer.h"
#include "SoundSystem.h"
#include "SoundInstance.h"

using namespace oxygine;

namespace GameSound
{
	void init(Resources *res);
	void update();
	void free();

	void playBackground(char *name);
}