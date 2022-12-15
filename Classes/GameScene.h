//
//  GameScene.h
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#ifndef GameScene_h
#define GameScene_h

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

#endif /* GameScene_h */
