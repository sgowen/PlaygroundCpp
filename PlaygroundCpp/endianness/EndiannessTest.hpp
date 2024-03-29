//
//  EndiannessTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/14/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include <inttypes.h>
#include <iostream>

class EndiannessTest
{
public:
    static void test()
    {
        using namespace std;
        
        cout << "Are we on a Little Endian Machine? " << endl;
        cout << "isLittleEndian() = " << (isLittleEndian() ? "true" : "false") << endl;
        
        cout << "Let's dig a little deeper and print some stuff" << endl;
        printInts();
    }
    
private:
    static bool isLittleEndian()
    {
        volatile uint32_t i = 0x01234567;
        return (*((uint8_t*)(&i))) == 0x67;
    }
    
    static void printInts()
    {
        unsigned int values[] = { 1, 387, 8533937 };
        
        printf ("scan by ints\n");
        for (unsigned int i = 0; i < sizeof(values) / sizeof(*values); i++) {
            printf (" 0x%08x", values[i]);
        }
        printf ("\n");
        
        printf ("scan by bytes\n");
        
        for (unsigned int i = 0; i < sizeof(values); i++) {
            if (i % 4 == 0) printf (" 0x");
            printf ("%02x", ((unsigned char *)values)[i]);
        }
        printf ("\n");
    }
    
    EndiannessTest();
    ~EndiannessTest();
    EndiannessTest(const EndiannessTest&);
    EndiannessTest& operator=(const EndiannessTest&);
};
