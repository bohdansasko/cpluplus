#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird( cocos2d::Layer *layer ) {
    m_isFalling = true;

    m_visibleSize = Director::getInstance()->getVisibleSize();
    m_origin = Director::getInstance()->getVisibleOrigin();

    flappyBird = Sprite::create( "iphonehd/Ball.png" );
    flappyBird->setPosition( m_visibleSize.width / 2 + m_origin.x,  m_visibleSize.height / 2 + m_origin.y );

    auto flappyBody = PhysicsBody::createCircle( flappyBird->getContentSize().width / 2 );
    flappyBird->setPhysicsBody( flappyBody );

    flappyBody->setCollisionBitmask( BIRD_COLLISION_BITMASK );
    flappyBody->setContactTestBitmask( true );

    layer->addChild( flappyBird, 100 );
}


void Bird::Fall() {
    if ( true == m_isFalling ) {
        flappyBird->setPositionX( m_visibleSize.width / 2 + m_origin.x );
        flappyBird->setPositionY( flappyBird->getPositionY() - ( BIRD_FALLING_SPEED * m_visibleSize.height ) );
    }
    else {
        flappyBird->setPositionX( m_visibleSize.width / 2 + m_origin.x );
        flappyBird->setPositionY( flappyBird->getPositionY() + ( BIRD_FALLING_SPEED * m_visibleSize.height ) );
    }

}

void Bird::Fly() {
    m_isFalling = false;
}
