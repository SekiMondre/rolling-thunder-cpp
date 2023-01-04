//
//  RankingView.h
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#ifndef RankingView_h
#define RankingView_h

#include "axmol.h"

class RankingView : public ax::Node
{
public:
    CREATE_FUNC(RankingView);
    virtual bool init() override;

private:
    RankingView();
    ~RankingView();
};

#endif /* RankingView_h */