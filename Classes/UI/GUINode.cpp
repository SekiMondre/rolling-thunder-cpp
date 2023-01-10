//
//  GUINode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 03/01/23.
//

#include "GUINode.h"
#include "RollingThunder.h"

USING_NS_AX;

GUINode::GUINode()
{
    // Constructor
}

GUINode::~GUINode()
{
    // Destructor
}

bool GUINode::init()
{
    if (!Node::init()) return false;
    
//    auto mainMenu = MenuView::create();
//    this->addChild(mainMenu);
    
    _hud = HUDView::create();
    this->addChild(_hud);
    
//    auto rank = RankingView::create();
//    rank->setPosition(Vec2(0.0f, 0.0f));
//    this->addChild(rank);
    
//    auto cre = CreditsView::create();
//    this->addChild(cre);
    
    return true;
}

//void GUINode::testCall()
//{
//    log("test call");
//}

HUDView* GUINode::getHUD()
{
    return _hud;
}
