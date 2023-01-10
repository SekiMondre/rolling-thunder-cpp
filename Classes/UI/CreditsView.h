//
//  CreditsView.h
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#ifndef CreditsView_h
#define CreditsView_h

#include "axmol.h"

class CreditsView : public ax::Node
{
public:
    CREATE_FUNC(CreditsView);
    virtual bool init() override;
    
    void setDismissCallback(const ax::ccMenuCallback& callback);
    
private:
    CreditsView();
    ~CreditsView();
    
    ax::MenuItem* _backButton;
};

#endif /* CreditsView_h */
