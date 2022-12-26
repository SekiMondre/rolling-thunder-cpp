//
//  LevelGenerator.h
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#ifndef LevelGenerator_h
#define LevelGenerator_h

#include "axmol.h"

struct Entity
{
    enum Category {
        ENEMY_NORMAL,
        ENEMY_BIG,
        ENEMY_DODGER,
        
        OBSTACLE_BIG,
        OBSTACLE_MEDIUM,
        OBSTACLE_SMALL
    };
    
    Entity(Category type, ax::Vec2 pos) : type(type), position(pos) {}
    
    Category type;
    ax::Vec2 position;
};

class LevelGenerator
{
public:
    LevelGenerator();
    ~LevelGenerator();
    
    std::list<Entity> spawnObstacles(const int n, const bool replaceEnemy);
    
private:
    int _currentLevel;
};

#endif /* LevelGenerator_h */
