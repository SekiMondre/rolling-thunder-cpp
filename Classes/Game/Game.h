//
//  Game.h
//  RollingThunderCpp
//
//  Created by André Vants on 21/12/22.
//

#ifndef Game_h
#define Game_h

#include "axmol.h"

enum class GameState
{
    IDLE,
    ACTIVE,
    GAMEOVER
};

class Game
{
public:
    static Game* getInstance();
    
    static ax::Vec2 getSceneSize();
    static float getSceneWidth();
    static float getSceneHeight();
    
    void reset();
    
    GameState getState();
    void setState(GameState state);
    
    float getScrollingSpeed();
    void setScrollingSpeed(float speed);
    
    int getPlayerHealth();
    void damagePlayerHealth();
    
private:
    Game();
    GameState _state;
    int _playerHealth;
    float _scrollingSpeed;
};

#endif /* Game_h */
