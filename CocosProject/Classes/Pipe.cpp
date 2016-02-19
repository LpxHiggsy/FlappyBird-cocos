//
//  Pipe.cpp
//  CocosProject
//
//  Created by HIGGS Callum T on 10/15/15.
//
//

#include "Pipe.h"
#include "cocostudio/CocoStudio.h"
#include "GameManger.h"

using namespace cocos2d;

//-------------------------------------------------------------------------

Pipe* Pipe::create()
{
    Pipe* myNode = new Pipe();
    if (myNode->init())
    {
        myNode->autorelease();
        return myNode;
    }
    else
    {
        CC_SAFE_DELETE(myNode);
        return nullptr;
    }
    return myNode;
}

//-------------------------------------------------------------------------

bool Pipe::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    
    //Load this object in from cocos studio.
    auto rootNode = CSLoader::createNode("Pipe.csb");
    addChild(rootNode);
    
    auto rootNode2 = CSLoader::createNode("Pipe.csb");
    addChild(rootNode2);
    
    //Position this container at left,centre. Anchor point should also be (0.0f, 0.5f).
    auto winSize = Director::getInstance()->getVisibleSize();
    this->setPosition(Vec2(0.0f, winSize.height*0.5f));
    this->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->scheduleUpdate();
    
    
    //Set references to the Sprite objects (pipes)
    topPipe    = (Sprite*)rootNode->getChildByName("toppipe");
    bottomPipe = (Sprite*)rootNode->getChildByName("bottompipe");
    
    topPipe2    = (Sprite*)rootNode2->getChildByName("toppipe");
    bottomPipe2 = (Sprite*)rootNode2->getChildByName("bottompipe");
    
    //Set the start positions.
    startXPosition        = winSize.width;
    startYPosition_top    = topPipe->getPositionY();
    startYPosition_bottom = bottomPipe->getPositionY();
    topPipe->setPosition(startXPosition, startYPosition_top);
    bottomPipe->setPosition(startXPosition, startYPosition_bottom);
    
    startXPosition2        = winSize.width/4;
    startYPosition_top2    = topPipe2->getPositionY();
    startYPosition_bottom2 = bottomPipe2->getPositionY();
    topPipe2->setPosition(startXPosition2, startYPosition_top2);
    bottomPipe2->setPosition(startXPosition2, startYPosition_bottom2);
    
    //Speed of pipes at start.
    currentSpeed = 200.0f;
    
    return true;
}

//-------------------------------------------------------------------------

Pipe::Pipe()
{
}

//-------------------------------------------------------------------------

Pipe::~Pipe()
{
    
}

//-------------------------------------------------------------------------

void Pipe::update(float deltaTime)
{
    if( GameManger::sharedGameManger()->isGameLive )
    {
        //Get the window size.
        auto  winSize = Director::getInstance()->getVisibleSize();
        
        //Move the pipes to the left.
        Vec2 currentTopPos = topPipe->getPosition();
        topPipe->setPosition(currentTopPos.x-currentSpeed*deltaTime, currentTopPos.y);
        
        Vec2 currentBottomPos = bottomPipe->getPosition();
        bottomPipe->setPosition(currentBottomPos.x-currentSpeed*deltaTime, currentBottomPos.y);
        
        //Did the x position (incorporating the sprite width) go off screen.
        if(currentTopPos.x < -bottomPipe->getBoundingBox().size.width*0.5f)
        {
            //Get the position just off screen to the right.
            float newXPos = winSize.width+bottomPipe->getBoundingBox().size.width*0.5f;
            //Get a random position for the regenerated pipes.
            float yOffset = rand_0_1()*winSize.height*0.3f;
            
            //Set the new positionings.
            topPipe->setPosition(newXPos, currentTopPos.y-yOffset);
            bottomPipe->setPosition(newXPos, currentBottomPos.y-yOffset);
            
            //Increase the speed of the pipes each time they are repositioned.
            currentSpeed += 10.0f;
            
            //Add 1 to score using the game manager singleton.
            GameManger::sharedGameManger()->AddToScore(1);
        }
    }
}

//-------------------------------------------------------------------------

bool Pipe::hasCollidedWithAPipe(Rect collisionBoxToCheck)
{
    //Did either of the pipes collide with the incoming object.
    
    //-----------------------------------------------------------------------------------------
    //We need to get the world positiona nd size of each pipe.
    
    //BOTTOM PIPE
    Rect modifiedBottomPipe;
    modifiedBottomPipe.size = bottomPipe->getBoundingBox().size;
    modifiedBottomPipe.origin = convertToWorldSpaceAR(bottomPipe->getBoundingBox().origin);
    
    //TOP PIPE
    Rect modifiedTopPipe;
    modifiedTopPipe.size = bottomPipe->getBoundingBox().size;
    modifiedTopPipe.origin = convertToWorldSpaceAR(topPipe->getBoundingBox().origin);
    //-----------------------------------------------------------------------------------------
    
    
    //Did the incoming Rect collide with either modified Rects?
    if( modifiedBottomPipe.intersectsRect(collisionBoxToCheck) || modifiedTopPipe.intersectsRect(collisionBoxToCheck) )
    {
        return true;
    }
    
    return false;
}

//-------------------------------------------------------------------------

void Pipe::reset()
{
    topPipe->setPosition(startXPosition, startYPosition_top);
    bottomPipe->setPosition(startXPosition, startYPosition_bottom);
    
    currentSpeed = 200.0f;
}

//-------------------------------------------------------------------------









