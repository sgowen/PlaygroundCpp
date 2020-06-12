//
//  BitMaskTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 10/29/19.
//  Copyright © 2019 Stephen Gowen. All rights reserved.
//

#pragma once

#include <inttypes.h>
#include <iostream>

class BitMaskTest
{
public:
    static void test()
    {
        uint16_t rawRecipeCode = 0x1001;
        printf("rawRecipeCode %d \n", rawRecipeCode);
        
        uint16_t recipeCode = rawRecipeCode & 0xF000;
        printf("recipeCode %d \n", recipeCode);
        
        uint16_t modifiers = rawRecipeCode & 0x0FFF;
        printf("modifiers %d \n", modifiers);
    }
    
private:
    BitMaskTest();
    ~BitMaskTest();
    BitMaskTest(const BitMaskTest&);
    BitMaskTest& operator=(const BitMaskTest&);
};
