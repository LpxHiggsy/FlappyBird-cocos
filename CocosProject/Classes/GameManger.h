//
//  GameManger.h
//  CocosProject
//
//  Created by HIGGS Callum T on 10/2/15.
//
//

#ifndef __CocosProject__GameManger__
#define __CocosProject__GameManger__

#include <stdio.h>

class GameManger
{
public:
    ~GameManger();
    static GameManger* sharedGameManger();
    
    void AddToScore( int increment );
    void ResetScore();
    int GetScore();
    
    bool isGameLive;
    
private:
    GameManger();
    static GameManger* instance;
    
    int score;
};

#endif /* defined(__CocosProject__GameManger__) */
