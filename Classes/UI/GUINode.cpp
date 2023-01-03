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
    
    auto mainMenu = MenuView::create();
    this->addChild(mainMenu);
    
    return true;
}

//void GUINode::testCall()
//{
//    log("test call");
//}
