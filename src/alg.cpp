// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::map<char, std::string> symbols{
    {'0', "num"}, {'1', "num"}, {'2', "num"}, {'3', "num"}, {'4', "num"},
    {'5', "num"}, {'6', "num"}, {'7', "num"}, {'8', "num"}, {'9', "num"},
    {'(', "operation"}, {')', "operation"}, {'+', "operation"},
    {'-', "operation"}, {'*', "operation"}, {'/', "operation"}
};
std::map<char, int> priorities{
    {'(', 0}, {')', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}
};

std::string infx2pstfx(const std::string& inf) {
    std::string out = "";
    TStack<char, 100> stack;
    bool numCheck = false;
    int index = 0;
    while (index < inf.length()) {
        if (symbols[inf[index]] == "num") {
            if (!numCheck && !out.empty())
                out.push_back(' ');
            numCheck = true;
            out.push_back(inf[index]);
        }
        else if (symbols[inf[index]] == "operation") {
            numCheck = false;
            if (stack.empty() || inf[index] == '(' ||
                (priorities[inf[index]] > stack.get())) {
                stack.Push(inf[index]);
            }
            else {
                while (!stack.empty() &&
                    priorities[inf[index]] <= priorities[stack.get()]) {
                    out.push_back(' ');
                    out.push_back(stack.get());
                    stack.Pop();
                }
                stack.Push(inf[index]);
            }
        }
        if (stack.get() == ')') {
            stack.Pop();
            while (stack.get() != '(') {
                out.push_back(' ');
                out.push_back(stack.get());
                stack.Pop();
            }
            stack.Pop();
        }
        index++;
    }
    while (!stack.empty()) {
        out.push_back(' ');
        out.push_back(stack.get());
        stack.Pop();
    }
    return out;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack;
    int index = 0;
    while (index < pref.length()) {
        if (symbols[pref[index]] == "num") {
            int number = 0;
            while (pref[index] != ' ') {
                number *= 10;
                number += pref[index] - 48;
                index++;
            }
            stack.Push(number);
        } else if (symbols[pref[index]] == "operation") {
            int number1 = stack.get();
            stack.Pop();
            int number2 = stack.get();
            stack.Pop();
            if (pref[index] == '+') {
                stack.Push(number2 + number1);
            } else if (pref[index] == '-') {
                stack.Push(number2 - number1);
            } else if (pref[index] == '*') {
                stack.Push(number2 * number1);
            } else if (pref[index] == '/') {
                stack.Push(number2 / number1);
            }
        }
        index++;
    }
    return stack.get();
}
