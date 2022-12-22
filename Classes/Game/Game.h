//
//  Game.h
//  RollingThunderCpp
//
//  Created by André Vants on 21/12/22.
//

#ifndef Game_h
#define Game_h

#include "axmol.h"

class Game
{
public:
    static Game* getInstance();
    static ax::Vec2 getSceneSize();
    static float getSceneWidth();
    static float getSceneHeight();
    
    void reset();
    
private:
    Game();
    int _playerHealth;
};

#endif /* Game_h */
