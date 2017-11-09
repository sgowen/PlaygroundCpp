//
//  MemoryTest.h
//  TestHarness
//
//  Created by Stephen Gowen on 11/9/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef MemoryTest_h
#define MemoryTest_h

#include <vector>
#include <string>

namespace NoctisGames
{
    class MemoryTest
    {
    public:
        static void testMemoryStuff()
        {
            std::vector<std::string> testVector;
            testVector.push_back("this is a test");
            testVector.push_back("this is a test as well");
            testVector.push_back("this is a test also");
            testVector.push_back("this is a test too");
            testVector.push_back("this is a test man");
            
            void* pointer1 = &testVector[3];
            
            std::string test = testVector[3];
            void* pointer2 = &test;
            
            std::string& test2 = testVector[3];
            void* pointer3 = &test2;
            
            std::cout << "pointer1 " << pointer1 << std::endl;
            std::cout << "pointer2 " << pointer2 << std::endl;
            std::cout << "pointer3 " << pointer3 << std::endl;
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        MemoryTest();
        MemoryTest(const MemoryTest&);
        MemoryTest& operator=(const MemoryTest&);
    };
}

#endif /* MemoryTest_h */
