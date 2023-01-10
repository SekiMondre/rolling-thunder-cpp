//
//  HUDView.h
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#ifndef HUDView_h
#define HUDView_h

#include "axmol.h"

struct Score;

class ShadowLabel;

class HUDView : public ax::Node
{
public:
    CREATE_FUNC(HUDView);
    virtual bool init() override;
    
    void updateScore(Score score);

private:
    HUDView();
    ~HUDView();
    
    ShadowLabel* _timeLabel;
    ShadowLabel* _coinLabel;
    ShadowLabel* _tr00scoreLabel;
};

#endif /* HUDView_h */
