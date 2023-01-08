//
//  World.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 22/12/22.
//

#include "World.h"
#include "RollingThunder.h"

USING_NS_AX;

World::World()
    : _updateHierarchy(nullptr)
    , _background_0(nullptr)
    , _background_1(nullptr)
    , _GAME(nullptr)
    , _levelGenerator(nullptr)
    , _shouldSpawnNextSection(false)
{}

World::~World()
{
    _updateHierarchy = nullptr;
    _background_0 = nullptr;
    _background_1 = nullptr;
    _GAME = nullptr;
    
    log("World destroy");
}

bool World::init()
{
    if (!Node::init()) return false;
    
    _GAME = Game::getInstance();
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto winSize = _director->getWinSize();
    
    const float spacing = 152.0f; // MAGIC
    _levelGenerator = std::make_unique<LevelGenerator>(winSize.width * 0.75f, winSize.height, spacing);
    
    this->setupBackground();
    
    _updateHierarchy = Node::create();
    _updateHierarchy->setPosition(origin.x + visibleSize.x * 0.5f, 0.0f);
    addChild(_updateHierarchy);
    
    return true;
}

void World::update(float deltaTime)
{
    if (_GAME->getState() == GameState::IDLE) return;
    
    // TODO: modify speed if needed / game over
    
    this->updateBackground(deltaTime);
    
    if (_shouldSpawnNextSection) {
        
        if (_levelGenerator->isEndOfLevel()) {
            // TODO: rise speed
            const float worldSpeed = 500.0f; // FIXME
            _levelGenerator->generateNextLevel(worldSpeed);
        }
        
        auto spawnList = _levelGenerator->popNextSection();
        
        for (const auto &spawn : spawnList) {
            auto node = NodeFactory::parseEntity(spawn);
            node->setPositionX(spawn.position.x);
            node->setPositionY(spawn.position.y + Game::getSceneHeight());
            _updateHierarchy->addChild(node);
            // TODO: bind player ref if dodge enemy
        }
        _shouldSpawnNextSection = false;
    }
    
    auto children = _updateHierarchy->getChildren();
    for (Node* child : children) {
        child->update(deltaTime);
        if (child->getPositionY() < -100) { /// maybe something like 500+ (half screen), take care not to remove player node
            child->removeFromParentAndCleanup(true);
        }
    }
}

void World::updateBackground(float deltaTime)
{
    float verticalDelta = Game::getInstance()->getScrollingSpeed() * deltaTime;
    float scaledHeight_0 = _background_0->getContentSize().height * _background_0->getScaleY();
    float scaledHeight_1 = _background_1->getContentSize().height * _background_1->getScaleY();
    float yTarget_0 = _background_0->getPositionY() - verticalDelta;
    float yTarget_1 = _background_1->getPositionY() - verticalDelta;
    
    if (yTarget_0 < -scaledHeight_0) {
        yTarget_0 = yTarget_1 + scaledHeight_0;
        _shouldSpawnNextSection = true;
    }
    if (yTarget_1 < -scaledHeight_1) {
        yTarget_1 = yTarget_0 + scaledHeight_1;
        _shouldSpawnNextSection = true;
    }
    _background_0->setPositionY(yTarget_0);
    _background_1->setPositionY(yTarget_1);
}

void World::setupBackground()
{
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    _background_0 = SpriteLoader::load(ImageAsset::BACKGROUND);
    _background_1 = SpriteLoader::load(ImageAsset::BACKGROUND);
    _background_0->setAnchorPoint(Vec2(0.5f, 0.0f));
    _background_1->setAnchorPoint(Vec2(0.5f, 0.0f));
    _background_0->setPosition(origin.x + visibleSize.x * 0.5f, 0.0f); // TODO: set z position
    _background_1->setPosition(origin.x + visibleSize.x * 0.5f, _background_0->getContentSize().height * _background_0->getScaleX());
    addChild(_background_0);
    addChild(_background_1);
}
