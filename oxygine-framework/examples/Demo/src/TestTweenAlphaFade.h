#pragma once
#include "test.h"
#include "TweenAlphaFade.h"
#undef OUT


class TestTweenAlphaFade : public Test
{
public:
    spActor _test;
    TestTweenAlphaFade()
    {
        spSprite sprite = new Sprite;
        //Vector2 pos(0, 0);
        //sprite->setPosition(pos);
        sprite->setResAnim(resources.getResAnim("t2p"));
        sprite->attachTo(content);
        //float scale = 1.0f / getStage()->getScaleX();
        //sprite->setScale(scale);
        //Vector2 displaySpriteSize = sprite->getSize() * scale;
        //sprite->setPosition((content->getSize() - displaySpriteSize) / 2.0f);
        //*/

        sprite->setPosition(100.8f, 100.5f);
        sprite->setScale(1.5f);
        sprite->setAnchor(0.5f, 0.5f);
        sprite->setRotationDegrees(45);
        sprite->addEventListener(TouchEvent::CLICK,
                                 CLOSURE(this, &TestTweenAlphaFade::onClick));

        spSprite child = new Sprite;
        //child->attachTo(sprite);
        child->setScale(1.0f / 1.5f);
        child->setResAnim(resources.getResAnim("t2p"));


        //sprite->addTween(Actor::TweenX(0), 10000, -1, true);
        sprite->addTween(TweenAnim(resources.getResAnim("anim")), 500, -1);
        _test = sprite;
    }

    void onClick(Event*)
    {
        _test->addTween(TweenAlphaFade(false, false), 5500, 1, true);
    }

    void clicked(string id)
    {
        //   _test->addTween(TweenFade(), 1500);
    }
};