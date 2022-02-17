//
//  HashMapTest.hpp
//  HashMap
//
//  Created by Stephen Gowen on 11/6/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include "HashMap.hpp"
#include "HashMapUtil.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

class MyCustomClass2
{
public:
    int _x;
    int _y;
    int _z;
    
    MyCustomClass2(int x, int y, int z)
    {
        printf("MyCustomClass2\n");
        _x = x;
        _y = y;
        _z = z;
    }
    
    ~MyCustomClass2()
    {
        std::cout << "We are being destructed!: " << _x << _y << _z << std::endl;
    }
};

struct MyKeyHash
{
    size_t operator()(const std::string& k) const
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

class Key
{
public:
    int _intValue;
    std::string _strValue;
    
    Key(int intValue = 0, std::string strValue = "") :
    _intValue(intValue),
    _strValue(strValue)
    {
        // Empty
    }
    
    bool operator==(const Key &other) const
    {
        return _intValue == other._intValue && _strValue == other._strValue;
    }
    
    friend std::ostream& operator <<(std::ostream& outputStream, const Key& k);
};

std::ostream& operator <<(std::ostream& os, const Key& k)
{
    os << "{ intValue = " << k._intValue << ", strValue = " << k._strValue << " }";
    
    return os;
}

class Entity
{
public:
    float _x;
    float _y;
    int _maxHealth;
    
    Entity(float x, float y, int maxHealth) : _x(x), _y(y), _maxHealth(maxHealth) {}
    
    friend std::ostream& operator <<(std::ostream& outputStream, const Entity& p);
};

std::ostream& operator <<(std::ostream& os, const Entity& e)
{
    os << "{ x = " << e._x << ", y = " << e._y << ", maxHealth = " << e._maxHealth << " }";
    
    return os;
}

struct HashKey
{
    std::size_t operator()(const Key& val) const
    {
        std::size_t h1 = val._intValue;
        
        std::size_t h2 = 7;
        size_t strlen = val._strValue.length();
        for (int i = 0; i < strlen; ++i)
        {
            h2 = h2 * 31 + val._strValue.at(i);
        }
        
        return h1 ^ (h2 << 1);
    }
};

class EntityManager
{
public:
    HashMap<Key, Entity*, HashKey> _entityMap;
};

void initEntityManager(EntityManager& entityManager)
{
    {
        Key key(1, "I'm a key!");
        Entity* entity = new Entity(3, 3, 10);
        entityManager._entityMap.insert(key, entity);
    }
    
    {
        Key key(2, "I'm a key as well!");
        Entity* entity = new Entity(5, 5, 15);
        entityManager._entityMap.insert(key, entity);
    }
    
    {
        Key key(4, "Sure are a lot of keys around here");
        Entity* entity = new Entity(7, 7, 21);
        entityManager._entityMap.insert(key, entity);
    }
}

void testEntityManager(EntityManager& entityManager)
{
    HashMap<Key, Entity*, HashKey>& hashMap = entityManager._entityMap;
    
    Key key1(1, "I'm a key!");
    HashMap<Key, Entity*, HashKey>::Iterator i = hashMap.find(key1);
    assert(i.second()->_x == 3 && i.second()->_y == 3 && i.second()->_maxHealth == 10);
    
    Key key2(2, "I'm a key as well!");
    i = hashMap.find(key2);
    assert(i.second()->_x == 5 && i.second()->_y == 5 && i.second()->_maxHealth == 15);
    
    std::cout << "Erasing an element from the Hash Map with key: " << key1 << std::endl;
    
    i = hashMap.find(key1);
    delete i.second();
    hashMap.erase(i);
    i = hashMap.find(key1);
    assert(i == hashMap.end());
}

void printEntityManager(EntityManager& entityManager)
{
    HashMap<Key, Entity*, HashKey>& hashMap = entityManager._entityMap;
    
    std::cout << "Hash Map Size: " << hashMap.size() << std::endl;
    
    std::cout << "Hash Map Elements:" << std::endl;
    for (HashMap<Key, Entity*, HashKey>::Iterator i = hashMap.begin(); i != hashMap.end(); ++i)
    {
        std::cout << "Key: " << i.first() << " Value: " << *i.second() << std::endl;
    }
}

class HashMapTest
{
public:
    static void test()
    {
        test1();
        test2();
    }
    
private:
    static void test1()
    {
        EntityManager entityManager;
        
        initEntityManager(entityManager);
        printEntityManager(entityManager);
        testEntityManager(entityManager);
        printEntityManager(entityManager);
        
        HashMapUtil::cleanUpHashMapOfPointers<Key, Entity, HashKey>(entityManager._entityMap);
        
        printEntityManager(entityManager);
    }
    
    static void test2()
    {
        HashMap<std::string, MyCustomClass2*, MyKeyHash> hmap(65535);
        MyCustomClass2* alpha = new MyCustomClass2(4, 3, 1);
        MyCustomClass2* beta = new MyCustomClass2(4, 2, 3);
        hmap.insert("alpha", alpha);
        hmap.insert("beta", beta);
        hmap.insert("gamma", new MyCustomClass2(3, 2, 1));
        hmap.insert("asdfasdf", new MyCustomClass2(4, 4, 5));
        hmap.insert("asdfcc", new MyCustomClass2(6, 1, 3));
        hmap.insert("zzzcc", new MyCustomClass2(7, 7, 7));
        hmap.insert("rrgd", new MyCustomClass2(3, 2, 19));
        hmap.insert("odiska", new MyCustomClass2(3, 2, 88));
        
        std::cout << "Hash Map Size: " << hmap.size() << std::endl;
        std::cout << "Hash Map Elements:" << std::endl;
        for (HashMap<std::string, MyCustomClass2*, MyKeyHash>::Iterator i = hmap.begin(); i != hmap.end(); ++i)
        {
            std::cout << "Key: " << i.first() << " Value: " << i.second()->_x << i.second()->_y << i.second()->_z << std::endl;
        }
        
        HashMap<std::string, MyCustomClass2*, MyKeyHash>::Iterator i = hmap.find("alpha");
        assert(i.second() == alpha);
        
        i = hmap.find("beta");
        assert(i.second() == beta);
        
        i = hmap.find("alpha");
        delete i.second();
        hmap.erase(i);
        i = hmap.find("alpha");
        assert(i == hmap.end());
        
        std::cout << "Hash Map Size after erase: " << hmap.size() << std::endl;
        
        HashMapUtil::cleanUpHashMapOfPointers<std::string, MyCustomClass2, MyKeyHash>(hmap);
        
        std::cout << "Hash Map Size after erase: " << hmap.size() << std::endl;
    }
    
    HashMapTest();
    ~HashMapTest();
    HashMapTest(const HashMapTest&);
    HashMapTest& operator=(const HashMapTest&);
};
