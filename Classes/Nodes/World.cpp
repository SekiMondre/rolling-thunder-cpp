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
{}

World::~World()
{
    _updateHierarchy = nullptr;
    _background_0 = nullptr;
    _background_1 = nullptr;
    _GAME = nullptr;
}

bool World::init()
{
    if (!Node::init()) return false;
    
    _GAME = Game::getInstance();
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    this->setupBackground();
    
    _updateHierarchy = Node::create();
    _updateHierarchy->setPosition(origin.x + visibleSize.x * 0.5f, 0.0f);
    addChild(_updateHierarchy);
    
    return true;
}

void World::update(float deltaTime)
{
    if (_GAME->getState() == GameState::IDLE) return;
    
    // spawn test ----------
    static float count = 0.0;
    count += deltaTime;
    if (count > 1.5f)
    {
        count = 0.0;
        
        auto nodeA = ObstacleNode::createWithType(Obstacle::BIG);
        nodeA->setPosition(-100.0f, Game::getSceneHeight() + 100);
        _updateHierarchy->addChild(nodeA);
        
        auto nodeB = CollectibleNode::create();
        nodeB->setPosition(100.0f, Game::getSceneHeight() + 100);
        _updateHierarchy->addChild(nodeB);

        auto nodeC = EnemyNode::create();
        nodeC->setPosition(0.0f, Game::getSceneHeight() + 280);
        _updateHierarchy->addChild(nodeC);
    }
    // end test ----------
    
    auto children = _updateHierarchy->getChildren();
    for (Node* child : children) {
        child->update(deltaTime);
        if (child->getPositionY() < -100) { /// maybe something like 500+ (half screen), take care not to remove player node
            child->removeFromParentAndCleanup(true);
        }
    }
    this->updateBackground(deltaTime);
    // TODO: Did finish update (spawn nodes if needed)
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
    }
    if (yTarget_1 < -scaledHeight_1) {
        yTarget_1 = yTarget_0 + scaledHeight_1;
    }
    _background_0->setPositionY(yTarget_0);
    _background_1->setPositionY(yTarget_1);
}

void World::setupBackground()
{
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    _background_0 = SpriteLoader::load(BACKGROUND);
    _background_1 = SpriteLoader::load(BACKGROUND);
    _background_0->setAnchorPoint(Vec2(0.5f, 0.0f));
    _background_1->setAnchorPoint(Vec2(0.5f, 0.0f));
    _background_0->setPosition(origin.x + visibleSize.x * 0.5f, 0.0f); // TODO: set z position
    _background_1->setPosition(origin.x + visibleSize.x * 0.5f, _background_0->getContentSize().height * _background_0->getScaleX());
    addChild(_background_0);
    addChild(_background_1);
}
