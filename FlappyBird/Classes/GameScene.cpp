#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    scene->getPhysicsWorld()->setGravity( Vec2( 0, 0 ) );

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_score = 0;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("iphonehd/Background.png");
    backgroundSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    this->addChild( backgroundSprite );

    //
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    edgeBody->setContactTestBitmask( true );

    auto edgeNode = Node::create();
    edgeNode->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );

    this->addChild(edgeNode);

    this->schedule( schedule_selector( GameScene::SpawnPipe ), PIPE_SPAWN_FREQUENCY * visibleSize.width );

    m_bird = new Bird( this );

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( contactListener, this );

    auto touchListener = EventListenerKeyboard::create();
    touchListener->onKeyPressed = CC_CALLBACK_2( GameScene::onKeyPressed, this );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( touchListener, this );

    __String *strScore = __String::createWithFormat("%i", m_score);
    m_scoreLabel = Label::createWithTTF(strScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);

    m_scoreLabel->setColor(Color3B::MAGENTA);
    m_scoreLabel->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y) );

    this->addChild(m_scoreLabel, 1000);

    this->scheduleUpdate();

    return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    m_bird->Fly();

    this->scheduleOnce( schedule_selector( GameScene::stopFlying ), BIRD_FLY_DURATION );
}

void GameScene::SpawnPipe( float dt ) {
    m_pipe.SpawnPipe( this );
}

void GameScene::setPhysicsWorld( cocos2d::PhysicsWorld *world) {
    m_sceneWorld = world;
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact ) {

    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((BIRD_COLLISION_BITMASK  == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) ||
        ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Hit.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();

        auto scene = GameOverScene::createScene(m_score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene) );
    }
    else if ((BIRD_COLLISION_BITMASK  == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) ||
             ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask() ) )
     {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Point.mp3");
         m_score++;
         // Update label with score
         __String *strScore = __String::createWithFormat("%i", m_score);
         m_scoreLabel->setString(strScore->getCString());

         if (m_score % 5 == 0) {
             CocosDenshion::SimpleAudioEngine::end();
             CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Wing.mp3");
             CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Hit.mp3");
             CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Point.mp3");
         }
     }

    return true;
}

void GameScene::stopFlying( float dt ) {
    m_bird->StopFlying();
}

void GameScene::update( float dt ) {
    m_bird->Fall();
}


