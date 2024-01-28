#ifndef AUTOPTR_H
#define AUTOPTR_H

#include <iostream>
using namespace std;

template <typename T>
class CustomUniquePtr {
private:
    T* ptr;

public:
    CustomUniquePtr(T* p) : ptr(p) {}

    ~CustomUniquePtr() {
        delete ptr;
    }

    T* get() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

  
    CustomUniquePtr(const CustomUniquePtr&) = delete;
    CustomUniquePtr& operator=(const CustomUniquePtr&) = delete;
};

template <typename T>
class CustomSharedPtr {
private:
    T* ptr;
    int* refCount;

public:
    CustomSharedPtr(T* p) : ptr(p), refCount(new int(1)) {}

    ~CustomSharedPtr() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    CustomSharedPtr(const CustomSharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        (*refCount)++;
    }

    CustomSharedPtr& operator=(const CustomSharedPtr& other) {
        if (this != &other) {
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }

            ptr = other.ptr;
            refCount = other.refCount;
            (*refCount)++;
        }
        return *this;
    }

    T* get() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    int useCount() const {
        return *refCount;
    }
};

#endif