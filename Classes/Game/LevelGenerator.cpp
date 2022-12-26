//
//  LevelGenerator.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#include "LevelGenerator.h"
#include "RollingThunder.h"

USING_NS_AX;

LevelGenerator::LevelGenerator(const float sceneHeight)
    : _heightUnit(sceneHeight)
    , _currentLevel(0)
{}

LevelGenerator::~LevelGenerator()
{
    log("Level generator destroyed");
}

Obstacle selectObstacle()
{
    int r = RNG::randomInt(0, 3);
    if (r == 0) {
        return Obstacle::BIG;
    } else if (r == 1) {
        return Obstacle::MEDIUM;
    } else {
        return Obstacle::SMALL;
    }
}

Enemy selectEnemyForLevel()
{
    return Enemy::NORMAL; // TODO
}

int selectSlotIndex(Obstacle o)
{
    return RNG::randomInt(0, o.slotCount) + 1;
}

float randomizeEnemyX(Enemy e)
{
    float laneSpacing = 153.0f; // Move to const init in class
    if (e == Enemy::DODGER) {
        float limit = laneSpacing - e.size.width * 0.64f;
        int maxDelta = 2 * (int)limit;
        return float(RNG::randomInt(0, maxDelta)) - limit;
    } else if (e == Enemy::BIG) {
        return float(RNG::randomInt(0, 5) - 2) * laneSpacing * 0.5f;
    } else { // NORMAL
        int maxDelta = 2 * (int)laneSpacing;
        return float(RNG::randomInt(0, maxDelta)) - laneSpacing;
    }
}

std::list<SpawnPoint> LevelGenerator::spawnObstacles(const int n, const bool replaceEnemy)
{
    std::list<SpawnPoint> spawns;
    
    int replaceIdx = (replaceEnemy) ? RNG::randomInt(0, n) : -1;
    
    for (int i = 0; i < n; i++)
    {
        const float y = (_heightUnit / float(n * 2)) * float(i * 2 + 1);
        
        if (i != replaceIdx) {
            auto obstacle = selectObstacle();
            int slotIndex = selectSlotIndex(obstacle);
            auto obstaclePosition = Vec2(obstacle.size.width * (float(slotIndex - 1) - obstacle.slotCorrectionFactor), y);
            auto obstacleSpawn = SpawnPoint(obstacle.entityType, obstaclePosition);
            spawns.push_back(obstacleSpawn);
            // Spawn coins
        } else {
            auto enemy = selectEnemyForLevel();
            auto enemyPosition = Vec2(randomizeEnemyX(enemy), y);
            auto enemySpawn = SpawnPoint(enemy.entityType, enemyPosition);
            spawns.push_back(enemySpawn);
        }
    }
    
    return spawns;
}
