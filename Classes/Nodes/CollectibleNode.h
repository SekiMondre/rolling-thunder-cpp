//
//  CollectibleNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef CollectibleNode_h
#define CollectibleNode_h

#include "axmol.h"

class CollectibleNode : public ax::Node
{
public:
    CREATE_FUNC(CollectibleNode);
    virtual bool init() override;

private:
    CollectibleNode();
    ~CollectibleNode();
};

#endif /* CollectibleNode_h */