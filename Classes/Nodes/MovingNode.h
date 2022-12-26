//
//  MovingNode.h
//  ConvertUTF
//
//  Created by André Vants on 25/12/22.
//

#ifndef MovingNode_h
#define MovingNode_h

#include "axmol.h"

class MovingNode : public ax::Node
{
public:
    CREATE_FUNC(MovingNode);
    virtual bool init() override;
    void update(float deltaTime) override;
    void setSprite(ax::Sprite* const sprite);

private:
    MovingNode();
    ~MovingNode();
    
    ax::Sprite* _sprite;
};

#endif /* MovingNode_h */
