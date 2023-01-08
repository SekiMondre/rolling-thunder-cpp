//
//  World.h
//  RollingThunderCpp
//
//  Created by André Vants on 22/12/22.
//

#ifndef World_h
#define World_h

#include "axmol.h"

class Game;
class LevelGenerator;

class World : public ax::Node
{
public:
    CREATE_FUNC(World);
    virtual bool init() override;
    void update(float deltaTime) override;

    ax::Node* _updateHierarchy;
    
private:
    World();
    ~World();
    
    void setupBackground();
    void updateBackground(float deltaTime);
    
//    ax::Node* _updateHierarchy;
    ax::Node* _background_0;
    ax::Node* _background_1;
    
    Game* _GAME;
    
    std::unique_ptr<LevelGenerator> _levelGenerator;
    
    bool _shouldSpawnNextSection;
};

#endif /* World_h */
