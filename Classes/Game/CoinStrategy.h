//
//  CoinStrategy.h
//  RollingThunderCpp
//
//  Created by André Vants on 27/12/22.
//

#ifndef CoinStrategy_h
#define CoinStrategy_h

#include "axmol.h"

class CoinStrategy
{
public:
    inline static float getWidthUnit();
    inline static float getHeightUnit();
    inline static ax::Vec2 defaultCenter();
    
    static CoinStrategy makeRow(const ax::Vec2& center, const int count, const float spacing);
    static CoinStrategy makeZigZagRow(const ax::Vec2 &center, const int count, const float spacing);
    static CoinStrategy makeSmallRhombus(const ax::Vec2& center);
    static CoinStrategy makeSineWave();
    static CoinStrategy makeHalfSineWave();
    static CoinStrategy makeCircle();
    static CoinStrategy makeSquare();
    static CoinStrategy makeBigRhombus();
    
    const std::vector<ax::Vec2>& getPositions() const {
        return _positions;
    }
    
    const ax::Vec2& getPivot() const {
        return _pivotPosition;
    }
    
    CoinStrategy(std::vector<ax::Vec2> positions, ax::Vec2 pivot) : _positions(positions), _pivotPosition(pivot) {}
//    virtual ~CoinStrategy() {}
    
private:
    std::vector<ax::Vec2> _positions;
    ax::Vec2 _pivotPosition;
};



//class CoinRow : public CoinStrategy
//{
//public:
//    static CoinStrategy makeDefault();
//    CoinRow(ax::Vec2 center, int count, float spacing);
//};
//
//
//
//class CoinZigZagRow : public CoinStrategy
//{
//public:
//    static CoinStrategy makeDefault();
//    CoinZigZagRow(ax::Vec2 center, int count, float spacing);
//};
//
//
//
//class CoinSmallRhombus : public CoinStrategy
//{
//public:
//    static CoinStrategy makeDefault();
//    CoinSmallRhombus(ax::Vec2 center);
//};
//
//
//
//class CoinSineWave : public CoinStrategy
//{
//public:
//    static CoinStrategy makeDefault();
//    CoinSineWave(int count);
//};
//
//
//
//class CoinHalfSineWave : public CoinStrategy
//{
//public:
//    static CoinStrategy makeDefault();
//    CoinHalfSineWave(int count);
//};
//
//
//
//class CoinCircle : public CoinStrategy
//{
//public:
//    static CoinStrategy makeDefault();
//    CoinCircle(ax::Vec2 center, float radius);
//};
//
//
//
//class CoinSquare : public CoinStrategy
//{
//public:
//    static CoinStrategy makeDefault();
//    CoinSquare(ax::Vec2 center, float halfSide);
//};
//
//
//
//class CoinBigRhombus : public CoinStrategy
//{
//public:
//    static CoinStrategy makeDefault();
//    CoinBigRhombus(ax::Vec2 center);
//};

#endif /* CoinStrategy_h */
