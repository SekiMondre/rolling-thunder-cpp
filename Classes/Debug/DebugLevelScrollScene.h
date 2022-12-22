//
//  DebugLevelScrollScene.h
//  ConvertUTF
//
//  Created by André Vants on 22/12/22.
//

#ifndef DebugLevelScrollScene_h
#define DebugLevelScrollScene_h

#include "axmol.h"

class World;

class DebugLevelScrollScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugLevelScrollScene);
    virtual bool init() override;
    void update(float deltaTime) override;

private:
    DebugLevelScrollScene();
    ~DebugLevelScrollScene();
    void layoutMenu();
    void exitScene();
    
    World* _world;
};

#endif /* DebugLevelScrollScene_h */
