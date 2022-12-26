//
//  LevelGenerator.h
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#ifndef LevelGenerator_h
#define LevelGenerator_h

#include "axmol.h"

enum class Entity
{
    ENEMY_NORMAL,
    ENEMY_BIG,
    ENEMY_DODGER,

    OBSTACLE_BIG,
    OBSTACLE_MEDIUM,
    OBSTACLE_SMALL
};

struct SpawnPoint
{
    SpawnPoint(Entity type, ax::Vec2 pos) : type(type), position(pos) {}
    
    Entity type;
    ax::Vec2 position;
};

class LevelGenerator
{
public:
    LevelGenerator(const float sceneHeight);
    ~LevelGenerator();
    
    std::list<SpawnPoint> spawnObstacles(const int n, const bool replaceEnemy);
    
private:
    const float _heightUnit;
    int _currentLevel;
};

#endif /* LevelGenerator_h */
