#include "Pipe.h"
#include "Definitions.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;

Pipe::Pipe() {
    m_visibleSize = Director::getInstance()->getVisibleSize();
    m_origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(Layer *layer) {
//    CCLOG( "SPAWN PIPE" );
    log( "SPAWN PIPE" );
    auto topPipe = Sprite::create( "iphonehd/Pipe.png" );
    auto bottomPipe = Sprite::create( "iphonehd/Pipe.png" );

    auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize() );
    auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize() );

    auto random = CCRANDOM_0_1();
    if ( random < LOWER_SCREEN_PIPE_THRESHOLD )
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    else if ( random > UPPER_SCREEN_PIPE_THRESHOLD )
        random = UPPER_SCREEN_PIPE_THRESHOLD;

    auto topPipePosition = ( random * m_visibleSize.width ) + ( topPipe->getContentSize().height / 2 );

    topPipeBody->setDynamic( false );
    bottomPipeBody->setDynamic( false );

    topPipeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    bottomPipeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );

    topPipeBody->setContactTestBitmask( true );
    bottomPipeBody->setContactTestBitmask( true );

    topPipe->setPhysicsBody( topPipeBody );
    bottomPipe->setPhysicsBody( bottomPipeBody );

    topPipe->setPosition( Vec2( m_visibleSize.width + topPipe->getContentSize().width + m_origin.x
                        /*+ CCRANDOM_MINUS1_1() * 250*/, topPipePosition ) );

    bottomPipe->setPosition( Vec2( topPipe->getPositionX(), topPipePosition - ( Sprite::create( "iphonehd/Ball.png" )->getContentSize().height * PIPE_GAP )
                                   - topPipe->getContentSize().height ) );

    layer->addChild( topPipe );
    layer->addChild( bottomPipe );

    auto topPipeAction    = MoveBy::create(PIPE_MOVEMENT_SPEED * m_visibleSize.width, Vec2( -m_visibleSize.width * 1.5, 0 ) );
    auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * m_visibleSize.width, Vec2( -m_visibleSize.width * 1.5, 0 ) );

    topPipe->runAction   ( topPipeAction );
    bottomPipe->runAction( bottomPipeAction );

    auto pointNode = Node::create();
    auto pointBody = PhysicsBody::createBox( Size(1, Sprite::create("iphonehd/Ball.png")->getContentSize().height * PIPE_GAP));

    pointBody->setDynamic(false);
    pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
    pointBody->setContactTestBitmask(true);

    pointNode->setPhysicsBody(pointBody);
    pointNode->setPosition(Vec2(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe->getContentSize().height / 2) - ((Sprite::create("iphonehd/Ball.png")->getContentSize().height * PIPE_GAP) / 2) ) );

    layer->addChild(pointNode);

    auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * m_visibleSize.width, Vec2( -m_visibleSize.width * 1.5, 0 ) );

    pointNode->runAction(pointNodeAction);
}
