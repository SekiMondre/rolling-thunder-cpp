//
//  DebugAnimationScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#ifndef DebugAnimationScene_h
#define DebugAnimationScene_h

#include "axmol.h"

class RollingRockNode;
class EnemyNode;

class DebugAnimationScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugAnimationScene);
    virtual bool init() override;
    void update(float deltaTime) override;

private:
    DebugAnimationScene();
    ~DebugAnimationScene();
    void layoutMenu();
    void exitScene();
    
    void animateOnce();
    
    RollingRockNode* _rockNode;
    EnemyNode* _dodger1;
    EnemyNode* _dodger2;
    ax::Node* _root;
};

#endif /* DebugAnimationScene_h */
