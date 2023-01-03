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
    
    for (int section_idx = 0; section_idx < numberOfSections; section_idx++) {
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
    log("--- power up");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnPowerUp(_levelModules.back());
    log("--- END LEVEL GEN");
}

std::list<SpawnPoint> LevelGenerator::popNextSection()
{
    auto section = _levelModules.front(); // check empty? -> .front() on empty list is undefined behavior
    _levelModules.pop_front();
    return section;
}

// MARK: - Builder methods

void LevelGenerator::buildSingleObstacle()
{
    log("--- 1x obstacle");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnObstacles(_levelModules.back(), 1, false);
}

void LevelGenerator::buildDoubleObstacle()
{
    log("--- 2x obstacle");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnObstacles(_levelModules.back(), 2, false);
}

void LevelGenerator::buildTripleObstacle()
{
    log("--- 3x obstacle");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnObstacles(_levelModules.back(), 3, false);
}

void LevelGenerator::buildSingleObstacleWithEnemy()
{
    log("--- 1x obstacle + enemy");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnObstacles(_levelModules.back(), 2, true);
}

void LevelGenerator::buildDoubleObstacleWithEnemy()
{
    log("--- 2x obstacle + enemy");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnObstacles(_levelModules.back(), 3, true);
}

void LevelGenerator::buildTripleObstacleWithEnemy()
{
    log("--- 3x obstacle + enemy");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnObstacles(_levelModules.back(), 4, true);
}

void LevelGenerator::buildSingleRollingRock()
{
    log("--- 1x rolling rock");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnRollingRock(_levelModules.back(), 0.5f);
}

void LevelGenerator::buildTripleRollingRocks()
{
    log("--- 3x rolling rock");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnTripleRollingRocks(_levelModules.back());
}

void LevelGenerator::buildCollectibles()
{
    log("--- collectible fiesta");
    _levelModules.emplace_back(std::list<SpawnPoint>());
    this->spawnCoinPattern(_levelModules.back());
}

// MARK: - Selector methods

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

// MARK: - Spawn methods

void LevelGenerator::spawnObstacles(std::list<SpawnPoint>& spawns, const int n, const bool replaceEnemy)
{
    int replaceIdx = (replaceEnemy) ? RNG::randomInt(0, n) : -1;
    
    for (int i = 0; i < n; i++)
    {
        const float y = (_heightUnit / float(n * 2)) * float(i * 2 + 1);
        if (i != replaceIdx) {
            auto obstacle = selectObstacle();
            int slotIndex = selectSlotIndex(obstacle);
            auto obstaclePosition = Vec2(obstacle.size.width * (float(slotIndex - 1) - obstacle.slotCorrectionFactor), y);
            spawns.emplace_back(SpawnPoint(obstacle.entityType, obstaclePosition)); // Construct in-place to apply move semantics
            // TODO: Spawn coins
        } else {
            auto enemy = selectEnemyForLevel();
            auto enemyPosition = Vec2(xShuffleForEnemy(enemy), y);
            spawns.emplace_back(SpawnPoint(enemy.entityType, enemyPosition));
        }
    }
}

void LevelGenerator::spawnRollingRock(std::list<SpawnPoint>& spawns, const float emptyChance)
{
    bool hasObstacle = !(RNG::randomUniform() < emptyChance);
    auto rock = selectRollingRock();
    auto rockPosition = Vec2(xShuffleForSingleRock(rock, hasObstacle), _heightUnit * 0.85f);
    spawns.emplace_back(SpawnPoint(rock.entityType, rockPosition));
    
    if (hasObstacle) {
        auto obstacle = RNG::randomBool() ? Obstacle::SMALL : Obstacle::MEDIUM;
        int slotIndex = selectSlotIndex(obstacle);
        auto obstaclePosition = Vec2(obstacle.size.width * (float(slotIndex - 1) - obstacle.slotCorrectionFactor), _heightUnit * 0.3f);
        spawns.emplace_back(SpawnPoint(obstacle.entityType, obstaclePosition));
        // TODO: Spawn coins
    } else {
        // TODO: Spawn coin pattern
    }
}

void LevelGenerator::spawnTripleRollingRocks(std::list<SpawnPoint>& spawns)
{
    float sign = float(RNG::randomSign());
    
    if (RNG::randomUniform() < 0.33f) {
        float centerDistance = _widthUnit * 0.2f;
        auto position1 = Vec2(0.0f, _heightUnit * 0.75f);
        auto position2 = Vec2(centerDistance, _heightUnit * 0.95f + _widthUnit * 0.1f * sign);
        auto position3 = Vec2(-centerDistance, _heightUnit * 0.95f + _widthUnit * 0.1f * -sign);
        spawns.emplace_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position1));
        spawns.emplace_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position2));
        spawns.emplace_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position3));
    } else {
        float xCoordinate = _widthUnit * 0.37f;
        bool isAlt = RNG::randomBool();
        for (int i = 0; i < 3; i++) {
            float altFactor = (isAlt) ? (1.0f - 2.0f * float(i % 2)) : 1.0f;
            auto rockPosition = Vec2(xCoordinate * sign * altFactor, _heightUnit * (0.95f - 0.3f * float(i)));
            spawns.emplace_back(SpawnPoint(Entity::ROLLING_ROCK_DIAGONAL, rockPosition));
        }
    }
    // TODO: Spawn coin pattern
}

void LevelGenerator::spawnCoinPattern(std::list<SpawnPoint>& spawns)
{
    CoinStrategy strategy = selectCoinStrategyStandalone();
    for (Vec2 position : strategy.getPositions()) {
        spawns.emplace_back(SpawnPoint(Entity::COLLECT_MONEY, position));
    }
    
    // TODO: use pivot
}

void LevelGenerator::spawnPowerUp(std::list<SpawnPoint>& spawns)
{
    CoinStrategy strategy = selectCoinStrategyForPowerUp();
    for (Vec2 position : strategy.getPositions()) {
        spawns.emplace_back(SpawnPoint(Entity::COLLECT_MONEY, position));
    }
    spawns.emplace_back(SpawnPoint(Entity::POWER_UP_CRACKLE, strategy.getPivot()));
}
