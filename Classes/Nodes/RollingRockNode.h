//
//  RollingRockNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef RollingRockNode_h
#define RollingRockNode_h

#include "axmol.h"

class RollingRockNode : public ax::Node
{
public:
    CREATE_FUNC(RollingRockNode);
    virtual bool init() override;

private:
    RollingRockNode();
    ~RollingRockNode();
};

#endif /* RollingRockNode_h */