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

private:
    MenuView();
    ~MenuView();
    
    void testCall();
};

#endif /* MenuView_h */
