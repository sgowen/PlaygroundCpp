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
#include <set>

std::vector<std::string> splitpath(const std::string& str, const std::set<char> delimiters)
{
    std::vector<std::string> result;
    
    char const* pch = str.c_str();
    char const* start = pch;
    for(; *pch; ++pch)
    {
        if (delimiters.find(*pch) != delimiters.end())
        {
            if (start != pch)
            {
                std::string str(start, pch);
                result.push_back(str);
            }
            else
            {
                result.push_back("");
            }
            start = pch + 1;
        }
    }
    
    result.push_back(start);
    
    return result;
}

class StringTest
{
public:
    static void test()
    {
        test1();
        test2();
    }
    
private:
    static void test1()
    {
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
    
    static void test2()
    {
        std::set<char> delims;
        delims.insert('/');
        
        std::vector<std::string> path = splitpath("/Users/sgowen/Documents/GitHub/main/PlaygroundCpp/PlaygroundCpp/string/StringTest.hpp", delims);
        std::cout << path.back() << std::endl;
    }
    
    StringTest();
    ~StringTest();
    StringTest(const StringTest&);
    StringTest& operator=(const StringTest&);
};
