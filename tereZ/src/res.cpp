#include "res.h"

class Level: public Resource
{
public:
	Level() {}
	~Level() {}
	static void initialize()
	{
		Resources::registerResourceType(&Level::createLevel, "level");
		log::messageln("initialize");
	}
	static void free()
	{
		Resources::unregisterResourceType("level");
	}
	static Resource* createLevel(CreateResourceContext& context)
	{
		Level* rs = new Level;
		rs->init(context);
		setNode(rs, context.walker.getNode());
		context.resources->add(rs);
		return rs;
	}
	bool init(CreateResourceContext& context)
	{
		std::string id = context.walker.getNode().attribute("id").as_string();
		this->setName(id);
		log::messageln("init:[%s]", id.c_str());
		return true;
	}
	void _load(LoadResourcesContext* context)
	{
		log::messageln("_load[%s]", this->getName().c_str());
	}
	void _unload()
	{
		//if (!_sound)
		//	return;
	}
	void load(LoadResourcesContext *context = 0)
	{
		log::messageln("load[%s]", this->getName().c_str());
		for (pugi::xml_node t = this->getNode().first_child(); t; t=t.next_sibling())
		{
			log::messageln("t.name:[%s]", t.name());
			int x = t.attribute("position-x").as_int();
			log::messageln("t.position-x:[%d]", x);
		}
	}
};


namespace res
{
	Resources ui;

	void load()
	{
		Level::initialize();
		ui.loadXML("xmls/ui.xml");
		Level* level = safeCast<Level*>(ui.get("level1"));
		level->load();

		for (pugi::xml_node t: level->getNode().children("trap"))
		{
			log::messageln("tttt.name:[%s]", t.name());
			int x = t.attribute("position-x").as_int();
			log::messageln("t.position-x:[%d]", x);
		}
	}

	void free()
	{
		Level::free();
		ui.free();
	}
}