//
//  GameOverView.h
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#ifndef GameOverView_h
#define GameOverView_h

#include "axmol.h"

class GameOverView : public ax::Node
{
public:
    CREATE_FUNC(GameOverView);
    virtual bool init() override;

private:
    GameOverView();
    ~GameOverView();
};

#endif /* GameOverView_h */