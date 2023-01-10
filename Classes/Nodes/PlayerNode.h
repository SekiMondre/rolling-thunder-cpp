//
//  PlayerNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef PlayerNode_h
#define PlayerNode_h

#include "axmol.h"

enum class PlayerState
{
    INACTIVE,
    ROLLING
};

class PlayerNode : public ax::Node
{
public:
    CREATE_FUNC(PlayerNode);
    virtual bool init() override;
    
    bool isInvincible() const;
    
    void setRollingState();
    void setInvincibleFrames();
    void applyBump(const ax::Vec2 contactPoint);
    
    void update(float deltaTime) override;
    void onInteractionBegin(const ax::Vec2 touchLocation);
    void onInteractionMoved(const ax::Vec2 touchLocation);
    void onInteractionEnded(const ax::Vec2 touchLocation);
    void onInteractionCancelled(const ax::Vec2 touchLocation);
    
private:
    PlayerNode();
    ~PlayerNode();
    void setupPhysicsBody();
    void endInvincibleFrames();
    
    ax::Sprite* _sprite;
    ax::Animation* _idleAnimation; //
//    ax::Animation* _rollAnimation;
//    ax::Animation* _deadAnimation;
//    ax::ActionInterval* _idleAnimation;
//    ax::ActionInterval* _rollAnimation;
//    ax::ActionInterval* _deadAnimation;
    
    PlayerState _state;
    
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
