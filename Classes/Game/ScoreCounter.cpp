//
//  ScoreCounter.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 08/01/23.
//

#include "ScoreCounter.h"

Score ScoreCounter::getScore() const
{
    return Score { _points, _moneyCount, _timeElapsed };
}

void ScoreCounter::addTimeElapsed(const float deltatime)
{
    _timeElapsed += deltatime;
}
