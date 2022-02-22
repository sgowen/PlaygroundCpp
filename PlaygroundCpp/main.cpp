//
//  main.cpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#include <casting/CastingTest.hpp>
#include <data_structures/GowArrayTest.hpp>
#include <endianness/EndiannessTest.hpp>
#include <hash_map/HashMapTest.hpp>
#include <operator/BitwiseOperatorTest.hpp>
#include <pool/PoolTest.hpp>
#include <queue/QueueTest.hpp>
#include <recursion/RecursionTest.hpp>
#include <sin_table/SinTableTest.hpp>
#include <string/StringTest.hpp>
#include <threading/ThreadingTest.hpp>

int main(int argc, const char* argv[])
{
    CastingTest::test();
    GowArrayTest::test();
    EndiannessTest::test();
    HashMapTest::test();
    BitwiseOperatorTest::test();
    PoolTest::test();
    QueueTest::test();
    RecursionTest::test();
    SinTableTest::test();
    StringTest::test();
    ThreadingTest::test();
    
    /* TODO
      1. ~~~ DONE ~~~ Implement Array
      2. Implement Set
      3. Implement Ordered Array
      4. Implement Linear Search O(n)
      5. Implement Binary Search O(log n)
      6. Implement Bubble Sort O(n^2)
      7. Implement Selection Sort O(n^2 / 2)
      8. Implement Insertion Sort O(n) to O(n^2)
      9. Implement Hash Table
     10. Implement Stack (abstract data type)
     11. Implement Queue (abstract data type)
     12. ~~~ DONE ~~~ Implement some Recursive Algorithms
     13. Implement SortableArray
     14. Implement Quicksort O(n log n) to O(n^2)
     15. Implement Quickselect O(2n)
     16. Implement Linked List
     17. Implement Doubly Linked List
     18. Implement Binary Search Tree
     19. Implement Priority Queue
     20. Implement Binary Heap (min and max)
     21. Implement Trie
     22. Implement Graph
     23. Implement Dijkstra's algorithm
     24. List examples of when to use Trie, Graph, Linked List, etc.
     */
}
