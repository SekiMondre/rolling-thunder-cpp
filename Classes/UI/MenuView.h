//
//  MenuView.h
//  RollingThunderCpp
//
//  Created by André Vants on 03/01/23.
//

#ifndef MenuView_h
#define MenuView_h

#include "axmol.h"

class MenuView : public ax::Node
{
public:
    CREATE_FUNC(MenuView);
    virtual bool init() override;
    
    void setCreditsCallback(const ax::ccMenuCallback& callback);
    
    void blinkStartLabelWithDelay(float d);

private:
    MenuView();
    ~MenuView();
    
    void showCredits();
    void dismissActiveView();
    void onDismissFinished();
    
    ax::Node* _startLabel;
    
    ax::MenuItem* _creditsButton;
//    ax::MenuItem* _rankingButton;
};

#endif /* MenuView_h */
