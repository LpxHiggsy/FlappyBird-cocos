//
//  GameManger.cpp
//  CocosProject
//
//  Created by HIGGS Callum T on 10/2/15.
//
//

#include "GameManger.h"

GameManger* GameManger::instance = NULL;

GameManger* GameManger::sharedGameManger()
{
   if (instance == NULL)
   {
       instance = new GameManger();
   }
    
    return instance;
}


GameManger::GameManger()
{
    isGameLive = false;
}

GameManger::~GameManger()
{
    
}

void GameManger::AddToScore(int increment)
{
    this->score += increment;
}

void GameManger::ResetScore()
{
    score = 0;
}

int GameManger::GetScore()
{
    return score;
}