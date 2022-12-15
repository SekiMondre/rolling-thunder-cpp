//
//  EnemyNode.h
//  ConvertUTF
//
//  Created by André Vants on 15/12/22.
//

#ifndef EnemyNode_h
#define EnemyNode_h

#include "axmol.h"

class EnemyNode : public ax::Node
{
public:
    CREATE_FUNC(EnemyNode);
    virtual bool init() override;

private:
    EnemyNode();
    ~EnemyNode();
};

#endif /* EnemyNode_h */
