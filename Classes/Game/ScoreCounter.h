//
//  ScoreCounter.h
//  RollingThunderCpp
//
//  Created by André Vants on 08/01/23.
//

#ifndef ScoreCounter_h
#define ScoreCounter_h

#include "axmol.h"

struct Score {
    int points;
    int coins;
    float timestamp; // double?
};

class ScoreCounter
{
public:
    Score getScore() const;
    void addRunningScore(const float points);
    void addMoneyScore(const int points, const int money);
    void addComboScore(const int points);
//    void setTimeElapsed(const float time);
    void addTimeElapsed(const float deltatime);
    
private:
    int _points;
    int _moneyCount;
    float _timeElapsed;
    float _runningPoints;
    
    bool _isComboActive;
    int _comboCount;
};

#endif /* ScoreCounter_h */
