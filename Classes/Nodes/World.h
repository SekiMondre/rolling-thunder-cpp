//
//  World.h
//  RollingThunderCpp
//
//  Created by André Vants on 22/12/22.
//

#ifndef World_h
#define World_h

#include "axmol.h"

class World : public ax::Node
{
public:
    CREATE_FUNC(World);
    virtual bool init() override;
    void update(float deltaTime) override;

private:
    World();
    ~World();
    
    ax::Node* _background_0;
    ax::Node* _background_1;
};

#endif /* World_h */
