//
//  GowArray.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 2/21/22.
//  Copyright © 2022 Stephen Gowen. All rights reserved.
//

#pragma once

#include "GowMemoryAllocator.hpp"

#include <stdlib.h>
#include <memory>
#include <assert.h>

template <typename T>
class GowArray
{
public:
    GowArray() :
    _size(0),
    _capacity(0),
    _buffer(nullptr)
    {
        // Empty
    }
    
    GowArray(const GowArray& other) :
    _size(other._size),
    _capacity(other._capacity),
    _buffer(nullptr)
    {
        if (_capacity > 0)
        {
            _buffer = allocate(_capacity);
            for (size_t i = 0; i < _size; ++i)
            {
                construct(_buffer + i, other._buffer[i]);
            }
        }
    }
    
    GowArray& operator=(GowArray& other)
    {
        if (this != &other)
        {
            clear();
            deallocate();
            
            _size = other._size;
            _capacity = other._capacity;
            
            if (_capacity > 0)
            {
                _buffer = allocate(_capacity);
                for (size_t i = 0; i < _size; ++i)
                {
                    construct(_buffer + i, other._buffer[i]);
                }
            }
        }
        
        return *this;
    }
    
    ~GowArray()
    {
        clear();
        deallocate();
    }
    
    bool contains(const T& value)
    {
        if (_buffer == nullptr)
        {
            return false;
        }
        
        for (size_t i = 0; i < _size; ++i)
        {
            if (_buffer[i] == value)
            {
                return true;
            }
        }
        
        return false;
    }
    
    size_t indexOf(const T& value)
    {
        assert(_buffer != nullptr);
        
        for (size_t i = 0; i < _size; ++i)
        {
            if (_buffer[i] == value)
            {
                return i;
            }
        }
        
        return -1;
    }
    
    void push_back(const T& value)
    {
        if (_size == _capacity)
        {
            expand();
        }
        
        construct(_buffer + _size++, value);
    }
    
    void insert(size_t index, const T& value)
    {
        assert(index < _size);
        
        if (_size == _capacity)
        {
            expand();
        }
        
        for (size_t i = ++_size - 1; i > index; --i)
        {
            construct(_buffer + i, _buffer[i - 1]);
            destruct(_buffer + (i - 1));
        }
        
        construct(_buffer + index, value);
    }
    
    void erase(size_t index)
    {
        assert(index < _size);
        
        --_size;
        
        if (index != _size)
        {
            for (size_t i = index; i < _size; ++i)
            {
                std::swap(_buffer[i], _buffer[i + 1]);
            }
        }
        
        destruct(_buffer + _size);
    }
    
    void clear()
    {
        for (size_t i = 0; i < _size; ++i)
        {
            destruct(_buffer + (_size - 1 - i));
        }
        
        _size = 0;
    }
    
    size_t size() const
    {
        return _size;
    }
    
    size_t capacity() const
    {
        return _capacity;
    }
    
    T& operator[](size_t index)
    {
        assert(index < _size);
        
        return _buffer[index];
    }
    
    void reserve(size_t capacity)
    {
        if (capacity > _capacity)
        {
            _buffer = GOW_REALLOC(_buffer, T, capacity);
            assert(_buffer != nullptr);
            _capacity = capacity;
        }
    }
    
    T* begin()
    {
        return &_buffer[0];
    }
    
    T* end()
    {
        return &_buffer[_size - 1];
    }
    
    friend bool operator==(GowArray<T>& lhs, GowArray<T>& rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        
        for (size_t i = 0, n = lhs.size(); i < n; ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        
        return true;
    }
    
    friend bool operator!=(GowArray<T>& lhs, GowArray<T>& rhs)
    {
        return !(lhs == rhs);
    }
    
private:
    size_t _size;
    size_t _capacity;
    T* _buffer;
    
    void expand()
    {
        if (_capacity == 0)
        {
            _capacity = 1;
        }
        reserve(_capacity * 2);
    }
    
    T* allocate(size_t count)
    {
        assert(count > 0);
        
        T* ptr = GOW_MALLOC(T, count);
        assert(ptr != nullptr);
        
        return ptr;
    }
    
    void deallocate()
    {
        GOW_FREE(_buffer);
    }
    
    void construct(T* buffer, const T& val)
    {
        new (buffer) T(val);
    }
    
    void destruct(T* buffer)
    {
        buffer->~T();
    }
};
