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

class SpawnPoint
{
public:
    Entity type;
    ax::Vec2 position;
    
    SpawnPoint(Entity type, ax::Vec2 pos) : type(type), position(pos) {}
    SpawnPoint(const SpawnPoint& spawnPoint) : type(spawnPoint.type), position(spawnPoint.position) {
        ax::log("COPY!!!");
    }
    SpawnPoint(SpawnPoint&& spawnPoint) : type(spawnPoint.type), position(spawnPoint.position) {
        ax::log("MOVE!!!");
    }
    SpawnPoint& operator=(const SpawnPoint& other) = default;
};

struct Enemy;
struct Obstacle;
struct RollingRock;

class CoinStrategy;
class EnemySelector;

class LevelGenerator
{
public:
    LevelGenerator(const float sceneWidth, const float sceneHeight, const float laneSpacing);
    ~LevelGenerator();
    
    int getCurrentLevel();
    std::list<SpawnPoint> popNextSection();
    void generateNextLevel(const float scrollSpeed);
    void generateLevel(const int level, const int numberOfSections);
    bool isEndOfLevel();
//    void increaseLevel();
    
    void spawnObstacles(std::list<SpawnPoint>& spawns, const int n, const bool replaceEnemy) const; // true -> replaces 1 obstacle for an enemy
    void spawnRollingRock(std::list<SpawnPoint>& spawns, const float emptyChance) const; // if !empty, spawns an obstacle / chance -> {0.0...1.0}
    void spawnTripleRollingRocks(std::list<SpawnPoint>& spawns) const;
    void spawnCoinPattern(std::list<SpawnPoint>& spawns) const;
    void spawnPowerUp(std::list<SpawnPoint>& spawns) const;
    
private:
    void buildSingleObstacle();
    void buildDoubleObstacle();
    void buildTripleObstacle();
    void buildSingleObstacleWithEnemy();
    void buildDoubleObstacleWithEnemy();
    void buildTripleObstacleWithEnemy();
    void buildSingleRollingRock();
    void buildTripleRollingRocks();
    void buildCollectibles();
    
    const Enemy& selectEnemyForLevel() const;
    const Obstacle& selectObstacle() const;
    int selectSlotIndex(Obstacle obstacle) const;
    int selectFreeLaneAgainst(const Obstacle obstacle, const int slotIndex) const;
    CoinStrategy selectCoinStrategyStandalone() const;
    CoinStrategy selectLaneCoins(const int obsCount, const ax::Vec2 center, const Obstacle obsType, const int slotIndex) const;
    
    float xShuffleForEnemy(const Enemy enemy) const;
    float xShuffleForSingleRock(const RollingRock type, bool hasObstacle) const;
    
    const std::unique_ptr<const EnemySelector> _enemySelector;
    const float _widthUnit;
    const float _heightUnit;
    const float _laneSpacing;
    
    int _currentLevel;
    
    std::vector<std::vector<std::function<void(void)>>> _levelBuilders;
    std::vector<std::vector<int>> _levelDistributions;
    
    std::list<std::list<SpawnPoint>> _levelModules;
    
//    void generateLevel(const int level, const int numberOfSections);
};

#endif /* LevelGenerator_h */
