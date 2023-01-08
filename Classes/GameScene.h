//
//  GameScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#ifndef GameScene_h
#define GameScene_h

#include "axmol.h"

class Game;
class World;
class PlayerNode;

class GameScene : public ax::Scene
{
public:
    CREATE_FUNC(GameScene);
    virtual bool init() override;
    void update(float deltaTime) override;
    
private:
    GameScene();
    ~GameScene();
    
    void startGame();
    
    bool onTouchBegan(ax::Touch* touch, ax::Event* event);
    void onTouchMoved(ax::Touch* touch, ax::Event* event);
    void onTouchEnded(ax::Touch* touch, ax::Event* event);
    void onTouchCancelled(ax::Touch* touch, ax::Event* event);
    bool onContactBegin(ax::PhysicsContact& contact);
    
    Game* _GAME;
    World* _world;
    PlayerNode* _player;
};

#endif /* GameScene_h */
