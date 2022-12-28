//
//  EnemySelector.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 28/12/22.
//

#include "EnemySelector.h"
#include "RollingThunder.h"

EnemySelector::EnemySelector()
{
    weightSum = {0, 0, 0, 0};
    for (int level = 0; level < enemyTable.size(); level++) {
        int weight = 0;
        for (int enemy_idx = 0; enemy_idx < enemyTable[level].size(); enemy_idx++) {
            weight += enemyTable[level][enemy_idx];
        }
        weightSum[level] = weight;
    }
}

const Enemy& EnemySelector::nextEnemy(const int level) const
{
    int levelIndex = std::clamp(level, 1, 4) - 1;
    int random = RNG::randomInt(0, weightSum[levelIndex]);
    int accumulate = 0;
    for (int enemy_idx = 0; enemy_idx < 3; enemy_idx++) {
        accumulate += enemyTable[levelIndex][enemy_idx];
        if (random < accumulate) {
            return Enemy::ALL[enemy_idx];
        }
    }
    return Enemy::ALL[0]; // Error
}
