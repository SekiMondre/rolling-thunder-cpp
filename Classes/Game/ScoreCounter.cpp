//
//  ScoreCounter.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 08/01/23.
//

#include "ScoreCounter.h"

const float COMBO_FACTOR = 0.3f;
const int MAX_COMBO_COUNT = 10;

Score ScoreCounter::getScore() const
{
    return Score { _points, _moneyCount, _timeElapsed };
}

void ScoreCounter::addMoneyScore(const int score, const int money)
{
    _points += score;
    _moneyCount += money;
}

void ScoreCounter::addComboScore(const int points)
{
    _points += points;
    if (_isComboActive) {
//        int bonus = int(float(points * _comboCount) * COMBO_FACTOR);
//        // combo score
//        _comboCount = std::min(_comboCount + 1, MAX_COMBO_COUNT);
    }
}

void ScoreCounter::addTimeElapsed(const float deltatime)
{
    _timeElapsed += deltatime;
}
