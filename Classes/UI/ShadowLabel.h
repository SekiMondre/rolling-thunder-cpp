//
//  ShadowLabel.h
//  RollingThunderCpp
//
//  Created by André Vants on 03/01/23.
//

#ifndef ShadowLabel_h
#define ShadowLabel_h

#include "axmol.h"

class ShadowLabel : public ax::Node
{
public:
    CREATE_FUNC(ShadowLabel);
    virtual bool init() override;
    
    void setString(std::string text);
    void setFont(std::string font);
    void setFontSize(float fontSize);
    
    void setAnchorPoint(const ax::Vec2 &anchorPoint) override;

private:
    ShadowLabel();
    ~ShadowLabel();
    
    ax::Label* _frontLabel;
    ax::Label* _backLabel;
};

#endif /* ShadowLabel_h */
