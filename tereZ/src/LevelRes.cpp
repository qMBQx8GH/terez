#include "LevelRes.h"

using namespace oxygine;

LevelRes::LevelRes()
{
}

LevelRes::~LevelRes()
{
}

void LevelRes::initialize()
{
	Resources::registerResourceType(&LevelRes::createLevel, "level");
	log::messageln("initialize");
}

void LevelRes::free()
{
	Resources::unregisterResourceType("level");
}

Resource* LevelRes::createLevel(CreateResourceContext& context)
{
	LevelRes* rs = new LevelRes;
	rs->init(context);
	setNode(rs, context.walker.getNode());
	context.resources->add(rs);
	return rs;
}

bool LevelRes::init(CreateResourceContext& context)
{
	std::string id = context.walker.getNode().attribute("id").as_string();
	this->setName(id);
	log::messageln("init:[%s]", id.c_str());
	return true;
}

void LevelRes::_load(LoadResourcesContext* context)
{
	//log::messageln("_load[%s]", this->getName().c_str());
}

void LevelRes::_unload()
{
	//if (!_sound)
		//	return;
}

void LevelRes::load(LoadResourcesContext *context)
{
	log::messageln("load[%s]", this->getName().c_str());
	for (pugi::xml_node t = this->getNode().first_child(); t; t = t.next_sibling())
	{
		log::messageln("t.name:[%s]", t.name());
		int x = t.attribute("position-x").as_int();
		log::messageln("t.position-x:[%d]", x);
	}
}
