//
//  StringTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 9/29/21.
//  Copyright © 2021 Stephen Gowen. All rights reserved.
//

#pragma once

#include <inttypes.h>
#include <iostream>

class StringTest
{
public:
    static void test()
    {
        using namespace std;
        
        std::string test = "ROBT";
        
        if (test == "ROBT")
        {
            printf("Okay, I guess strings do work like that \n");
        }
        else
        {
            printf("Ah! Better to use .compare \n");
        }
    }
    
private:
    StringTest();
    ~StringTest();
    StringTest(const StringTest&);
    StringTest& operator=(const StringTest&);
};
