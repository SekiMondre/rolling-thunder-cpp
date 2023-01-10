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
//    void setTimeElapsed(const float time);
    void addTimeElapsed(const float deltatime);
    
private:
    int _points;
    int _moneyCount;
    float _timeElapsed;
};

#endif /* ScoreCounter_h */
