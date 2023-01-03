//
//  CoinStrategy.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 27/12/22.
//

#include "CoinStrategy.h"
#include "RollingThunder.h"

USING_NS_AX;

inline float CoinStrategy::getWidthUnit()
{
    return Game::getSceneWidth() * 0.75f; // Legacy width: 768 -> 576 (og)
}

inline float CoinStrategy::getHeightUnit()
{
    return Game::getSceneHeight();
}

inline Vec2 CoinStrategy::defaultCenter()
{
    return Vec2(0.0f, CoinStrategy::getHeightUnit() * 0.5f);
}

// MARK: - Static Factory Methods

CoinStrategy CoinStrategy::makeRow(const Vec2 &center, const int count, const float spacing)
{
    std::vector<Vec2> positions;
    positions.reserve(count);
    for (int i = 0; i < count; i++) {
        float heightDelta = spacing * (i - count / 2 + 0.5f * (1 - count % 2));
        positions.emplace_back(Vec2(center.x, center.y + heightDelta));
    }
    return CoinStrategy(positions, Vec2::ZERO);
}

CoinStrategy CoinStrategy::makeZigZagRow(const Vec2 &center, const int count, const float spacing)
{
    const float xDelta = CoinStrategy::getWidthUnit() * 0.05f;
    std::vector<Vec2> positions;
    positions.reserve(count);
    for (int i = 0; i < count; i++) {
        int side = (i % 2) * 2 - 1;
        float heightDelta = spacing * (i - count / 2 + 0.5f * (1 - count % 2));
        positions.emplace_back(Vec2(center.x + side * xDelta, center.y + heightDelta));
    }
    return CoinStrategy(positions, Vec2::ZERO);
}

CoinStrategy CoinStrategy::makeSmallRhombus(const Vec2 &center)
{
    const float dx = CoinStrategy::getWidthUnit() * 0.08f;
    const float dy = CoinStrategy::getHeightUnit() * 0.09f;
    std::vector<Vec2> positions = {
        center + Vec2(0.0f, dy),
        center + Vec2(0.0f, -dy),
        center + Vec2(dx, 0.0f),
        center + Vec2(-dx, 0.0f)
    };
    return CoinStrategy(positions, Vec2::ZERO);
}

CoinStrategy CoinStrategy::makeSineWave()
{
    const int count = 9;
    const float amplitude = CoinStrategy::getWidthUnit() * 0.21f;
    const float heightDelta = CoinStrategy::getHeightUnit() / float(count * 2);
    const float direction = float(RNG::randomSign());
    
    std::vector<Vec2> positions;
    positions.reserve(count);
    for (int i = 0; i < count; i++) {
        positions.emplace_back(Vec2(sin(M_PI_4 * float(i)) * amplitude * direction, heightDelta * float(1 + 2 * i)));
    }
    return CoinStrategy(positions, Vec2::ZERO);
}

CoinStrategy CoinStrategy::makeHalfSineWave()
{
    const int count = 9;
    const float amplitude = CoinStrategy::getWidthUnit() * 0.21f;
    const float heightDelta = CoinStrategy::getHeightUnit() / float(count * 2);
    const float direction = float(RNG::randomSign());
    
    std::vector<Vec2> positions;
    positions.reserve(count);
    for (int i = 0; i < count; i++) {
        positions.emplace_back(Vec2(cos(M_PI_4 * 0.5f * float(i)) * amplitude * direction, heightDelta * float(1 + 2 * i)));
    }
    return CoinStrategy(positions, Vec2::ZERO);
}

CoinStrategy CoinStrategy::makeCircle()
{
    const Vec2 center = CoinStrategy::defaultCenter();
    const float radius = 152.0f; // Magic number | lane spacing
    
    std::vector<Vec2> positions;
    positions.reserve(8);
    for (int i = 0; i < 8; i++) {
        positions.emplace_back(Vec2(center.x + radius * cos(M_PI_4 * float(i)), center.y + radius * sin(M_PI_4 * float(i))));
    }
    return CoinStrategy(positions, center);
}

CoinStrategy CoinStrategy::makeSquare()
{
    const Vec2 center = CoinStrategy::defaultCenter();
    const float halfSide = 152.0f; // Magic number | lane spacing
    
    std::vector<Vec2> positions;
    positions.reserve(8);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != 1 || j != 1) {
                positions.emplace_back(Vec2(center.x + float(i - 1) * halfSide, center.y + float(j - 1) * halfSide));
            }
        }
    }
    return CoinStrategy(positions, center);
}

CoinStrategy CoinStrategy::makeBigRhombus()
{
    const Vec2 center = CoinStrategy::defaultCenter();
    const float vOffset = CoinStrategy::getHeightUnit() * 0.12f;
    const float hOffset = vOffset * 0.66f;
    
    int x_dir = -1;
    int y_dir = -1;
    int x = 2;
    int y = 0;
    
    std::vector<Vec2> positions;
    positions.reserve(8);
    for (int i = 0; i < 8; i++) {
        positions.emplace_back(Vec2(center.x + x * hOffset, center.y + y * vOffset));
        x += x_dir;
        y += y_dir;
        if (x == 2 || x == -2) {
            x_dir = -x_dir;
        }
        if (y == 2 || y == -2) {
            y_dir = -y_dir;
        }
    }
    return CoinStrategy(positions, center);
}

//// MARK: - Coin Row
//
//CoinStrategy CoinRow::makeDefault()
//{
//    return CoinRow(CoinStrategy::defaultCenter(), 10, CoinStrategy::getHeightUnit() / 10);
//}
//
//CoinRow::CoinRow(Vec2 center, int count, float spacing)
//{
//    for (int i = 0; i < count; i++) {
//        float heightDelta = spacing * (i - count / 2 + 0.5f * (1 - count % 2));
//        _positions.push_back(Vec2(center.x,
//                                  center.y + heightDelta));
//    }
//}
//
//// MARK: - Coin ZigZag Row
//
//CoinStrategy CoinZigZagRow::makeDefault()
//{
//    return CoinZigZagRow(CoinStrategy::defaultCenter(), 10, CoinStrategy::getHeightUnit() * 0.1f);
//}
//
//CoinZigZagRow::CoinZigZagRow(Vec2 center, int count, float spacing)
//{
//    float xDelta = CoinStrategy::getWidthUnit() * 0.05f;
//    for (int i = 0; i < count; i++) {
//        int side = (i % 2) * 2 - 1;
//        float heightDelta = spacing * (i - count / 2 + 0.5f * (1 - count % 2));
//        _positions.push_back(Vec2(center.x + side * xDelta,
//                                  center.y + heightDelta));
//    }
//}
//
//// MARK: - Coin Small Rhombus
//
//CoinStrategy CoinSmallRhombus::makeDefault()
//{
//    return CoinSmallRhombus(CoinStrategy::defaultCenter());
//}
//
//CoinSmallRhombus::CoinSmallRhombus(Vec2 center)
//{
//    float dx = CoinStrategy::getWidthUnit() * 0.08f;
//    float dy = CoinStrategy::getHeightUnit() * 0.09f;
//    _positions = {
//        center + Vec2(0.0f, dy),
//        center + Vec2(0.0f, -dy),
//        center + Vec2(dx, 0.0f),
//        center + Vec2(-dx, 0.0f)
//    };
//}
//
//// MARK: - Coin Sine Wave
//
//CoinStrategy CoinSineWave::makeDefault()
//{
//    return CoinSineWave(9);
//}
//
//CoinSineWave::CoinSineWave(int count)
//{
//    float amplitude = CoinStrategy::getWidthUnit() * 0.21f;
//    float heightDelta = CoinStrategy::getHeightUnit() / float(count * 2);
//    float direction = float(RNG::randomSign());
//    for (int i = 0; i < count; i++) {
//        _positions.push_back(Vec2(sin(M_PI_4 * float(i)) * amplitude * direction,
//                                  heightDelta * float(1 + 2 * i)));
//    }
//}
//
//// MARK: - Coin Half Sine Wave
//
//CoinStrategy CoinHalfSineWave::makeDefault()
//{
//    return CoinHalfSineWave(9);
//}
//
//CoinHalfSineWave::CoinHalfSineWave(int count)
//{
//    float amplitude = CoinStrategy::getWidthUnit() * 0.21f;
//    float heightDelta = CoinStrategy::getHeightUnit() / float(count * 2);
//    float direction = float(RNG::randomSign());
//    for (int i = 0; i < count; i++) {
//        _positions.push_back(Vec2(cos(M_PI_4 * 0.5f * float(i)) * amplitude * direction,
//                                  heightDelta * float(1 + 2 * i)));
//    }
//}
//
//// MARK: - Coin Circle
//
//CoinStrategy CoinCircle::makeDefault()
//{
//    return CoinCircle(CoinStrategy::defaultCenter(), 152.0f); // Magic number | lane spacing
//}
//
//CoinCircle::CoinCircle(Vec2 center, float radius)
//{
//    for (int i = 0; i < 8; i++) {
//        _positions.push_back(Vec2(center.x + radius * cos(M_PI_4 * float(i)),
//                                  center.y + radius * sin(M_PI_4 * float(i))));
//    }
//    _pivotPosition = center;
//}
//
//// MARK: - Coin Square
//
//CoinStrategy CoinSquare::makeDefault()
//{
//    return CoinSquare(CoinStrategy::defaultCenter(), 152.0f); // Magic number | lane spacing
//}
//
//CoinSquare::CoinSquare(Vec2 center, float halfSide)
//{
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            if (i != 1 || j != 1) {
//                _positions.push_back(Vec2(center.x + float(i - 1) * halfSide,
//                                          center.y + float(j - 1) * halfSide));
//            }
//        }
//    }
//    _pivotPosition = center;
//}
//
//// MARK: - Coin Big Rhombus
//
//CoinStrategy CoinBigRhombus::makeDefault()
//{
//    return CoinBigRhombus(CoinStrategy::defaultCenter());
//}
//
//CoinBigRhombus::CoinBigRhombus(Vec2 center)
//{
//    float vOffset = CoinStrategy::getHeightUnit() * 0.12f;
//    float hOffset = vOffset * 0.66f;
//
//    int x_dir = -1;
//    int y_dir = -1;
//    int x = 2;
//    int y = 0;
//
//    for (int i = 0; i < 8; i++) {
//        _positions.push_back(Vec2(center.x + x * hOffset, center.y + y * vOffset));
//        x += x_dir;
//        y += y_dir;
//        if (x == 2 || x == -2) {
//            x_dir = -x_dir;
//        }
//        if (y == 2 || y == -2) {
//            y_dir = -y_dir;
//        }
//    }
//    _pivotPosition = center;
//}
