//
//  DebugSpriteScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef DebugSpriteScene_h
#define DebugSpriteScene_h

#include "axmol.h"

class DebugSpriteScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugSpriteScene);
    virtual bool init() override;

private:
    DebugSpriteScene();
    ~DebugSpriteScene();
    void exitScene();
};

#endif /* DebugSpriteScene_h */
