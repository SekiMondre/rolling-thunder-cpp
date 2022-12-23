//
//  DebugAnimationScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#ifndef DebugAnimationScene_h
#define DebugAnimationScene_h

#include "axmol.h"

class DebugAnimationScene : public ax::Scene
{
public:
    CREATE_FUNC(DebugAnimationScene);
    virtual bool init() override;

private:
    DebugAnimationScene();
    ~DebugAnimationScene();
    void exitScene();
    
    void animateOnce();
};

#endif /* DebugAnimationScene_h */
