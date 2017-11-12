//
//  PoolTest.h
//  TestHarness
//
//  Created by Stephen Gowen on 11/12/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef NoctisGames_PoolTest_h
#define NoctisGames_PoolTest_h

namespace NoctisGames
{
    class PoolTest
    {
    public:
        static void testPool()
        {
            // TODO
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        PoolTest();
        PoolTest(const PoolTest&);
        PoolTest& operator=(const PoolTest&);
    };
}

#endif /* NoctisGames_PoolTest_h */
