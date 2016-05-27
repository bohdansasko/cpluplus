#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Bird
{
public:
        Bird(cocos2d::Layer *layer);

        void Fall();
        void Fly();
        void StopFlying() {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Wing.mp3");
            m_isFalling = true;
        }

private:
    cocos2d::Size m_visibleSize;
    cocos2d::Vec2 m_origin;

    cocos2d::Sprite *flappyBird;

    bool m_isFalling;


};

#endif // __BIRD_H__
