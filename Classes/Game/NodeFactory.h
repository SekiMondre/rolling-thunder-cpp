//
//  NodeFactory.h
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#ifndef NodeFactory_h
#define NodeFactory_h

#include "axmol.h"
#include "RollingThunder.h"

class NodeFactory
{
public:
    static ax::Node* parseEntity(const SpawnPoint spawnPoint);
    
private:
    NodeFactory();
};

#endif /* NodeFactory_h */
