//
//  main.cpp
//  TestHarness
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <time.h>

#include <container/ContainerUtil.h>
#include <container/Vector.h>
#include <container/HashMap.h>

using namespace std;
using namespace TestHarness;

class MyCustomClass
{
public:
    int _x;
    int _y;
    int _z;
    
    MyCustomClass(int x, int y, int z)
    {
        printf("MyCustomClass");
        _x = x;
        _y = y;
        _z = z;
    }
    
    ~MyCustomClass()
    {
        cout << "We are being destructed!: " << _x << _y << _z << endl;
    }
    
    //    MyCustomClass(const MyCustomClass& inMyCustomClass)
    //    {
    //        _x = inMyCustomClass._x;
    //    }
};

class Point
{
public:
    Point(int theX, int theY) :x(theX), y(theY)
    {
        // Empty
    }
    
private:
    int x;
    int y;
    
    // Print the object
    friend std::ostream& operator <<(std::ostream& outputStream, const Point& p);
};

std::ostream& operator <<(std::ostream& outputStream, const Point& p)
{
    int posX = p.x;
    int posY = p.y;
    
    outputStream << "x="<<posX<<","<<"y="<<posY;
    return outputStream;
}

int getNextID()
{
    static int nextID = 0;
    
    return (nextID++ & 65535) << 11;
}

void Print(Vector<int>& array, const char* _functionName)
{
    cout << _functionName << endl;
    for (int* it = array.begin(); it != array.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void Print(Vector<string>& array, const char* _functionName)
{
    cout << _functionName << endl;
    for (string* it = array.begin(); it != array.end(); it++)
    {
        cout << (*it).c_str() << " ";
    }
    cout << endl;
}

void Print(Vector<MyCustomClass*>& array, const char* _functionName)
{
    cout << _functionName << endl;
    for (MyCustomClass** it = array.begin(); it != array.end(); it++)
    {
        cout << (*it)->_x << " " << (*it)->_y << " " << (*it)->_z << "|";
    }
    cout << endl;
}

void Generate(Vector<int>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(rand() % 101);
    }
    Print(array, __FUNCTION__);
}

void Erase(Vector<int>& array)
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

void Insert(Vector<int>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        const int pos = array.size() ? rand() % array.size() : 0;
        const int value = rand() % 101;
        array.insert(pos, value);
    }
    Print(array, __FUNCTION__);
}

void Add(Vector<int>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(rand() % 101);
    }
    Print(array, __FUNCTION__);
}

string RandomString()
{
    const char chars[] = "abcdefghijklmnopqrstuvwxyz";
    const size_t size = sizeof(chars) - 1;
    string str;
    const int length = rand() % 10 + 1;
    for (int i = 0; i < length; ++i)
    {
        str += chars[rand() % size];
    }
    return str;
}

void Generate(Vector<string>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(RandomString());
    }
    Print(array, __FUNCTION__);
}

void Generate(Vector<MyCustomClass*>& array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(new MyCustomClass(rand() % 10, rand() % 10, rand() % 10));
    }
    Print(array, __FUNCTION__);
}

bool StrContainsChars(const string& _str,const string& _charsToFind)
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

void Erase(Vector<string>& array)
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
void Sort(Vector<T>& array)
{
    sort(array.begin(), array.end());
    Print(array, __FUNCTION__);
}

void Insert(Vector<string>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        const int pos = array.size() ? rand() % array.size() : 0;
        const string str = RandomString();
        array.insert(pos, str);
    }
    Print(array, __FUNCTION__);
}

void Add(Vector<string>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(RandomString());
    }
    Print(array, __FUNCTION__);
}

void Add(Vector<MyCustomClass*>& array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array.push_back(new MyCustomClass(rand() % 10, rand() % 10, rand() % 10));
    }
    Print(array, __FUNCTION__);
}

template<typename T>
void Clear(Vector<T>& array)
{
    array.clear();
    Print(array, __FUNCTION__);
}

void TestVectorInt()
{
    Vector<int> arr;
    Generate(arr, 2500);
    Sort(arr);
    Erase(arr);
    Insert(arr, 2500);
    Add(arr, 2500);
    Clear(arr);
}

void TestVectorString()
{
    Vector<string> arr;
    Generate(arr, 1500);
    Sort(arr);
    Erase(arr);
    Insert(arr, 3000);
    Add(arr, 5000);
    Clear(arr);
}

#include "ContainerUtil.h"

void TestVectorCustom()
{
    Vector<MyCustomClass*> arr;
    Generate(arr, 4);
    Add(arr, 4);
    ContainerUtil::cleanUpVectorOfPointers(arr);
    Clear(arr);
}

struct MyKeyHash
{
    size_t operator()(const string& k) const
    {
        int hash = 7;
        size_t strlen = k.length();
        for (int i = 0; i < strlen; ++i)
        {
            hash = hash * 31 + k.at(i);
        }
        
        return hash;
    }
};

#include <math.h>

#define SPINE_PI 3.1415927f
#define SPINE_PI_2 PI * 2
#define RadDeg 180.0f / SPINE_PI
#define DegRad SPINE_PI / 180.0f

const int SIN_BITS = 14; // 16KB. Adjust for accuracy.
const int SIN_MASK = ~(-(1 << SIN_BITS));
const int SIN_COUNT = SIN_MASK + 1;
const float RadFull = SPINE_PI * 2;
const float DegFull = 360;
const float RadToIndex = SIN_COUNT / RadFull;
const float DegToIndex = SIN_COUNT / DegFull;
float SIN_TABLE[SIN_COUNT] = {0.0f};

void configure()
{
    for (int i = 0; i < SIN_COUNT; ++i)
    {
        SIN_TABLE[i] = (float)sinf((i + 0.5f) / SIN_COUNT * RadFull);
    }
    
    for (int i = 0; i < 360; i += 90)
    {
        SIN_TABLE[(int)(i * DegToIndex) & SIN_MASK] = (float)sinf(i * DegRad);
    }
}

/// Returns the sine in radians from a lookup table.
float computeSin(float radians)
{
    return SIN_TABLE[(int)(radians * RadToIndex) & SIN_MASK];
}

#include <operator/BitwiseOperatorTest.h>

int main(int argc, const char * argv[])
{
    BitwiseOperatorTest::testBitWiseOperations();
    
    configure();
    
    Point p1(5, 3);
    
    std::cout << p1 << std::endl;
    
    float value = computeSin(2);
    
    printf("Value is %f \n", value);
    
    cout << "Hello, World!" << endl;
    
    HashMap<string, MyCustomClass*, MyKeyHash> hmap(65535);
    MyCustomClass* alpha = new MyCustomClass(4, 3, 1);
    MyCustomClass* beta = new MyCustomClass(4, 2, 3);
    hmap.insert("alpha", alpha);
    hmap.insert("beta", beta);
    hmap.insert("gamma", new MyCustomClass(3, 2, 1));
    //    hmap.insert("gamma", new MyCustomClass(2, 2, 4));
    
    cout << "Hash Map Size: " << hmap.size() << endl;
    cout << "Hash Map Elements:" << endl;
    for (HashMap<string, MyCustomClass*, MyKeyHash>::Iterator i = hmap.begin(); i != hmap.end(); ++i)
    {
        cout << "Key: " << i.first() << " Value: " << i.second()->_x << i.second()->_y << i.second()->_z << endl;
    }
    
    HashMap<string, MyCustomClass*, MyKeyHash>::Iterator i = hmap.find("alpha");
    assert(i.second() == alpha);
    
    i = hmap.find("beta");
    assert(i.second() == beta);
    
    i = hmap.find("alpha");
    delete i.second();
    hmap.erase(i);
    i = hmap.find("alpha");
    assert(i == hmap.end());
    
    cout << "Hash Map Size after erase: " << hmap.size() << endl;
    
    ContainerUtil::cleanUpHashMapOfPointers<string, MyCustomClass, MyKeyHash>(hmap);
    
    cout << "Hash Map Size after erase: " << hmap.size() << endl;
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    unsigned long start = clock();
    
    TestVectorInt();
    TestVectorString();
    TestVectorCustom();

    for (int i = 0; i < 65535; ++i)
    {
        int _id = getNextID();
        printf("ID is %d\n", _id);
    }
    
    unsigned long end = clock();
    
    std::cout << "it took " << end - start << " ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << " seconds." << std::endl;
}
