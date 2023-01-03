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
struct SpawnPoint;

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
    
    void resetSpawn(const std::list<SpawnPoint>& spawns);
    
    void test1a();
    void test1b();
    void test1c();
    void test1d();
    void test2a();
    void test2b();
    void test2c();
    void test2d();
    void test3a();
    void test3b();
    void test3c();
    void test4a();
    void test4b();
    
//    void action1();
    
    LevelGenerator* _levelGen;
    Node* _root;
};

#endif /* DebugLevelSectionScene_h */
