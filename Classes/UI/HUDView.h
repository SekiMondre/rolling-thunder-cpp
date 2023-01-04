//
//  HUDView.h
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#ifndef HUDView_h
#define HUDView_h

#include "axmol.h"

class HUDView : public ax::Node
{
public:
    CREATE_FUNC(HUDView);
    virtual bool init() override;

private:
    HUDView();
    ~HUDView();
};

#endif /* HUDView_h */