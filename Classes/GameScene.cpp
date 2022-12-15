//
//  GameScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#include "GameScene.hpp"
#include "Nodes/ObstacleNode.hpp"

USING_NS_AX;

GameScene::GameScene()
{
    aNode = nullptr;
    log("Game scene load");
}

bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    log("Game scene init"); 
    
    aNode = ObstacleNode::create();
    if (aNode == nullptr) {
        log("ERROR create node");
////        return false;
    }
    aNode->setPosition(Vec2(300, 500));
    addChild(aNode);
    
    this->scheduleUpdate();
    return true;
}

void GameScene::update(float deltaTime)
{
    static float count = 0;
    count += deltaTime;
    if (count > 2) {
        if (aNode != nullptr) {
            log("Removing node...");
            aNode->removeFromParent();
            aNode = nullptr;
        }
    }
    
//    log("Update delta: %f", deltaTime);
}
