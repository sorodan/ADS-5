// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int Size>
class TStack {
private:
    T arr[Size];
    int top;

public:
    TStack() :top(-1) {}
    bool empty() const {
        return top == -1;
    }
    bool full() const {
        return top == Size - 1;
    }
    T get() const {
        if (!empty())
            return arr[top];
        else
            return 0;
    }
    void Pop() {
        if (!empty())
            top--;
    }
    void Push(T item) {
        if (!full())
            arr[++top] = item;
    }
};

#endif  // INCLUDE_TSTACK_H_#pragma once
