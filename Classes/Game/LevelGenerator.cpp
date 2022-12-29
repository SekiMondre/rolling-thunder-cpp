//
//  LevelGenerator.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#include "LevelGenerator.h"
#include "RollingThunder.h"

USING_NS_AX;

LevelGenerator::LevelGenerator(const float sceneWidth, const float sceneHeight, const float laneSpacing)
    : _enemySelector(std::unique_ptr<EnemySelector>(new EnemySelector()))
    , _widthUnit(sceneWidth)
    , _heightUnit(sceneHeight)
    , _laneSpacing(laneSpacing)
    , _currentLevel(0)
{
    std::vector<std::function<void(void)>> level1 = {
        std::bind(&LevelGenerator::buildSingleObstacle, this),
        std::bind(&LevelGenerator::buildSingleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this)
    };
    std::vector<int> chancesLevel1 = {35, 45, 20};
    _levelBuilders.push_back(level1);
    _levelDistributions.push_back(chancesLevel1);
    
    std::vector<std::function<void(void)>> level2 = {
        std::bind(&LevelGenerator::buildSingleRollingRock, this),
        std::bind(&LevelGenerator::buildSingleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this),
        std::bind(&LevelGenerator::buildCollectibles, this)
    };
    std::vector<int> chancesLevel2 = {35, 27, 28, 10};
    _levelBuilders.push_back(level2);
    _levelDistributions.push_back(chancesLevel2);
    
    std::vector<std::function<void(void)>> level3 = {
        std::bind(&LevelGenerator::buildTripleRollingRocks, this),
        std::bind(&LevelGenerator::buildSingleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this),
        std::bind(&LevelGenerator::buildTripleObstacle, this),
        std::bind(&LevelGenerator::buildCollectibles, this)
    };
    std::vector<int> chancesLevel3 = {30, 25, 10, 10, 15, 10};
    _levelBuilders.push_back(level3);
    _levelDistributions.push_back(chancesLevel3);
    
    std::vector<std::function<void(void)>> level4 = {
        std::bind(&LevelGenerator::buildTripleRollingRocks, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this),
        std::bind(&LevelGenerator::buildTripleObstacle, this),
        std::bind(&LevelGenerator::buildDoubleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildTripleObstacleWithEnemy, this)
    };
    std::vector<int> chancesLevel4 = {30, 17, 17, 16, 20};
    _levelBuilders.push_back(level4);
    _levelDistributions.push_back(chancesLevel4);
}

LevelGenerator::~LevelGenerator()
{
    log("Level generator destroyed");
}

void LevelGenerator::generateLevel(const int level, const int numberOfSections)
{
    int lvl_idx = std::clamp(level, 1, 4) - 1;
    
    for (int sec = 0; sec < numberOfSections; sec++) {
        int random = RNG::randomInt(0, 100);
        int acc = 0;
        
        for(int build_idx = 0; build_idx < _levelDistributions[lvl_idx].size(); build_idx++) {
            acc += _levelDistributions[lvl_idx][build_idx];
            if (random < acc) {
                _levelBuilders[lvl_idx][build_idx]();
                break;
            }
        }
    }
    // append power up
}

void LevelGenerator::testLevel()
{
    std::vector<std::vector<std::function<void(void)>>> levelBuilders;
    std::vector<std::vector<int>> levelDistributions;
    
    std::vector<std::function<void(void)>> level1 = {
        std::bind(&LevelGenerator::buildSingleObstacle, this),
        std::bind(&LevelGenerator::buildSingleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this)
    };
    std::vector<int> chancesLevel1 = {35, 45, 20};
    
    levelBuilders.push_back(level1);
    levelDistributions.push_back(chancesLevel1);
    
    std::vector<std::function<void(void)>> level2 = {
        std::bind(&LevelGenerator::buildSingleRollingRock, this),
        std::bind(&LevelGenerator::buildSingleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this),
        std::bind(&LevelGenerator::buildCollectibles, this)
    };
    std::vector<int> chancesLevel2 = {35, 27, 28, 10};
    
    levelBuilders.push_back(level2);
    levelDistributions.push_back(chancesLevel2);
    
    std::vector<std::function<void(void)>> level3 = {
        std::bind(&LevelGenerator::buildTripleRollingRocks, this),
        std::bind(&LevelGenerator::buildSingleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this),
        std::bind(&LevelGenerator::buildTripleObstacle, this),
        std::bind(&LevelGenerator::buildCollectibles, this)
    };
    std::vector<int> chancesLevel3 = {30, 25, 10, 10, 15, 10};
    
    levelBuilders.push_back(level3);
    levelDistributions.push_back(chancesLevel3);
    
    std::vector<std::function<void(void)>> level4 = {
        std::bind(&LevelGenerator::buildTripleRollingRocks, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this),
        std::bind(&LevelGenerator::buildTripleObstacle, this),
        std::bind(&LevelGenerator::buildDoubleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildTripleObstacleWithEnemy, this)
    };
    std::vector<int> chancesLevel4 = {30, 17, 17, 16, 20};
    
    levelBuilders.push_back(level4);
    levelDistributions.push_back(chancesLevel4);
    
    std::vector<std::function<void(void)>> funs = {
        std::bind(&LevelGenerator::buildSingleObstacle, this),
        std::bind(&LevelGenerator::buildSingleObstacleWithEnemy, this),
        std::bind(&LevelGenerator::buildDoubleObstacle, this)
    };
    std::vector<int> probabilities = {35, 45, 20};
    
    int r = RNG::randomInt(0, 100);
    int acc = 0;
    for (int i = 0; i < 3; i++) {
        acc += probabilities[i];
        if (r < acc) {
            funs[i]();
            break;
        }
    }
}

void LevelGenerator::buildSingleObstacle()
{
    log("SINGLE obstacle");
    // create list
    // pass as reference to spawn func / fill
    // make segment with list
    // append to level array
}

void LevelGenerator::buildDoubleObstacle()
{
    log("DOUBLE obstacle");
}

void LevelGenerator::buildTripleObstacle()
{
    log("");
}

void LevelGenerator::buildSingleObstacleWithEnemy()
{
    log("");
}

void LevelGenerator::buildDoubleObstacleWithEnemy()
{
    log("");
}

void LevelGenerator::buildTripleObstacleWithEnemy()
{
    log("");
}

void LevelGenerator::buildSingleRollingRock()
{
    log("");
}

void LevelGenerator::buildTripleRollingRocks()
{
    log("");
}

void LevelGenerator::buildCollectibles()
{
    log("");
}



//void LevelGenerator::build

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

RollingRock selectRollingRock()
{
    return RNG::randomBool() ? RollingRock::VERTICAL : RollingRock::DIAGONAL;
}

Enemy LevelGenerator::selectEnemyForLevel() const  // maybe remove and call directly
{
    return _enemySelector->nextEnemy(_currentLevel);
}

int selectSlotIndex(Obstacle o)
{
    return RNG::randomInt(0, o.slotCount) + 1;
}

CoinStrategy selectCoinStrategyForPowerUp()
{
    return (RNG::randomBool()) ? CoinCircle::makeDefault() : CoinSquare::makeDefault();
}

CoinStrategy selectCoinStrategyStandalone()
{
    int idx = RNG::randomInt(0, 5);
    if (idx == 0) {
        return CoinCircle::makeDefault();
    } else if (idx == 1) {
        return CoinSquare::makeDefault();
    } else if (idx == 2) {
        return CoinBigRhombus::makeDefault();
    } else if (idx == 3) {
        return CoinSineWave::makeDefault();
    } else if (idx == 4) {
        return CoinHalfSineWave::makeDefault();
    } else {
        log("[ERROR] Invalid coin strategy standalone index: %d", idx);
        return CoinCircle::makeDefault();
    }
}

float xShuffleForEnemy(Enemy e)
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

float LevelGenerator::xShuffleForSingleRock(RollingRock type, bool hasObstacle)
{
    if (type == RollingRock::VERTICAL) {
        if (hasObstacle) {
            return _widthUnit * 0.2f * float(RNG::randomSign());
        } else {
            return _laneSpacing * (RNG::randomUniform() * 2.0f - 1.0f);
        }
    } else { // DIAGONAL
        return _widthUnit * 0.37f * float(RNG::randomSign());
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
            // TODO: Spawn coins
        } else {
            auto enemy = selectEnemyForLevel();
            auto enemyPosition = Vec2(xShuffleForEnemy(enemy), y);
            auto enemySpawn = SpawnPoint(enemy.entityType, enemyPosition);
            spawns.push_back(enemySpawn);
        }
    }
    
    return spawns;
}

std::list<SpawnPoint> LevelGenerator::spawnRollingRock(const float emptyChance)
{
    std::list<SpawnPoint> spawns;
    
    bool hasObstacle = !(RNG::randomUniform() < emptyChance);
    auto rock = selectRollingRock();
    auto rockPosition = Vec2(xShuffleForSingleRock(rock, hasObstacle), _heightUnit * 0.85f);
    auto rockSpawn = SpawnPoint(rock.entityType, rockPosition);
    spawns.push_back(rockSpawn);
    
    if (hasObstacle) {
        auto obstacle = RNG::randomBool() ? Obstacle::SMALL : Obstacle::MEDIUM;
        int slotIndex = selectSlotIndex(obstacle);
        auto obstaclePosition = Vec2(obstacle.size.width * (float(slotIndex - 1) - obstacle.slotCorrectionFactor), _heightUnit * 0.3f);
        auto obstacleSpawn = SpawnPoint(obstacle.entityType, obstaclePosition);
        spawns.push_back(obstacleSpawn);
        // TODO: Spawn coins
    } else {
        // TODO: Spawn coin pattern
    }
    return spawns;
}

std::list<SpawnPoint> LevelGenerator::spawnTripleRollingRocks()
{
    std::list<SpawnPoint> spawns;
    
    float sign = float(RNG::randomSign());
    
    if (RNG::randomUniform() < 0.33f) {
        float centerDistance = _widthUnit * 0.2f;
        auto position1 = Vec2(0.0f, _heightUnit * 0.75f);
        auto position2 = Vec2(centerDistance, _heightUnit * 0.95f + _widthUnit * 0.1f * sign);
        auto position3 = Vec2(-centerDistance, _heightUnit * 0.95f + _widthUnit * 0.1f * -sign);
        spawns.push_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position1));
        spawns.push_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position2));
        spawns.push_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position3));
    } else {
        float xCoordinate = _widthUnit * 0.37f;
        bool isAlt = RNG::randomBool();
        for (int i = 0; i < 3; i++) {
            float altFactor = (isAlt) ? (1.0f - 2.0f * float(i % 2)) : 1.0f;
            auto rockPosition = Vec2(xCoordinate * sign * altFactor, _heightUnit * (0.95f - 0.3f * float(i)));
            auto rockSpawn = SpawnPoint(Entity::ROLLING_ROCK_DIAGONAL, rockPosition);
            spawns.push_back(rockSpawn);
        }
    }
    // TODO: Spawn coin pattern
    return spawns;
}

std::list<SpawnPoint> LevelGenerator::spawnCoinPattern()
{
    std::list<SpawnPoint> spawns;
    
    CoinStrategy strategy = selectCoinStrategyStandalone();
    for (Vec2 position : strategy.getPositions()) {
        spawns.push_back(SpawnPoint(Entity::COLLECT_MONEY, position));
    }
    
    // TODO: use pivot
    
    return spawns;
}

std::list<SpawnPoint> LevelGenerator::spawnPowerUp()
{
    std::list<SpawnPoint> spawns;
    CoinStrategy strategy = selectCoinStrategyForPowerUp();
    for (Vec2 position : strategy.getPositions()) {
        spawns.push_back(SpawnPoint(Entity::COLLECT_MONEY, position));
    }
    auto powerSpawn = SpawnPoint(Entity::POWER_UP_CRACKLE, strategy.getPivot());
    spawns.push_back(powerSpawn);
    return spawns;
}
