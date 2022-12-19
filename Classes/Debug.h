//
//  Debug.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef Debug_h
#define Debug_h

#include "Debug/DebugMenuScene.h"
#include "Debug/DebugSpriteScene.h"
#include "Debug/DebugAnimationScene.h"
#include "Debug/DebugCollisionScene.h"
#include "Debug/DebugLevelSectionScene.h"
#include "Debug/DebugLevelGenScene.h"
#include "Debug/DebugSoundScene.h"
#include "Metadata.h"

namespace Debug
{
    ax::MenuItem* createColorButton(std::string_view text, float fontSize, ax::Vec2 size, ax::Color4B color);
    ax::MenuItem* createColorButton(std::string_view text, float fontSize, ax::Vec2 size, ax::Color4B color, std::string_view font);
    ax::MenuItem* createExitButton(const ax::ccMenuCallback &callback);
}

#endif /* Debug_h */
