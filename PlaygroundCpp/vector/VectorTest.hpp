//
//  VectorTest.hpp
//  Vector
//
//  Created by Stephen Gowen on 11/6/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include "Extension.hpp"

#include "Vector.hpp"
#include "VectorUtil.hpp"

#include <iostream>
#include <time.h>
#include <assert.h>
#include <algorithm>
#include <string>

class MyCustomClass
{
public:
    int _x;
    int _y;
    int _z;
    
    MyCustomClass(int x, int y, int z)
    {
        printf("MyCustomClass\n");
        _x = x;
        _y = y;
        _z = z;
    }
    
    ~MyCustomClass()
    {
        std::cout << "We are being destructed!: " << _x << _y << _z << std::endl;
    }
    
    friend bool operator==(MyCustomClass& lhs, MyCustomClass& rhs)
    {
        return lhs._x == rhs._x && lhs._y == rhs._y && lhs._z == rhs._z;
    }
    
    friend bool operator!=(MyCustomClass& lhs, MyCustomClass& rhs)
    {
        return !(lhs == rhs);
    }
};

void print(Vector<int>& array, const char* _functionName)
{
    std::cout << _functionName << std::endl;
    for (int* it = array.begin(); it != array.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void print(Vector<std::string>& array, const char* _functionName)
{
    std::cout << _functionName << std::endl;
    for (std::string* it = array.begin(); it != array.end(); it++)
    {
        std::cout << (*it).c_str() << " ";
    }
    std::cout << std::endl;
}

void print(Vector<MyCustomClass>& array, const char* _functionName)
{
    std::cout << _functionName << std::endl;
    for (MyCustomClass* it = array.begin(); it != array.end(); it++)
    {
        std::cout << (*it)._x << " " << (*it)._y << " " << (*it)._z << "|";
    }
    std::cout << std::endl;
}

void generate(Vector<int>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(rand() % 101);
    }
    print(array, __FUNCTION__);
}

void erase(Vector<int>& array)
{
    for (size_t i = 0, j = 1; i < array.size(); ++i)
    {
        if (i % 2 == j % 2)
        {
            array.erase(i--);
            j++;
        }
    }
    print(array, __FUNCTION__);
}

void insert(Vector<int>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        const int pos = array.size() ? rand() % array.size() : 0;
        const int value = rand() % 101;
        array.insert(pos, value);
    }
    print(array, __FUNCTION__);
}

void add(Vector<int>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(rand() % 101);
    }
    print(array, __FUNCTION__);
}

std::string createRandomString()
{
    const char chars[] = "abcdefghijklmnopqrstuvwxyz";
    const size_t size = sizeof(chars) - 1;
    std::string str;
    const int length = rand() % 10 + 1;
    for (int i = 0; i < length; ++i)
    {
        str += chars[rand() % size];
    }
    return str;
}

void generate(Vector<std::string>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(createRandomString());
    }
    print(array, __FUNCTION__);
}

void generate(Vector<MyCustomClass>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(MyCustomClass(rand() % 10, rand() % 10, rand() % 10));
    }
    print(array, __FUNCTION__);
}

bool doesStringContainChars(const std::string& _str,const std::string& _charsToFind)
{
    for (size_t i = 0; i < _charsToFind.size(); ++i)
    {
        if (strchr(_str.c_str(), _charsToFind[i]))
        {
            return true;
        }
    }
    return false;
}

void erase(Vector<std::string>& array)
{
    for (size_t i = 0; i < array.size(); ++i)
    {
        if (doesStringContainChars(array[i], "abcde"))
        {
            array.erase(i--);
        }
    }
    print(array, __FUNCTION__);
}

template<typename T>
void sort(Vector<T>& array)
{
    std::sort(array.begin(), array.end());
    print(array, __FUNCTION__);
}

void insert(Vector<std::string>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        const int pos = array.size() ? rand() % array.size() : 0;
        const std::string str = createRandomString();
        array.insert(pos, str);
    }
    print(array, __FUNCTION__);
}

void add(Vector<std::string>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(createRandomString());
    }
    print(array, __FUNCTION__);
}

void add(Vector<MyCustomClass>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(MyCustomClass(rand() % 10, rand() % 10, rand() % 10));
    }
    print(array, __FUNCTION__);
}

template<typename T>
void clear(Vector<T>& array)
{
    array.clear();
    print(array, __FUNCTION__);
}

class VectorTest
{
public:
    static void test()
    {
        srand(static_cast<unsigned int>(time(NULL)));
        unsigned long vectorTestStartTime = clock();
        
        testVectorInt();
        testVectorString();
        testVectorCustom();
        testOtherStuff();
        
        unsigned long end = clock();
        std::cout << "it took " << end - vectorTestStartTime << " ticks, or " << ((float)end - vectorTestStartTime)/CLOCKS_PER_SEC << " seconds." << std::endl;
    }
    
private:
    static void testVectorInt()
    {
        Vector<int> arr;
        generate(arr, 2500);
        sort(arr);
        erase(arr);
        insert(arr, 2500);
        add(arr, 2500);
        clear(arr);
    }
    
    static void testVectorString()
    {
        Vector<std::string> arr;
        generate(arr, 1500);
        sort(arr);
        erase(arr);
        insert(arr, 3000);
        add(arr, 5000);
        
        clear(arr);
    }
    
    static void testVectorCustom()
    {
        printf("testVectorCustom\n");
        
        Vector<MyCustomClass> arr;
        generate(arr, 4);
        add(arr, 4);
        
        clear(arr);
    }
    
    static void testOtherStuff()
    {
        printf("testOtherStuff\n");
        
        Vector<MyCustomClass> arr;
        Vector<MyCustomClass> arr2;
        Vector<MyCustomClass> arr3;
        Vector<MyCustomClass> arr4;
        generate(arr, 4);
        generate(arr2, 5);
        generate(arr3, 6);
        generate(arr4, 6);
        
        arr = arr3;
        
        assert(arr == arr3);
        assert(arr != arr2);
        assert(arr3 != arr4);
    }
    
    VectorTest();
    ~VectorTest();
    VectorTest(const VectorTest&);
    VectorTest& operator=(const VectorTest&);
};
