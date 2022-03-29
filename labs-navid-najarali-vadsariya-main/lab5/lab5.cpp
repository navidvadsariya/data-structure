#include <iostream>
#include "stack.h"

bool bracketCheck(const std::string& s){
    Stack<char> stack;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack.push(s[i]);
        }
        else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            char lastCharInStack = stack.top();
            if ((s[i] == ')' && lastCharInStack == '(') || 
                (s[i] == ']' && lastCharInStack == '[') || 
                (s[i] == '}' && lastCharInStack == '{')) {
                stack.pop();
            }
            else {
                return false;
            }
        }
    }

    // at this point stack should be empty if its not empty that means there were some brackets left in stack
    return stack.isEmpty();
}
