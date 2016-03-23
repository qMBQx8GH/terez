#include "GameSound.h"

namespace GameSound
{
	SoundPlayer player;
	Resources *res;
	bool _muted;

	void init(Resources *a_res)
	{
		_muted = false;

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
		if (!_muted)
		{
			player.play(res->get(name), PlayOptions().loop());
		}
	}

	void play(char *name)
	{
		if (!_muted)
		{
			player.play(res->get(name));
		}
	}

	void mute()
	{
		_muted = true;
		player.pause();
	}

	void unmute()
	{
		_muted = false;
		player.resume();
	}

	bool isMuted()
	{
		return _muted;
	}
}