//
//  DebugLevelGenScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef DebugLevelGenScene_h
#define DebugLevelGenScene_h

#include "axmol.h"

class DebugLevelGenScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugLevelGenScene);
    virtual bool init() override;

private:
    DebugLevelGenScene();
    ~DebugLevelGenScene();
    void exitScene();
};

#endif /* DebugLevelGenScene_h */
