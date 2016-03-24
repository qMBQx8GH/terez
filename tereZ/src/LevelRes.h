#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

class LevelRes : public Resource
{
public:
	LevelRes();
	~LevelRes();
	static void initialize();
	static void free();
	static Resource* createLevel(CreateResourceContext& context);
	bool init(CreateResourceContext& context);
	void _load(LoadResourcesContext* context);
	void _unload();
	void load(LoadResourcesContext *context = 0);
};

