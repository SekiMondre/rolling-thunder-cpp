//
//  EnemySelector.h
//  RollingThunderCpp
//
//  Created by André Vants on 28/12/22.
//

#ifndef EnemySelector_h
#define EnemySelector_h

#include "axmol.h"

struct Enemy;

class EnemySelector
{
public:
    EnemySelector();
    const Enemy& nextEnemy(const int level) const;
    
private:
    const std::vector<std::vector<int>> enemyTable = {
        {80, 20, 0},
        {60, 30, 10},
        {30, 35, 35},
        {0, 35, 65}
    };
    std::array<int, 4> weightSum;
};

#endif /* EnemySelector_h */
