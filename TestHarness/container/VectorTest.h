//
//  VectorTest.h
//  TestHarness
//
//  Created by Stephen Gowen on 11/6/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef VectorTest_h
#define VectorTest_h

#include "ContainerUtil.h"

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
};

void Print(NoctisGames::Vector<int>& array, const char* _functionName)
{
    std::cout << _functionName << std::endl;
    for (int* it = array.begin(); it != array.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void Print(NoctisGames::Vector<std::string>& array, const char* _functionName)
{
    std::cout << _functionName << std::endl;
    for (std::string* it = array.begin(); it != array.end(); it++)
    {
        std::cout << (*it).c_str() << " ";
    }
    std::cout << std::endl;
}

void Print(NoctisGames::Vector<MyCustomClass*>& array, const char* _functionName)
{
    std::cout << _functionName << std::endl;
    for (MyCustomClass** it = array.begin(); it != array.end(); it++)
    {
        std::cout << (*it)->_x << " " << (*it)->_y << " " << (*it)->_z << "|";
    }
    std::cout << std::endl;
}

void Generate(NoctisGames::Vector<int>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(rand() % 101);
    }
    Print(array, __FUNCTION__);
}

void Erase(NoctisGames::Vector<int>& array)
{
    for (size_t i = 0, j = 1; i < array.size(); ++i)
    {
        if (i % 2 == j % 2)
        {
            array.erase(i--);
            j++;
        }
    }
    Print(array, __FUNCTION__);
}

void Insert(NoctisGames::Vector<int>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        const int pos = array.size() ? rand() % array.size() : 0;
        const int value = rand() % 101;
        array.insert(pos, value);
    }
    Print(array, __FUNCTION__);
}

void Add(NoctisGames::Vector<int>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(rand() % 101);
    }
    Print(array, __FUNCTION__);
}

std::string RandomString()
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

void Generate(NoctisGames::Vector<std::string>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(RandomString());
    }
    Print(array, __FUNCTION__);
}

void Generate(NoctisGames::Vector<MyCustomClass*>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(new MyCustomClass(rand() % 10, rand() % 10, rand() % 10));
    }
    Print(array, __FUNCTION__);
}

bool StrContainsChars(const std::string& _str,const std::string& _charsToFind)
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

void Erase(NoctisGames::Vector<std::string>& array)
{
    for (size_t i = 0; i < array.size(); ++i)
    {
        if (StrContainsChars(array[i], "abcde"))
        {
            array.erase(i--);
        }
    }
    Print(array, __FUNCTION__);
}

template<typename T>
void Sort(NoctisGames::Vector<T>& array)
{
    std::sort(array.begin(), array.end());
    Print(array, __FUNCTION__);
}

void Insert(NoctisGames::Vector<std::string>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        const int pos = array.size() ? rand() % array.size() : 0;
        const std::string str = RandomString();
        array.insert(pos, str);
    }
    Print(array, __FUNCTION__);
}

void Add(NoctisGames::Vector<std::string>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(RandomString());
    }
    Print(array, __FUNCTION__);
}

void Add(NoctisGames::Vector<MyCustomClass*>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(new MyCustomClass(rand() % 10, rand() % 10, rand() % 10));
    }
    Print(array, __FUNCTION__);
}

template<typename T>
void Clear(NoctisGames::Vector<T>& array)
{
    array.clear();
    Print(array, __FUNCTION__);
}

namespace NoctisGames
{
    static unsigned long _gVectorTestStartTime;
    
    class VectorTest
    {
    public:
        static void onBegin()
        {
            srand(static_cast<unsigned int>(time(nullptr)));
            
            _gVectorTestStartTime = clock();
        }
        
        static void onEnd()
        {
            unsigned long end = clock();
            
            std::cout << "it took " << end - _gVectorTestStartTime << " ticks, or " << ((float)end - _gVectorTestStartTime)/CLOCKS_PER_SEC << " seconds." << std::endl;
        }
        
        static void testVectorInt()
        {
            NoctisGames::Vector<int> arr;
            Generate(arr, 2500);
            Sort(arr);
            Erase(arr);
            Insert(arr, 2500);
            Add(arr, 2500);
            Clear(arr);
        }
        
        static void testVectorString()
        {
            NoctisGames::Vector<std::string> arr;
            Generate(arr, 1500);
            Sort(arr);
            Erase(arr);
            Insert(arr, 3000);
            Add(arr, 5000);
            Clear(arr);
        }
        
        static void testVectorCustom()
        {
            NoctisGames::Vector<MyCustomClass*> arr;
            Generate(arr, 4);
            Add(arr, 4);
            ContainerUtil::cleanUpVectorOfPointers(arr);
            Clear(arr);
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        VectorTest();
        VectorTest(const VectorTest&);
        VectorTest& operator=(const VectorTest&);
    };
}

#endif /* VectorTest_h */
