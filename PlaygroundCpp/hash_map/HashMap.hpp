//
//  HashMap.hpp
//  HashMap
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include "GowMemoryAllocator.hpp"
#include <data_structures/GowArray.hpp>

template <typename K, typename V, typename H>
class HashMap
{
private:
    class Entry;
    
public:
    class Iterator
    {
        friend class HashMap;
        
    public:
        Iterator(Entry* entry = nullptr) : _entry(entry)
        {
            // Empty
        }
        
        Iterator& operator++()
        {
            _entry = _entry->next;
            return *this;
        }
        
        Iterator& operator--()
        {
            _entry = _entry->prev;
            return *this;
        }
        
        bool operator==(const Iterator& p) const
        {
            return _entry == p._entry;
        }
        
        bool operator!=(const Iterator& p) const
        {
            return _entry != p._entry;
        }
        
        K& first()
        {
            return _entry->_key;
        }
        
        V& second()
        {
            return _entry->_value;
        }
        
    private:
        Entry* _entry;
    };
    
    HashMap(size_t capacity = 65535) :
    _hashFunction(),
    _capacity(capacity),
    _header(),
    _trailer(),
    _hashSize(0)
    {
        _hashTable.reserve(capacity);
        for (int i = 0; i < _capacity; ++i)
        {
            _hashTable.push_back(Entry());
        }
        
        _header.prev = &_header;
        _header.next = &_trailer;
        _trailer.prev = &_header;
        _trailer.next = &_trailer;
    }
    
    ~HashMap()
    {
        _hashSize = 0;
    }
    
    size_t size()
    {
        return _hashSize;
    }
    
    Iterator begin()
    {
        return Iterator(_header.next);
    }
    
    Iterator end()
    {
        return Iterator(&_trailer);
    }
    
    Iterator rbegin()
    {
        return Iterator(_trailer.prev);
    }
    
    Iterator rend()
    {
        return Iterator(_header);
    }
    
    std::pair<Iterator, bool> insert(const K& key, const V& value)
    {
        Iterator iter = find(key);
        
        if (iter._entry != &_trailer)
        {
            return std::make_pair(iter, false);
        }
        
        size_t index = hash(key);
        
        Entry* entry = GOW_NEW(Entry);
        new (entry) Entry(key, value);
        
        ++_hashSize;
        
        if (_header.next == (&_trailer))
        {
            _hashTable[index].next = entry;
            _hashTable[index].prev = entry;
            _header.next = entry;
            entry->prev = &_header;
            entry->next = &_trailer;
            _trailer.prev = entry;
            
            return std::make_pair(Iterator(entry), true);
        }
        
        if (_hashTable[index].next == nullptr)
        {
            _hashTable[index].next = entry;
            _hashTable[index].prev = entry;
            if (index < hash(_header.next->_key))
            {
                entry->next = _header.next;
                entry->prev = &_header;
                _header.next->prev = entry;
                _header.next = entry;
            }
            else
            {
                entry->next = &_trailer;
                entry->prev = _trailer.prev;
                _trailer.prev = entry;
                entry->prev->next = entry;
            }
            
            return std::make_pair(Iterator(entry), true);
        }
        
        if (index == hash(_header.next->_key))
        {
            _header.next = entry;
            entry->next = _hashTable[index].next;
            entry->prev = &_header;
            _hashTable[index].next->prev = entry;
            _hashTable[index].next = entry;
        }
        else
        {
            entry->next = _hashTable[index].next;
            entry->prev = _hashTable[index].next->prev;
            entry->next->prev = entry;
            entry->prev->next = entry;
            _hashTable[index].next = entry;
        }
        
        return std::make_pair(Iterator(entry), true);
    }
    
    Iterator find(const K& key)
    {
        const size_t index = hash(key);
        Iterator iter(_hashTable[index].next);
        
        if (iter._entry != nullptr)
        {
            for ( ; hash(iter._entry->_key) == index ; ++iter)
            {
                if (iter._entry->_key == key)
                {
                    return iter;
                }
            }
        }
        
        return Iterator(&_trailer);
    }
    
    Iterator erase(Iterator pos)
    {
        if (pos._entry != &_header && pos._entry != &_trailer)
        {
            Entry* next = pos._entry->next;
            
            size_t index = hash(pos._entry->_key);
            
            if (_hashTable[index].next == pos._entry && _hashTable[index].prev == pos._entry)
            {
                _hashTable[index].next = nullptr;
                _hashTable[index].prev = nullptr;
                
                if (_header.next == pos._entry)
                {
                    _header.next = pos._entry->next;
                    pos._entry->next->prev = &_header;
                }
                else if (_trailer.prev == pos._entry)
                {
                    _trailer.prev = pos._entry->prev;
                    pos._entry->prev->next = &_trailer;
                }
                else
                {
                    pos._entry->prev->next = pos._entry->next;
                    pos._entry->next->prev = pos._entry->prev;
                }
                
                GOW_DESTROY(pos._entry, Entry);
            }
            else if (_hashTable[index].next == pos._entry)
            {
                _hashTable[index].next = pos._entry->next;
                if (_header.next == pos._entry)
                {
                    _header.next = pos._entry->next;
                    pos._entry->next->prev = &_header;
                }
                else
                {
                    pos._entry->prev->next = pos._entry->next;
                    pos._entry->next->prev = pos._entry->prev;
                }
                
                GOW_DESTROY(pos._entry, Entry);
            }
            else if (_hashTable[index].prev == pos._entry)
            {
                _hashTable[index].prev = pos._entry->prev;
                if (_trailer.prev == pos._entry)
                {
                    _trailer.prev = pos._entry->prev;
                    pos._entry->prev->next = &_trailer;
                }
                else
                {
                    pos._entry->prev->next = pos._entry->next;
                    pos._entry->next->prev = pos._entry->prev;
                }
                
                GOW_DESTROY(pos._entry, Entry);
            }
            else
            {
                pos._entry->prev->next = pos._entry->next;
                pos._entry->next->prev = pos._entry->prev;
                
                GOW_DESTROY(pos._entry, Entry);
            }
            
            _hashSize--;
            
            return Iterator(next);
        }
        
        return Iterator(&_trailer);
    }
    
    V operator[](const K& key)
    {
        Iterator iter = find(key);
        
        if (iter._entry != _trailer)
        {
            return iter._entry->_value;
        }
        
        return V();
    }
    
private:
    class Entry
    {
    public:
        K _key;
        V _value;
        Entry* next;
        Entry* prev;
        
        Entry(K key, V value) :
        _key(key),
        _value(value),
        next(nullptr),
        prev(nullptr)
        {
            // Empty
            printf("Entry ctor");
        }
        
        Entry() :
        next(nullptr),
        prev(nullptr)
        {
            // Empty
        }
    };
    
    const H _hashFunction;
    const size_t _capacity;
    GowArray<Entry> _hashTable;
    Entry _header;
    Entry _trailer;
    size_t _hashSize;
    
    size_t hash(const K& key)
    {
        return _hashFunction(key) % _capacity;
    }
};
