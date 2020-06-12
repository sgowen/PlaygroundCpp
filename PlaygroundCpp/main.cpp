//
//  main.cpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#include <bitmask/BitMaskTest.hpp>
#include <casting/CastingTest.hpp>
#include <endianness/EndiannessTest.hpp>
#include <hash_map/HashMapTest.hpp>
#include <math/MathTest.hpp>
#include <memory/MemoryTest.hpp>
#include <misc/MiscTest.hpp>
#include <operator/BitwiseOperatorTest.hpp>
#include <pool/PoolTest.hpp>
#include <queue/QueueTest.hpp>
#include <random_file_access/RandomFileAccessTest.hpp>
#include <sin_table/SinTableTest.hpp>
#include <string_split/StringSplitTest.hpp>
#include <threading/ThreadingTest.hpp>
#include <uniqueness/UniquenessTest.hpp>
#include <vector/VectorTest.hpp>
#include <vector/Extension.hpp>

int main(int argc, const char* argv[])
{
    NGExtension::setInstance(DefaultNGExtension::getInstance());
    
    BitMaskTest::test();
    CastingTest::test();
    EndiannessTest::test();
    HashMapTest::test();
    MathTest::test();
//    MemoryTest::test(); // TODO, this is currently crashing
    MiscTest::test();
    BitwiseOperatorTest::test();
    PoolTest::test();
    QueueTest::test();
//    RandomFileAccessTest::test(); // TODO, Uh oh, Sample.dat could not be opened for reading!
    SinTableTest::test();
    StringSplitTest::test();
    ThreadingTest::test();
    UniquenessTest::test();
    VectorTest::test();
}
