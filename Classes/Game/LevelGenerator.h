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
    OBSTACLE_SMALL,
    
    ROLLING_ROCK_VERTICAL,
    ROLLING_ROCK_DIAGONAL,
    
    COLLECT_MONEY,
    COLLECT_GOLD_BAR,
    COLLECT_GOLD_BAR_3X,
    POWER_UP_CRACKLE
};

struct SpawnPoint
{
    SpawnPoint(Entity type, ax::Vec2 pos) : type(type), position(pos) {}
    
    Entity type;
    ax::Vec2 position;
};

struct RollingRock;

class LevelGenerator
{
public:
    LevelGenerator(const float sceneWidth, const float sceneHeight, const float laneSpacing);
    ~LevelGenerator();
    
    std::list<SpawnPoint> spawnObstacles(const int n, const bool replaceEnemy); // true -> replaces 1 obstacle for an enemy
    std::list<SpawnPoint> spawnRollingRock(const float emptyChance); // if !empty, spawns an obstacle / chance -> {0.0...1.0}
    std::list<SpawnPoint> spawnTripleRollingRocks();
    std::list<SpawnPoint> spawnCoinPattern();
    std::list<SpawnPoint> spawnPowerUp();
    
private:
    float xShuffleForSingleRock(RollingRock type, bool hasObstacle);
    
    const float _widthUnit;
    const float _heightUnit;
    const float _laneSpacing;
    int _currentLevel;
};

#endif /* LevelGenerator_h */
