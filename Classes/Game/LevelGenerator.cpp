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

const Enemy& LevelGenerator::selectEnemyForLevel() const
{
    return _enemySelector->nextEnemy(_currentLevel);
}

const Obstacle& LevelGenerator::selectObstacle() const
{
    return Obstacle::ALL[RNG::randomInt(0, 3)];
}

int LevelGenerator::selectSlotIndex(Obstacle obstacle) const
{
    return RNG::randomInt(0, obstacle.slotCount) + 1;
}

int LevelGenerator::selectFreeLaneAgainst(const Obstacle obstacle, const int slotIndex) const
{
    int laneToRemove = 0;
    if (obstacle == Obstacle::BIG) {
        laneToRemove = slotIndex - 1;
    } else if (obstacle == Obstacle::MEDIUM) {
        laneToRemove = slotIndex / 2;
    } else { // SMALL
        laneToRemove = (slotIndex - 1) / 2;
    }
    int lanes[2] = {0};
    lanes[0] = 0 - (laneToRemove + 1) / 2; // SAGAZ trust the truncation
    lanes[1] = 1 - laneToRemove / 2;
    return lanes[RNG::randomInt(0, 2)];
}

CoinStrategy LevelGenerator::selectCoinStrategyStandalone() const
{
    int idx = RNG::randomInt(0, 5);
    if (idx == 0) {
        return CoinStrategy::makeCircle();
    } else if (idx == 1) {
        return CoinStrategy::makeSquare();
    } else if (idx == 2) {
        return CoinStrategy::makeBigRhombus();
    } else if (idx == 3) {
        return CoinStrategy::makeSineWave();
    } else if (idx == 4) {
        return CoinStrategy::makeHalfSineWave();
    } else {
        log("[ERROR] Invalid coin strategy standalone index: %d", idx);
        return CoinStrategy::makeCircle();
    }
}

CoinStrategy LevelGenerator::selectLaneCoins(const int obsCount, const Vec2 center, const Obstacle obsType, const int slotIndex) const
{
    const bool isSpecialCase = (obsType == Obstacle::MEDIUM && (slotIndex / 2 == 1));
    if (obsCount == 1) {
        if (isSpecialCase || RNG::randomBool()) {
            return CoinStrategy::makeRow(center, 10, _heightUnit * 0.1f);
        } else {
            return CoinStrategy::makeZigZagRow(center, 10, _heightUnit * 0.1f);
        }
    } else if (obsCount == 2) {
        if (isSpecialCase || RNG::randomBool()) {
            return CoinStrategy::makeRow(center, 4, _heightUnit * 0.125f);
        } else {
            return CoinStrategy::makeSmallRhombus(center);
        }
    } else if (obsCount == 3) {
        if (isSpecialCase || RNG::randomBool()) {
            return CoinStrategy::makeRow(center, 3, _heightUnit * 0.111f);
        } else {
            return CoinStrategy::makeSmallRhombus(center);
        }
    } else if (obsCount == 4) {
        if (_currentLevel >= 5) {
            return CoinStrategy::makeRow(center, 3, _heightUnit * 0.083f);
        } else {
            return CoinStrategy::makeRow(center, 2, _heightUnit * 0.125f);
        }
    }
    log("[ERROR] Invalid obstacle count for lane coins: %d", obsCount);
    return CoinStrategy::makeRow(center, 1, 0.0f);
}

float LevelGenerator::xShuffleForEnemy(const Enemy enemy) const
{
    float laneSpacing = 153.0f; // Move to const init in class
    if (enemy == Enemy::DODGER) {
        float limit = laneSpacing - enemy.size.width * 0.64f;
        int maxDelta = 2 * (int)limit;
        return float(RNG::randomInt(0, maxDelta)) - limit;
    } else if (enemy == Enemy::BIG) {
        return float(RNG::randomInt(0, 5) - 2) * laneSpacing * 0.5f;
    } else { // NORMAL
        int maxDelta = 2 * (int)laneSpacing;
        return float(RNG::randomInt(0, maxDelta)) - laneSpacing;
    }
}

float LevelGenerator::xShuffleForSingleRock(const RollingRock type, bool hasObstacle) const
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

void LevelGenerator::spawnObstacles(std::list<SpawnPoint>& spawns, const int n, const bool replaceEnemy) const
{
    int replaceIdx = (replaceEnemy) ? RNG::randomInt(0, n) : -1;
    
    for (int i = 0; i < n; i++)
    {
        const float y = (_heightUnit / float(n * 2)) * float(i * 2 + 1);
        if (i != replaceIdx) {
            const auto obstacle = selectObstacle();
            const int slotIndex = selectSlotIndex(obstacle);
            const auto obstaclePosition = Vec2(obstacle.size.width * (float(slotIndex - 1) - obstacle.slotCorrectionFactor), y);
            spawns.emplace_back(SpawnPoint(obstacle.entityType, obstaclePosition)); // Construct in-place to apply move semantics
            
            // Spawn coins
            const auto coinSpawnCenter = Vec2(_laneSpacing * float(selectFreeLaneAgainst(obstacle, slotIndex)), y);
            const auto coinStrategy = selectLaneCoins(n, coinSpawnCenter, obstacle, slotIndex);
            for (const Vec2& position : coinStrategy.getPositions()) {
                spawns.emplace_back(SpawnPoint(Entity::COLLECT_MONEY, position));
            }
        } else {
            const auto enemy = selectEnemyForLevel();
            const auto enemyPosition = Vec2(xShuffleForEnemy(enemy), y);
            spawns.emplace_back(SpawnPoint(enemy.entityType, enemyPosition));
        }
    }
}

void LevelGenerator::spawnRollingRock(std::list<SpawnPoint>& spawns, const float emptyChance) const
{
    const bool hasObstacle = !(RNG::randomUniform() < emptyChance);
    const auto rock = RNG::randomBool() ? RollingRock::VERTICAL : RollingRock::DIAGONAL;;
    const auto rockPosition = Vec2(xShuffleForSingleRock(rock, hasObstacle), _heightUnit * 0.85f);
    spawns.emplace_back(SpawnPoint(rock.entityType, rockPosition));
    
    if (hasObstacle) {
        const auto obstacle = RNG::randomBool() ? Obstacle::SMALL : Obstacle::MEDIUM;
        const int slotIndex = selectSlotIndex(obstacle);
        const auto obstaclePosition = Vec2(obstacle.size.width * (float(slotIndex - 1) - obstacle.slotCorrectionFactor), _heightUnit * 0.3f);
        spawns.emplace_back(SpawnPoint(obstacle.entityType, obstaclePosition));
        
        // Spawn coins
        const auto coinSpawnCenter = Vec2(_laneSpacing * float(selectFreeLaneAgainst(obstacle, slotIndex)), _heightUnit * 0.5f);
        const auto coinStrategy = selectLaneCoins(1, coinSpawnCenter, obstacle, slotIndex);
        for (const Vec2& position : coinStrategy.getPositions()) {
            spawns.emplace_back(SpawnPoint(Entity::COLLECT_MONEY, position));
        }
    } else {
        this->spawnCoinPattern(spawns);
    }
}

void LevelGenerator::spawnTripleRollingRocks(std::list<SpawnPoint>& spawns) const
{
    const float sign = float(RNG::randomSign());
    
    if (RNG::randomUniform() < 0.33f) {
        const float centerDistance = _widthUnit * 0.2f;
        const auto position1 = Vec2(0.0f, _heightUnit * 0.75f);
        const auto position2 = Vec2(centerDistance, _heightUnit * 0.95f + _widthUnit * 0.1f * sign);
        const auto position3 = Vec2(-centerDistance, _heightUnit * 0.95f + _widthUnit * 0.1f * -sign);
        spawns.emplace_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position1));
        spawns.emplace_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position2));
        spawns.emplace_back(SpawnPoint(Entity::ROLLING_ROCK_VERTICAL, position3));
    } else {
        const float xCoordinate = _widthUnit * 0.37f;
        const bool isAlt = RNG::randomBool();
        for (int i = 0; i < 3; i++) {
            const float altFactor = (isAlt) ? (1.0f - 2.0f * float(i % 2)) : 1.0f;
            const auto rockPosition = Vec2(xCoordinate * sign * altFactor, _heightUnit * (0.95f - 0.3f * float(i)));
            spawns.emplace_back(SpawnPoint(Entity::ROLLING_ROCK_DIAGONAL, rockPosition));
        }
    }
    this->spawnCoinPattern(spawns);
}

void LevelGenerator::spawnCoinPattern(std::list<SpawnPoint>& spawns) const
{
    const CoinStrategy strategy = selectCoinStrategyStandalone();
    for (const Vec2& position : strategy.getPositions()) {
        spawns.emplace_back(SpawnPoint(Entity::COLLECT_MONEY, position));
    }
    
    const auto pivot = strategy.getPivot();
    if (pivot != Vec2::ZERO) {
        if (_currentLevel < 4) {
            // 1-gold, enemy, coin
            if (RNG::randomUniform() < 0.2f) {
                spawns.emplace_back(SpawnPoint(Entity::COLLECT_GOLD_BAR, pivot));
            } else {
                const auto enemy = selectEnemyForLevel();
                spawns.emplace_back(SpawnPoint(enemy.entityType, pivot));
            }
        } else {
            if (RNG::randomUniform() < 0.3f) {
                // super gold -1
                spawns.emplace_back(SpawnPoint(Entity::COLLECT_GOLD_BAR_3X, pivot));
            } else {
                const auto enemy = selectEnemyForLevel();
                spawns.emplace_back(SpawnPoint(enemy.entityType, pivot));
            }
        }
    }
}

void LevelGenerator::spawnPowerUp(std::list<SpawnPoint>& spawns) const
{
    const CoinStrategy strategy = (RNG::randomBool()) ? CoinStrategy::makeCircle() : CoinStrategy::makeSquare();
    for (const Vec2& position : strategy.getPositions()) {
        spawns.emplace_back(SpawnPoint(Entity::COLLECT_MONEY, position));
    }
    spawns.emplace_back(SpawnPoint(Entity::POWER_UP_CRACKLE, strategy.getPivot()));
}
