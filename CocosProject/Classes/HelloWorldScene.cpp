#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Pipe.h"
#include "GameManger.h"
#include "stdio.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    this->scheduleUpdate();
    
    auto winSize = Director::getInstance()->getVisibleSize();
    upForce = 0;
    flappyBird = (Sprite*)rootNode->getChildByName("flappyBird");
    
    //scoreLabel = (Text*)rootNode->getChildByName("scoreLabel");
    scoreLabel = static_cast<ui::Text*>(rootNode->getChildByName("scoreLabel"));
    
    pipeNode = (Node*)rootNode->getChildByName("pipeNode");
    pipes = Pipe::create();
    pipeNode->addChild(pipes);
    
    //TOUCHES
    auto touchListener = EventListenerTouchOneByOne::create();
    
    //Set callbacks for our touch functions.
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //StartButton
    StartButton = static_cast<ui::Button*>(rootNode->getChildByName("Start_Button"));
    StartButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartButtonPressed, this));
    StartButton->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));
    
    GameManger::sharedGameManger()->isGameLive = false;

    return true;
}

static const int kGravity = 5.0f;

void HelloWorld::update(float delta)
{
    if(GameManger::sharedGameManger()->isGameLive)
    {
        Vec2 currentPos = flappyBird->getPosition();
        flappyBird->setPosition(currentPos.x, currentPos.y+upForce-kGravity);
        
        if( upForce > 0 )
            upForce--;
        
        //If the birs collides with a pipe then rotate it.
        if(pipes->hasCollidedWithAPipe(flappyBird->getBoundingBox()))
        {
            this->EndGame();
        }
    }
    
    //Display the score
    scoreLabel->setString(StringUtils::format("%d", GameManger::sharedGameManger()->GetScore()));
    
}

void HelloWorld::StartButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("In touch! %d", type);
    
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        //CCLOG("touch ended.")
        this->StartGame();
    }
    
    this->StartGame();
    
}

void HelloWorld::StartGame()
{
    auto winSize = Director::getInstance()->getVisibleSize();
    
    GameManger::sharedGameManger()->isGameLive = true;
    
    // Reset bird position.
    flappyBird->setPosition(flappyBird->getPosition().x, winSize.height*0.7f);
    upForce = 0;
    
    // Reset the score.
    GameManger::sharedGameManger()->ResetScore();
    
    pipes->reset();
    
    //Retract start button.
    auto moveTo = MoveTo::create(0.5, Vec2(-winSize.width*0.5f, winSize.height*0.5f));
    // Take half a second to move off screen.
    StartButton->runAction(moveTo);
}

void HelloWorld::EndGame()
{
    auto winSize = Director::getInstance()->getVisibleSize();
    
    GameManger::sharedGameManger()->isGameLive = false;
    
    //Bring start button back on screen.
    auto moveTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height*0.5f)); // Take half a second to move on screen.
    StartButton->runAction(moveTo);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    cocos2d::log("touch began");
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    upForce = 20;
    cocos2d::log("touch ended");
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}


