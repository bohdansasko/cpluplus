#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();

    virtual bool init();
       
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    inline void setPhysicsWorld( cocos2d::PhysicsWorld *world);

    void SpawnPipe( float dt );

    bool onContactBegin(cocos2d::PhysicsContact &contact );

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void stopFlying(float dt);

    void update(float dt);

private:
    cocos2d::PhysicsWorld *m_sceneWorld;

    Pipe m_pipe;

    Bird *m_bird;

    unsigned int m_score;

    cocos2d::Label *m_scoreLabel;

};

#endif // __GAME_SCENE_H__
