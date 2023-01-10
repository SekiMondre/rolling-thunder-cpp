//
//  GUINode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 03/01/23.
//

#include "GUINode.h"
#include "RollingThunder.h"

USING_NS_AX;

const float VIEW_TRANSITION_DURATION = 0.5f;

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
    
    _mainMenu = MenuView::create();
    _hud = HUDView::create();
    
    this->addChild(_mainMenu);
    this->addChild(_hud);
    
    _hud->setVisible(false);
    
//    auto rank = RankingView::create();
//    rank->setPosition(Vec2(0.0f, 0.0f));
//    this->addChild(rank);
    
    _mainMenu->setCreditsCallback(AX_CALLBACK_0(GUINode::showCredits, this));
    
    return true;
}

MenuView* GUINode::getMainMenu()
{
    return _mainMenu;
}

HUDView* GUINode::getHUD()
{
    return _hud;
}

void GUINode::setTransitionBeginCallback(const std::function<void()>& callback)
{
    _onTransitionBeganCallback = callback;
}

void GUINode::setTransitionEndCallback(const std::function<void()>& callback)
{
    _onTransitionEndedCallback = callback;
}

void GUINode::showCredits()
{
    if (_activeView) return;
    _onTransitionBeganCallback();
    
    auto viewSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    auto view = CreditsView::create();
    view->setDismissCallback(AX_CALLBACK_0(GUINode::dismissActiveView, this));
    _activeView = view;
    addChild(view);
    view->setPosition(0.0f, origin.y + viewSize.height);
    auto moveToView = MoveTo::create(VIEW_TRANSITION_DURATION, Vec2(0.0f, origin.y));
    auto easeMove = EaseCubicActionInOut::create(moveToView->clone());
    view->runAction(easeMove);
}

void GUINode::dismissActiveView()
{
    if (!_activeView) return;
    
    auto moveOut = MoveTo::create(VIEW_TRANSITION_DURATION, Vec2(0.0f, _director->getVisibleSize().height));
    auto dismissAction = Sequence::create(EaseCubicActionInOut::create(moveOut->clone()),
                                          RemoveSelf::create(),
                                          CallFunc::create(AX_CALLBACK_0(GUINode::onDismissFinished, this)),
                                          nullptr);
    _activeView->runAction(dismissAction);
}

void GUINode::onDismissFinished()
{
    _activeView = nullptr;
    _onTransitionEndedCallback();
}
