//
//  ThreadingTest.h
//  TestHarness
//
//  Created by Stephen Gowen on 3/30/18.
//  Copyright © 2018 Noctis Games. All rights reserved.
//

#ifndef ThreadingTest_h
#define ThreadingTest_h

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

namespace NoctisGames
{
    std::mutex _m;
    int _i;
    
    class ThreadingTest
    {
    public:
        static void test()
        {
            std::thread* doStuffs[1000];
            for (int i = 0; i < 1000; ++i)
            {
                std::thread* t = new std::thread(doStuff);
                std::cout << "i = " << _i << " Thread ID " << t->get_id() << std::endl;
                doStuffs[i] = t;
            }
            
            for (int i = 0; i < 1000; ++i)
            {
                doStuffs[i]->join();
            }
            
            for (int i = 0; i < 1000; ++i)
            {
                delete doStuffs[i];
            }
            
            /// Check the Console Output!
            /// You'll see the threads all stomping on cout
            /// Thread 1 doesn't necessarily increment i from 1 to 2, it could be Thread 78
        }
        
        static void doStuff()
        {
            _m.lock();
            std::cout << "i = " << _i << " Thread ID " << std::this_thread::get_id() << std::endl;
            _i++;
            _m.unlock();
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        ThreadingTest();
        ThreadingTest(const ThreadingTest&);
        ThreadingTest& operator=(const ThreadingTest&);
    };
}

#endif /* ThreadingTest_h */
