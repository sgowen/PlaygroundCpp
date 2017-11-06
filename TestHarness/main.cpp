//
//  main.cpp
//  TestHarness
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include <container/HashMapTest.h>
#include <container/VectorTest.h>
#include <operator/BitwiseOperatorTest.h>
#include <sin_table/SinTableTest.h>
#include <uniqueness/UniquenessTest.h>

int main(int argc, const char * argv[])
{
    using namespace NoctisGames;
    
    HashMapTest::testHashMap();
    HashMapTest::testHashMap2();
    
    VectorTest::onBegin();
    VectorTest::testVectorInt();
    VectorTest::testVectorString();
    VectorTest::testVectorCustom();
    VectorTest::onEnd();
    
    BitwiseOperatorTest::testBitWiseOperations();
    
    SinTableTest::testSinTable();

    UniquenessTest::testUniqueness();
}
