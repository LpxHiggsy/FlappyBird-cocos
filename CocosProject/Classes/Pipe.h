//
//  Pipe.h
//  CocosProject
//
//  Created by HIGGS Callum T on 10/15/15.
//
//

#ifndef __CocosProject__Pipe__
#define __CocosProject__Pipe__

#include <stdio.h>


class Pipe : public cocos2d::Node
{
public:
    Pipe();
    ~Pipe();
    
    virtual bool init() override;
    static Pipe* create();
    
    void    update(float);
    
    bool    hasCollidedWithAPipe(cocos2d::Rect collisionBoxToCheck);
    void    reset();
    
private:
    cocos2d::Sprite* topPipe;
    cocos2d::Sprite* bottomPipe;
    
    cocos2d::Sprite* topPipe2;
    cocos2d::Sprite* bottomPipe2;
    
    float       startXPosition;
    float       startYPosition_top;
    float       startYPosition_bottom;
    float       startXPosition2;
    float       startYPosition_top2;
    float       startYPosition_bottom2;
    float       currentSpeed;
    
    
};




#endif /* defined(__CocosProject__Pipe__) */
