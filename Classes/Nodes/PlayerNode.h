//
//  PlayerNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef PlayerNode_h
#define PlayerNode_h

#include "axmol.h"

enum PlayerState
{
    INACTIVE,
    ROLLING
};

class PlayerNode : public ax::Node
{
public:
    CREATE_FUNC(PlayerNode);
    virtual bool init() override;
    void update(float deltaTime) override;
    void onInteractionBegin(const ax::Vec2 touchLocation);
    void onInteractionMoved(const ax::Vec2 touchLocation);
    void onInteractionEnded(const ax::Vec2 touchLocation);
    void onInteractionCancelled(const ax::Vec2 touchLocation);
    void applyBump(const ax::Vec2 contactPoint);
    
    bool isInvincible() const;

private:
    PlayerNode();
    ~PlayerNode();
    void setupPhysicsBody();
    
    PlayerState _state;
    ax::Sprite* _sprite;
    ax::Vec2 _touchPosition;
    ax::Vec2 _velocity;
    ax::Vec2 _direction;
    ax::Vec2 _moveDelta;
    ax::Vec2 _decaySpeed;
    ax::Vec2 _bumpForce;
    float _internalAcceleration;
    bool _invincible;
};

#endif /* PlayerNode_h */
