//
//  RollingRockNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef RollingRockNode_h
#define RollingRockNode_h

#include "axmol.h"

enum RollingRockType
{
    VERTICAL,
    DIAGONAL,
    NONE
};

class RollingRockNode : public ax::Node
{
public:
    CREATE_FUNC(RollingRockNode);
    virtual bool init() override;
    void setType(RollingRockType type);
    void update(float deltaTime) override;
    
private:
    RollingRockNode();
    ~RollingRockNode();
    void setupPhysicsBody();
    void bounce();
    
    RollingRockType _type;
    ax::Sprite* _sprite;
    ax::Sprite* _shadowSprite;
    ax::Vec2 _direction;
    bool _isRolling;
    float _rollStartFactor; // % of the screen height the rock start rolling
    
    float _bounceSpeed;
    float _rotationSpeed;
};

#endif /* RollingRockNode_h */
