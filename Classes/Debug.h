//
//  Debug.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef Debug_h
#define Debug_h

#include "Debug/DebugMenuScene.h"
#include "Debug/DebugAnimationScene.h"
#include "Debug/DebugCollisionScene.h"

namespace Debug
{
    ax::MenuItem* createColorButton(std::string_view text, float fontSize, ax::Vec2 size, ax::Color4B color);
}

#endif /* Debug_h */
