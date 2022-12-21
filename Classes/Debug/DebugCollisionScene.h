//
//  DebugCollisionScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef DebugCollisionScene_h
#define DebugCollisionScene_h

#include "axmol.h"

class DebugCollisionScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugCollisionScene);
    virtual bool init() override;

private:
    DebugCollisionScene();
    ~DebugCollisionScene();
    bool onContactBegin(ax::PhysicsContact& contact);
    void layoutMenu();
    void resetNodes();
    void exitScene();
};

#endif /* DebugCollisionScene_h */
