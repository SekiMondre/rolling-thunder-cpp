//
//  PlayerNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef PlayerNode_h
#define PlayerNode_h

#include "axmol.h"

class PlayerNode : public ax::Node
{
public:
    CREATE_FUNC(PlayerNode);
    virtual bool init() override;

private:
    PlayerNode();
    ~PlayerNode();
};

#endif /* PlayerNode_h */
