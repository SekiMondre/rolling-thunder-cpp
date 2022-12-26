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

int selectSlotIndex(Obstacle o)
{
    return RNG::randomInt(0, o.slotCount) + 1;
}

std::list<SpawnPoint> LevelGenerator::spawnObstacles(const int n, const bool replaceEnemy)
{
    std::list<SpawnPoint> spawns;
    
//    int replaceIdx = (replaceEnemy) ? RNG::randomInt(0, n) : -1;
    int replaceIdx = -1;
    
    for (int i = 0; i < n; i++)
    {
        const float y = (_heightUnit / float(n * 2)) * float(i * 2 + 1);
        
        if (i != replaceIdx) {
            auto obstacle = selectObstacle();
            int slotIndex = selectSlotIndex(obstacle);
            auto obstaclePosition = Vec2(obstacle.size.width * (float(slotIndex - 1) - obstacle.slotCorrectionFactor), y);
            auto obstacleSpawn = SpawnPoint(obstacle.entityType, obstaclePosition);
            spawns.push_back(obstacleSpawn);
        } else {
            // enemy
        }
    }
    
    return spawns;
}
