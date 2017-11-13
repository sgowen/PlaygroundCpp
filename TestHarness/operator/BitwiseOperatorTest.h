//
//  BitwiseOperatorTest.h
//  TestHarness
//
//  Created by Stephen Gowen on 11/3/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef BitwiseOperatorTest_h
#define BitwiseOperatorTest_h

namespace NoctisGames
{
    class BitwiseOperatorTest
    {
    public:
        static void test()
        {
            int atomicNumMask = 0x7F;
            int typeMask = 0x1FF;
            
            int element = 29;
            int atomicNum = atomicNumMask & element;
            int elementShifted = element >> 7;
            int type = typeMask & elementShifted;
            
            printf("atomicNumMask: %d, typeMask: %d, atomicNum: %d type: %d element: %d elementShifted: %d \n", atomicNumMask, typeMask, atomicNum, type, element, elementShifted);
            
            int x = 0b00001100;
            int y = 0b00001011;
            int z = x & y;
            
            printf("bitwise & operator yields x: %d, y: %d, z: %d \n", x, y, z);
            
            z = x | y;
            printf("bitwise | operator yields x: %d, y: %d, z: %d \n", x, y, z);
            
            {
                int mask1 = 0x100;
                int mask2 = 0x10;
                int result = mask1 | mask2;
                
                printf("mask1: %d, mask2: %d, result: %d \n", mask1, mask2, result);
            }
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        BitwiseOperatorTest();
        BitwiseOperatorTest(const BitwiseOperatorTest&);
        BitwiseOperatorTest& operator=(const BitwiseOperatorTest&);
    };
}

#endif /* BitwiseOperatorTest_h */
