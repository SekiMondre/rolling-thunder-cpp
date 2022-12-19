//
//  DebugLevelSectionScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef DebugLevelSectionScene_h
#define DebugLevelSectionScene_h

#include "axmol.h"

class DebugLevelSectionScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugLevelSectionScene);
    virtual bool init() override;

private:
    DebugLevelSectionScene();
    ~DebugLevelSectionScene();
    void exitScene();
};

#endif /* DebugLevelSectionScene_h */
