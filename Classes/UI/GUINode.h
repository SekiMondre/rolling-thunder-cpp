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
class MenuView;

class GUINode : public ax::Node
{
public:
    CREATE_FUNC(GUINode);
    virtual bool init() override;
    
    void setTransitionBeginCallback(const std::function<void()>& callback);
    void setTransitionEndCallback(const std::function<void()>& callback);
    
    HUDView* getHUD();
    MenuView* getMainMenu();

private:
    GUINode();
    ~GUINode();
    
    void showCredits();
    void dismissActiveView();
    void onDismissFinished();
    
    HUDView* _hud;
    MenuView* _mainMenu;
    
    ax::Node* _activeView;
    
    std::function<void()> _onTransitionBeganCallback;
    std::function<void()> _onTransitionEndedCallback;
};

#endif /* GUINode_h */
