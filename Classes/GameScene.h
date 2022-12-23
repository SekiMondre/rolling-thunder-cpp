//
//  GameScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#ifndef GameScene_h
#define GameScene_h

#include "axmol.h"
#include "RollingThunder.h"

class World;

class GameScene : public ax::Scene
{
public:
    CREATE_FUNC(GameScene);
    virtual bool init() override;
    void update(float deltaTime) override;
    
private:
    GameScene();
    ~GameScene();
    
    bool onTouchBegan(ax::Touch* touch, ax::Event* event);
    void onTouchMoved(ax::Touch* touch, ax::Event* event);
    void onTouchEnded(ax::Touch* touch, ax::Event* event);
    void onTouchCancelled(ax::Touch* touch, ax::Event* event);
    bool onContactBegin(ax::PhysicsContact& contact);
    
    World* _world;
};

#endif /* GameScene_h */
