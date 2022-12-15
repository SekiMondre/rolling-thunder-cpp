//
//  DebugMenuScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef DebugMenuScene_h
#define DebugMenuScene_h

#include "axmol.h"

class DebugMenuScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugMenuScene);
    virtual bool init() override;

private:
    DebugMenuScene();
    ~DebugMenuScene();
};

#endif /* DebugMenuScene_h */