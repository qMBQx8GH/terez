#include "oxygine-framework.h"

#include "core/STDFileSystem.h"

#include "test.h"
#include "TestSoundFormats.h"
#include "TestStress.h"
#include "TestCoord.h"
#ifdef __S3E__
#include "s3eKeyboard.h"
#endif


#include "SoundPlayer.h"
#include "SoundSystem.h"

using namespace oxygine;


//it is our resources
//in real project you would have more than one Resources declarations. It is important on mobile devices with limited memory and you would load/unload them
Resources resources;
SoundPlayer splayer;

class TestActor: public Test
{
public:

    TestActor()
    {
        _x = getStage()->getWidth() / 2.0f;
        _y = 0;


        addButton("sound_formats", "sound formats");
        addButton("stress_test", "stress test");
        addButton("test_coord", "test coord");
        addButton("exit", "exit");

        getStage()->addEventListener(Stage::ACTIVATE, CLOSURE(this, &TestActor::resume));
        getStage()->addEventListener(Stage::DEACTIVATE, CLOSURE(this, &TestActor::pause));
    }

    void pause(Event*)
    {
        SoundSystem::get()->pause();
    }

    void resume(Event*)
    {
        SoundSystem::get()->resume();
    }

    void clicked(string id)
    {
        setVisible(false);

        if (id == "sound_formats")
        {
            getStage()->addChild(new TestSoundFormats);
        }

        if (id == "stress_test")
        {
            getStage()->addChild(new TestStress);
        }

        if (id == "test_coord")
        {
            getStage()->addChild(new TestCoord);
        }

        if (id == "exit")
        {
            core::requestQuit();
        }
    }
};

void example_preinit()
{

}

void example_init()
{
    //initialize our sound system with 16 channels

    SoundSystem::create()->init(16);

    //initialize SoundPlayer
    SoundPlayer::initialize();
    splayer.setResources(&resources);

    //load xml file with resources definition
    resources.loadXML("xmls/res.xml");

    Test::init();

    Test::instance = new TestActor;
    getStage()->addChild(Test::instance);


#ifdef EMSCRIPTEN
    Resources::resources lst;
    resources.collect(lst);
    for (size_t i = 0; i < lst.size(); ++i)
    {
        ResSound* rs = dynamic_cast<ResSound*>(lst[i].get());
        if (!rs)
            continue;

        EM_ASM_ARGS(
        {
            var p = Preloading("hello");
            p.add(Pointer_stringify($0));
            p.start();
        }, rs->getPath().c_str());
    }

#endif
}

void example_update()
{
    SoundSystem::get()->update();
    splayer.update();
}

void example_destroy()
{
    splayer.stop();
    SoundPlayer::free();
    SoundSystem::free();

    resources.free();
    Test::free();
}


