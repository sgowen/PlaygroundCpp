//
//  SinTableTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/6/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include <math.h>

#define NG_PI 3.1415927f
#define NG_PI_2 PI * 2
#define RadDeg 180.0f / NG_PI
#define DegRad NG_PI / 180.0f

const int SIN_BITS = 14; // 16KB. Adjust for accuracy.
const int SIN_MASK = ~(-(1 << SIN_BITS));
const int SIN_COUNT = SIN_MASK + 1;
const float RadFull = NG_PI * 2;
const float DegFull = 360;
const float RadToIndex = SIN_COUNT / RadFull;
const float DegToIndex = SIN_COUNT / DegFull;
float SIN_TABLE[SIN_COUNT] = {0.0f};

void configure()
{
    for (int i = 0; i < SIN_COUNT; ++i)
    {
        SIN_TABLE[i] = (float)sinf((i + 0.5f) / SIN_COUNT * RadFull);
    }
    
    for (int i = 0; i < 360; i += 90)
    {
        SIN_TABLE[(int)(i * DegToIndex) & SIN_MASK] = (float)sinf(i * DegRad);
    }
}

/// Returns the sine in radians from a lookup table.
float computeSin(float radians)
{
    return SIN_TABLE[(int)(radians * RadToIndex) & SIN_MASK];
}

class SinTableTest
{
public:
    static void test()
    {
        configure();
        
        float value = computeSin(2);
        
        printf("Value is %f \n", value);
    }
    
private:
    SinTableTest();
    ~SinTableTest();
    SinTableTest(const SinTableTest&);
    SinTableTest& operator=(const SinTableTest&);
};
