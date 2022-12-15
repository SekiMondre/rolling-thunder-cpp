//
//  ObstacleNode.hpp
//  RollingThunderCpp
//
//  Created by André Vants on 14/12/22.
//

#ifndef ObstacleNode_hpp
#define ObstacleNode_hpp

#include "axmol.h"

class ObstacleNode : public ax::Node
{
public:
    CREATE_FUNC(ObstacleNode);
    virtual bool init() override;

private:
    ObstacleNode();
    ~ObstacleNode();
    ax::Sprite* _sprite;
};

#endif /* ObstacleNode_hpp */
