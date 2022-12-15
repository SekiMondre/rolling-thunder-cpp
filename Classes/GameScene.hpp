//
//  GameScene.hpp
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "axmol.h"

//class ObstacleNode;

class GameScene : public ax::Scene
{
public:
    GameScene();
    virtual bool init() override;
    void update(float deltaTime) override;
    CREATE_FUNC(GameScene);
    
private:
    Node* aNode;
};

#endif /* GameScene_hpp */
