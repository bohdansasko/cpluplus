#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    auto backgroundSprite = Sprite::create("iphonehd/Splash Screen.png");
//    backgroundSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

//    this->addChild( backgroundSprite );

    auto backgroundSprite = Sprite::create( "iphonehd/Background.png" );
    backgroundSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height /  2 + origin.y ) );
    this->addChild( backgroundSprite );

    auto titleSprite = Sprite::create( "iphonehd/Title.png" );
    titleSprite->setPosition( Vec2( visibleSize.width  / 2 + origin.x, visibleSize.height - titleSprite->getContentSize().height ) );
    this->addChild( titleSprite );

    auto playItem = MenuItemImage::create( "iphonehd/Play Button.png", "iphonehd/Play Button Clicked.png",
                                           CC_CALLBACK_1( MainMenuScene::goToGameScene, this ));
    playItem->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ));

    auto menu = Menu::create(playItem, NULL);
    menu->setPosition( Vec2(Point::ZERO) );

    this->addChild( menu );

    return true;
}

void MainMenuScene::goToGameScene( cocos2d::Ref *sender ) {
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME, scene) );
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
