#include "GameSound.h"

namespace GameSound
{
	SoundPlayer player;
	Resources *res;

	void init(Resources *a_res)
	{
		res = a_res;
		SoundSystem::create()->init(16);

		//initialize SoundPlayer
		SoundPlayer::initialize();
		player.setResources(res);
	}

	void update()
	{
		SoundSystem::instance->update();
		player.update();
	}

	void free()
	{
	}

	void playBackground(char *name)
	{
		player.play(res->get(name), PlayOptions().loop());
	}
}