//
//  DebugSoundScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef DebugSoundScene_h
#define DebugSoundScene_h

#include "axmol.h"

class DebugSoundScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugSoundScene);
    virtual bool init() override;

private:
    DebugSoundScene();
    ~DebugSoundScene();
    void exitScene();
};

#endif /* DebugSoundScene_h */
