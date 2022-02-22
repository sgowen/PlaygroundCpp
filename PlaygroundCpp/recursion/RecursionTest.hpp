//
//  RecursionTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 2/22/22.
//  Copyright © 2022 Stephen Gowen. All rights reserved.
//

#pragma once

#include <stdio.h>

class RecursionTest
{
public:
    static void test()
    {
        testReverseString();
        testPrimeNumbers();
    }
    
private:
    static void testReverseString()
    {
        std::string str = "This is a test";
        printf("string is: \n%s \n", str.c_str());
        
        reverse(str, 0, str.length() - 1);
        printf("Reversed string is: \n%s \n", str.c_str());
    }
    
    static void reverse(std::string &str, size_t l, size_t h)
    {
        if (l < h)
        {
            std::swap(str[l], str[h]);
            reverse(str, l + 1, h - 1);
        }
    }
    
    static void testPrimeNumbers()
    {
        assert(isPrime(3) == true);
        assert(isPrime(5) == true);
        assert(isPrime(7) == true);
        assert(isPrime(11) == true);
        assert(isPrime(13) == true);
        assert(isPrime(17) == true);
    }
    
    static bool isPrime(int n, int i = 2)
    {
        if (n <= 2)
        {
            return n == 2;
        }
        
        if (n % i == 0)
        {
            return false;
        }
        
        if (i * i > n)
        {
            return true;
        }
     
        return isPrime(n, i + 1);
    }
    
    RecursionTest();
    ~RecursionTest();
    RecursionTest(const RecursionTest&);
    RecursionTest& operator=(const RecursionTest&);
};
