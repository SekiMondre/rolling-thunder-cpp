//
//  ObstacleNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 14/12/22.
//

#ifndef ObstacleNode_h
#define ObstacleNode_h

#include "axmol.h"
#include "Game/Obstacle.h"

class ObstacleNode : public ax::Node
{
public:
//    CREATE_FUNC(ObstacleNode);
    static ObstacleNode* create(); // Remove default create func
    static ObstacleNode* createWithType(Obstacle type);
    virtual bool init() override;
    void update(float deltaTime) override;
    
    const Obstacle& getType() const;

private:
    ObstacleNode(Obstacle type);
    ~ObstacleNode();
    void setupPhysicsBody();
    
    Obstacle _type;
    ax::Sprite* _sprite;
};

#endif /* ObstacleNode_h */
