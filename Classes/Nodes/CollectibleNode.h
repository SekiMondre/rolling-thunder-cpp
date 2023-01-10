//
//  CollectibleNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef CollectibleNode_h
#define CollectibleNode_h

#include "axmol.h"
#include "Game/Collectible.h"

class CollectibleNode : public ax::Node
{
public:
    static CollectibleNode* createWithType(Collectible type);
    virtual bool init() override;
    void update(float deltaTime) override;
    
    const Collectible& getType() const;

private:
    CollectibleNode(Collectible type);
    ~CollectibleNode();
    void setupPhysicsBody();
    
    Collectible _type;
    ax::Sprite* _sprite;
};

#endif /* CollectibleNode_h */
