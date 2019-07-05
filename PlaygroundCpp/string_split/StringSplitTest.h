//
//  StringSplitTest.h
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/14/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#ifndef StringSplitTest_h
#define StringSplitTest_h

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

class StringSplitTest
{
public:
    static void test()
    {
        std::set<char> delims;
        delims.insert('/');
        
        std::vector<std::string> path = splitpath("/Users/sgowen/Dropbox/Documents/gamedev/github/PlaygroundCpp/PlaygroundCpp/random_file_access/RandomFileAccessTest.h", delims);
        std::cout << path.back() << std::endl;
    }
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    StringSplitTest();
    StringSplitTest(const StringSplitTest&);
    StringSplitTest& operator=(const StringSplitTest&);
};

#endif /* StringSplitTest_h */
