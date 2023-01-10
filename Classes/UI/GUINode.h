//
//  GUINode.h
//  ConvertUTF
//
//  Created by André Vants on 03/01/23.
//

#ifndef GUINode_h
#define GUINode_h

#include "axmol.h"

class HUDView;

class GUINode : public ax::Node
{
public:
    CREATE_FUNC(GUINode);
    virtual bool init() override;
    
    HUDView* getHUD();

private:
    GUINode();
    ~GUINode();
    
//    void testCall();
    HUDView* _hud;
};

#endif /* GUINode_h */
