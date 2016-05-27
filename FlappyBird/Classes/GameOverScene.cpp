#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;

Scene *GameOverScene::createScene(unsigned int tempScore)
{
    score = tempScore;
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    log("Game Over");
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Wing.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Point.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Hit.mp3");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("iphonehd/Background.png");
    backgroundSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    this->addChild(backgroundSprite);

    auto retryItem = MenuItemImage::create("iphonehd/Retry Button.png", "iphonehd/Retry Button Clicked.png",
                                           CC_CALLBACK_1(GameOverScene::goToGameScene, this));
    retryItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4));


    auto mainMenuItem = MenuItemImage::create("iphonehd/Menu Button.png", "iphonehd/Menu Button Clicked.png",
                                           CC_CALLBACK_1(GameOverScene::goToMainMenuScene, this));
    mainMenuItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3));

    auto menu = Menu::create(retryItem, mainMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu);

    // Load or set score
    UserDefault *def = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey("HIGHSCORE", 0);

    if (score > highScore) {
        highScore = score;
        def->setIntegerForKey("HIGHSCORE", highScore);
    }
    def->flush();

    // Score of current time
    __String *tempScore = __String::createWithFormat("%i", score);

    auto labelCurrentScore = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    labelCurrentScore->setPosition(visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y);
    labelCurrentScore->setColor(Color3B::WHITE);

    this->addChild(labelCurrentScore);

    // label high score
    __String *tempHighScore = __String::createWithFormat("%i", highScore);
    auto highScoreLabel = Label::createWithTTF(tempHighScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    highScoreLabel->setColor(Color3B::WHITE);
    highScoreLabel->setPosition(Vec2(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(highScoreLabel);

    return true;
}

void GameOverScene::goToMainMenuScene(cocos2d::Ref *sender) {
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::goToGameScene(cocos2d::Ref *sender) {
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
