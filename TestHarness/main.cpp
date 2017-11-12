//
//  main.cpp
//  TestHarness
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include <hash_map/HashMapTest.h>
#include <memory/MemoryTest.h>
#include <operator/BitwiseOperatorTest.h>
#include <pool/PoolTest.h>
#include <sin_table/SinTableTest.h>
#include <uniqueness/UniquenessTest.h>
#include <vector/VectorTest.h>

int main(int argc, const char * argv[])
{
    using namespace NoctisGames;
    
    HashMapTest::testHashMap();
    HashMapTest::testHashMap2();
    
    MemoryTest::testMemoryStuff();
    
    BitwiseOperatorTest::testBitWiseOperations();
    
    PoolTest::testPool();
    
    SinTableTest::testSinTable();

    UniquenessTest::testUniqueness();
    
    VectorTest::onBegin();
    VectorTest::testVectorInt();
    VectorTest::testVectorString();
    VectorTest::testVectorCustom();
    VectorTest::onEnd();
}
