//
//  LevelGenerator.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#include "LevelGenerator.h"

USING_NS_AX;

LevelGenerator::LevelGenerator()
    : _currentLevel(0)
{}

LevelGenerator::~LevelGenerator()
{
    log("Level generator destroyed");
}

std::list<Entity> LevelGenerator::spawnObstacles(const int n, const bool replaceEnemy)
{
    std::list<Entity> spawns;
    
    auto e1 = Entity(Entity::ENEMY_NORMAL, Vec2(-100, 500));
    auto e2 = Entity(Entity::OBSTACLE_BIG, Vec2(152, 750));
    auto e3 = Entity(Entity::OBSTACLE_SMALL, Vec2(-50, 250));
//    auto e3 = Entity(Entity::OBSTACLE_MEDIUM, Vec2(-50, 250)); // explode
    
    spawns.push_back(e1);
    spawns.push_back(e2);
    spawns.push_back(e3);
    
    return spawns;
}
