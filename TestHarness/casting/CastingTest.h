//
//  CastingTest.h
//  TestHarness
//
//  Created by Stephen Gowen on 11/14/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef CastingTest_h
#define CastingTest_h

#include <inttypes.h>
#include <iostream>

namespace NoctisGames
{
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
        // ctor, copy ctor, and assignment should be private in a Singleton
        CastingTest();
        CastingTest(const CastingTest&);
        CastingTest& operator=(const CastingTest&);
    };
}

#endif /* CastingTest_h */
