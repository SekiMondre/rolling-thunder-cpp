//
//  EnemyNode.h
//  ConvertUTF
//
//  Created by André Vants on 15/12/22.
//

#ifndef EnemyNode_h
#define EnemyNode_h

#include "axmol.h"

enum Enemy
{
    NORMAL,
    BIG,
    DODGER
};

class EnemyNode : public ax::Node
{
public:
    CREATE_FUNC(EnemyNode);
    virtual bool init() override;
    void setType(const Enemy type);
    void update(float deltaTime) override;
    void simpleDodge();

private:
    EnemyNode();
    ~EnemyNode();
    void setupPhysicsBody();
    void dodge(const int direction);
    void spawnAfterimage();
    
    Enemy _type;
    ax::Sprite* _sprite;
    bool _hasDodged;
};

#endif /* EnemyNode_h */
