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
    void presentGameScene();
    void presentSpriteTest();
    void presentAnimationTest();
    void presentCollisionTest();
    void presentLevelModulesTest();
    void presentLevelGenTest();
    void presentSoundTest();
};

#endif /* DebugMenuScene_h */
