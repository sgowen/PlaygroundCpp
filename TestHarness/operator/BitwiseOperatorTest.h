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
            
            testBools();
            
            testBitwiseAnd();
            
            testShifts();
        }
        
        static void testBools()
        {
            bool showWindow = true;
            bool showDialog = false;
            bool containsErrors = true;
            
            printf("showDialog: %d, containsErrors: %d \n", showDialog, containsErrors);
            
            showDialog |= containsErrors;
            
            printf("showDialog: %d, containsErrors: %d \n", showDialog, containsErrors);
            
            showWindow |= containsErrors;
            
            printf("showWindow: %d, containsErrors: %d \n", showWindow, containsErrors);
            
            assert(showDialog);
            assert(showWindow);
        }
        
        static void testBitwiseAnd()
        {
            unsigned char b = 255;
            int value = b & 0x7F;
            int huh = b & 0x80;
            if (huh)
            {
                b = '9';
                value |= (b & 0x7F) << 7;
                if (b & 0x80)
                {
                    b = 'F';
                    value |= (b & 0x7F) << 14;
                    if (b & 0x80)
                    {
                        b = '4';
                        value |= (b & 0x7F) << 21;
                        unsigned char b2 = '7';
                        if (b & 0x80) value |= (b2 & 0x7F) << 28;
                    }
                }
            }
        }
        
        static void testShifts()
        {
            {
                uint8_t Value = 80;
                testShiftImpl1(Value*16);
            }
            {
                uint16_t Value = 80;
                testShiftImpl1(Value);
            }
            
            {
                uint8_t Value = 80;
                testShiftImpl2(Value*16);
            }
            {
                uint8_t Value = 80;
                Value = Value << 4;
                testShiftImpl2(Value);
            }
            {
                uint16_t Value = 80;
                Value <<= 4;
                testShiftImpl2(Value);
            }
            {
                int Value = 80;
                uint8_t v = Value & 0xFF;
                testShiftImpl2(v*16);
            }
        }
        
        static void testShiftImpl1(uint16_t Data)
        {
            uint8_t Bytes[2];
            Bytes[1] = (Data >> 8);
            Bytes[0] = (uint8_t) (Data & 0x00ff);
            
            printf("1 Bytes[0] %d \n", Bytes[0]);
            printf("1 Bytes[1] %d \n", Bytes[1]);
        }
        
        static void testShiftImpl2(uint16_t Data)
        {
            uint8_t Bytes[2];
            Bytes[1] = (Data >> 8);
            Bytes[0] = (Data & 0xff);
            
            printf("2 Bytes[0] %d \n", Bytes[0]);
            printf("2 Bytes[1] %d \n", Bytes[1]);
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        BitwiseOperatorTest();
        BitwiseOperatorTest(const BitwiseOperatorTest&);
        BitwiseOperatorTest& operator=(const BitwiseOperatorTest&);
    };
}

#endif /* BitwiseOperatorTest_h */
