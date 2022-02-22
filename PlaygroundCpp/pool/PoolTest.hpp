//
//  PoolTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/12/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include <pool/Pool.hpp>
#include <data_structures/GowArray.hpp>

#include <iostream>

class MyClass
{
public:
    float _x, _y, _z;
};

class SomethingThatHasAPool
{
public:
    Pool< GowArray<std::string> > _poolOfGowArrayStrings;
    Pool<MyClass> _poolOfClass;
};

class PoolTest
{
public:
    static void test()
    {
        SomethingThatHasAPool obj;
        
        using namespace std;
        
        cout << "Testing _poolOfClass" << endl;

        MyClass* mc1 = obj._poolOfClass.obtain();
        mc1->_x = 5;
        mc1->_y = 6;
        mc1->_z = 7;

        MyClass* mc2 = obj._poolOfClass.obtain();
        mc2->_x = 6;
        mc2->_y = 7;
        mc2->_z = 8;

        cout << "Freeing mc1" << endl;

        obj._poolOfClass.free(mc1);

        // I shouldn't be able to free it again
        obj._poolOfClass.free(mc1);

        MyClass* mc3 = obj._poolOfClass.obtain();
        mc3->_x += 10;
        mc3->_y += 10;
        mc3->_z += 10;

        assert(mc3->_x == 15);

        cout << "mc3->_x == 15, sweet, that means mc3 == mc1" << endl;

        obj._poolOfClass.free(mc2);
        obj._poolOfClass.free(mc3);

        cout << "Okay, what about a pool of vectors?" << endl;
        
        // I expect to allocate a new GowArray here
        GowArray<string>* vec1P = obj._poolOfGowArrayStrings.obtain();
        GowArray<string>& vec1 = *vec1P;
        vec1.push_back("This is a test");
        vec1.push_back("This is a test as well");
        vec1.push_back("This is a test too");
        
        // I expect to allocate a new GowArray here as well
        GowArray<string>* vec2P = obj._poolOfGowArrayStrings.obtain();
        GowArray<string>& vec2 = *vec2P;
        vec2.push_back("This is a test2");
        vec2.push_back("This is a test2 as well");
        vec2.push_back("This is a test2 too");
        
        cout << "Freeing vec1" << endl;
        
        // Okay, sure had a lot of fun using that vector, time to throw it away
        obj._poolOfGowArrayStrings.free(&vec1);
        
        // I shouldn't be able to free it again
        obj._poolOfGowArrayStrings.free(&vec1);
        
        // We should get back vec1 here, which already has 3 strings in it
        GowArray<string>* vec3P = obj._poolOfGowArrayStrings.obtain();
        GowArray<string>& vec3 = *vec3P;
        
        assert(vec3.size() == 3);
        
        cout << "vec3.size() == 3, which means that vec3 == vec1" << endl;
        
        vec3.clear();
        
        assert(vec3.size() == 0);
        
        vec3.push_back("This is a test3");
        vec3.push_back("This is a test3 as well");
        vec3.push_back("This is a test3 too");
        
        obj._poolOfGowArrayStrings.free(vec2P);
        obj._poolOfGowArrayStrings.free(vec3P);
        
        cout << "Okay, allocations table should be empty via desctructors after this message" << endl;
    }
    
private:
    PoolTest();
    ~PoolTest();
    PoolTest(const PoolTest&);
    PoolTest& operator=(const PoolTest&);
};
