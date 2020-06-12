//
//  CastingTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/14/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include <inttypes.h>
#include <iostream>

class CastingTest
{
public:
    static void test()
    {
        using namespace std;
        
        std::string test = "ROBT";
        
        const char* chars = test.c_str();
        
        uint32_t num = (uint32_t)chars[0] << 24 |
        (uint32_t)chars[1] << 16 |
        (uint32_t)chars[2] << 8  |
        (uint32_t)chars[3];
        
        uint32_t raw = 'ROBT';
        
        printf("num: %d raw: %d", num, raw);
    }
    
private:
    CastingTest();
    ~CastingTest();
    CastingTest(const CastingTest&);
    CastingTest& operator=(const CastingTest&);
};
