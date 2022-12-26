//
//  EnemyNode.h
//  ConvertUTF
//
//  Created by André Vants on 15/12/22.
//

#ifndef EnemyNode_h
#define EnemyNode_h

#include "axmol.h"
#include "Game/Enemy.h"

class EnemyNode : public ax::Node
{
public:
//    CREATE_FUNC(EnemyNode);
    static EnemyNode* createWithType(Enemy type);
    virtual bool init() override;
    void update(float deltaTime) override;
    void simpleDodge();

private:
    EnemyNode(Enemy type);
    ~EnemyNode();
    void setupPhysicsBody();
    void dodge(const int direction);
    void spawnAfterimage();
    
    Enemy _type;
    ax::Sprite* _sprite;
    bool _hasDodged;
};

#endif /* EnemyNode_h */
