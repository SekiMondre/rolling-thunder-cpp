//
//  DebugLevelSectionScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef DebugLevelSectionScene_h
#define DebugLevelSectionScene_h

#include "axmol.h"

class LevelGenerator;

class DebugLevelSectionScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugLevelSectionScene);
    virtual bool init() override;

private:
    DebugLevelSectionScene();
    ~DebugLevelSectionScene();
    void layoutMenu();
    void exitScene();
    
    void action1();
    
    LevelGenerator* _levelGen;
    Node* _root;
};

#endif /* DebugLevelSectionScene_h */
