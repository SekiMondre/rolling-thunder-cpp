//
//  ObstacleNode.h
//  RollingThunderCpp
//
//  Created by André Vants on 14/12/22.
//

#ifndef ObstacleNode_h
#define ObstacleNode_h

#include "axmol.h"

struct Obstacle
{
    Obstacle(std::string _imageName, ax::Vec2 _size);
    
    std::string imageName;
    ax::Vec2 size = ax::Vec2::ZERO;
    
    static const Obstacle BIG;
    static const Obstacle SMALL;
};

// --------------------------------------------------------------------------------

class ObstacleNode : public ax::Node
{
public:
//    CREATE_FUNC(ObstacleNode);
    static ObstacleNode* create();
    static ObstacleNode* createWithType(Obstacle type);
    virtual bool init() override;
    void update(float deltaTime) override;

private:
    ObstacleNode();
    ~ObstacleNode();
    void setupPhysicsBody();
    
    ax::Sprite* _sprite;
    ax::Vec2 _size;
};

#endif /* ObstacleNode_h */
