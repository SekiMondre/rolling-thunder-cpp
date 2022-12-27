//
//  RollingRockNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef RollingRockNode_h
#define RollingRockNode_h

#include "axmol.h"
#include "Game/RollingRock.h"

class RollingRockNode : public ax::Node
{
public:
    static RollingRockNode* createWithType(RollingRock type);
    virtual bool init() override;
    void update(float deltaTime) override;
    
private:
    RollingRockNode(RollingRock type);
    ~RollingRockNode();
    void setupPhysicsBody();
    void bounce();
    
    RollingRock _type;
    ax::Sprite* _sprite;
    ax::Sprite* _shadowSprite;
    ax::Vec2 _direction;
    bool _isRolling;
    float _rollStartFactor; // % of the screen height the rock start rolling
    
    float _bounceSpeed;
    float _rotationSpeed;
};

#endif /* RollingRockNode_h */
