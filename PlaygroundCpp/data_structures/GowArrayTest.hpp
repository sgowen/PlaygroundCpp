//
//  GowArrayTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 2/21/22.
//  Copyright © 2022 Stephen Gowen. All rights reserved.
//

#pragma once

#include "GowArray.hpp"

class GowArrayTest
{
public:
    static void test()
    {
        testInt();
        testCustomType();
        testCustomPointerType();
        testCustomTypeCopying();
    }
    
private:
    static void testInt()
    {
        GowArray<int> integerArray;
        
        integerArray.reserve(3);
        assert(integerArray.capacity() == 3);
        assert(integerArray.size() == 0);
        
        integerArray.push_back(3);
        assert(integerArray.capacity() == 3);
        assert(integerArray.size() == 1);
        
        integerArray.push_back(5);
        assert(integerArray.capacity() == 3);
        assert(integerArray.size() == 2);
        
        integerArray.push_back(7);
        assert(integerArray.capacity() == 3);
        assert(integerArray.size() == 3);
        
        integerArray.push_back(9);
        assert(integerArray.capacity() == 6);
        assert(integerArray.size() == 4);
        
        assert(integerArray.contains(7) == true);
        assert(integerArray.indexOf(5) == 1);
        assert(integerArray[1] == 5);
        
        integerArray.insert(3, 8);
        assert(integerArray[3] == 8);
        assert(integerArray[4] == 9);
        
        integerArray.erase(1);
        assert(integerArray[1] == 7);
        
        int* beginP = integerArray.begin();
        int begin = *beginP;
        assert(begin == 3);
        
        int* endP = integerArray.end();
        int end = *endP;
        assert(end == 9);
        
        GowArray<int> integerArray2 = integerArray;
        assert(integerArray == integerArray2);
        
        integerArray.clear();
        assert(integerArray.capacity() == 6);
        assert(integerArray.size() == 0);
        
        assert(integerArray2.capacity() == 6);
        assert(integerArray2.size() == 4);
    }
    
    class Point3D
    {
    public:
        int _x;
        int _y;
        int _z;
        
        Point3D(int x, int y, int z) :
        _x(x),
        _y(y),
        _z(z)
        {
            printf("Point3D ctor \n");
        }
        
        Point3D(const Point3D& other) :
        _x(other._x),
        _y(other._y),
        _z(other._z)
        {
            printf("Point3D copy ctor \n");
        }
        
        Point3D& operator=(const Point3D& other)
        {
            _x = other._x;
            _y = other._y;
            _z = other._z;
            
            printf("Point3D assignment ctor \n");
            
            return *this;
        }
        
        ~Point3D()
        {
            printf("Point3D dtor \n");
        }
        
        friend bool operator==(Point3D& lhs, Point3D& rhs)
        {
            return lhs._x == rhs._x && lhs._y == rhs._y && lhs._z == rhs._z;
        }
        
        friend bool operator!=(Point3D& lhs, Point3D& rhs)
        {
            return !(lhs == rhs);
        }
    };
    
    static void testCustomType()
    {
        GowArray<Point3D> point3DArray;
        
        assert(point3DArray.capacity() == 0);
        assert(point3DArray.size() == 0);
        
        Point3D testPoint = Point3D(3, 5, 7);
        point3DArray.push_back(testPoint);
        
        Point3D* beginP = point3DArray.begin();
        Point3D begin = *beginP;
        assert(begin._x == 3);
        assert(begin._y == 5);
        assert(begin._z == 7);
        
        testPoint._x = 9;
        assert(begin._x == 3);
        assert(beginP->_x == 3);
        
        point3DArray.reserve(5);
        
        Point3D* beginP2 = point3DArray.begin();
        Point3D begin2 = *beginP2;
        assert(begin2._x == 3);
        assert(begin2._y == 5);
        assert(begin2._z == 7);
    }
    
    static void testCustomPointerType()
    {
        GowArray<Point3D*> point3DArray;
        
        assert(point3DArray.capacity() == 0);
        assert(point3DArray.size() == 0);
        
        Point3D* testPoint = new Point3D(3, 5, 7);
        point3DArray.push_back(testPoint);
        
        Point3D** beginPP = point3DArray.begin();
        Point3D* beginP = *beginPP;
        Point3D begin = *beginP;
        assert(begin._x == 3);
        assert(begin._y == 5);
        assert(begin._z == 7);
        
        begin._x = 5;
        assert(beginP->_x == 3);
        
        testPoint->_x = 9;
        assert(beginP->_x == 9);
    }
    
    static void testCustomTypeCopying()
    {
        GowArray<Point3D> point3DArray;
        
        point3DArray.push_back(Point3D(3, 5, 7));
        point3DArray.push_back(Point3D(2, 4, 6));
        point3DArray.push_back(Point3D(1, 11, 111));
        
        GowArray<Point3D> point3DArray2(point3DArray);
        
        GowArray<Point3D> point3DArray3 = point3DArray2;
        GowArray<Point3D> point3DArray4;
        point3DArray4 = point3DArray3;
        point3DArray4 = point3DArray4;
    }
    
    GowArrayTest();
    ~GowArrayTest();
    GowArrayTest(const GowArrayTest&);
    GowArrayTest& operator=(const GowArrayTest&);
};
