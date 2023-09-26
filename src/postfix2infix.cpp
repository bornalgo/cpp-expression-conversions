#include <iostream>
#include <string>
#include <stack>

// Function to check if a character is an operator
bool is_operator(char chr) {
    return (chr == '(' || chr == ')' || chr == '^' || chr == '+' || chr == '-' || chr == '*' || chr == '/');
}

// Function to convert postfix expression to infix expression
std::string postfix_to_infix(const std::string& postfix, std::stack<std::string>& operands_stack) {
    std::string infix = "";
    
    // Iterate through the postfix expression character by character
    for (char chr : postfix) {
        if (chr == ' ') {
            continue; // Skip whitespace
        }
        if (is_operator(chr)) {
            int i = 0;
            std::string first = "?";
            std::string second = "?";
            
            // Pop the top two operands from the stack
            while (!operands_stack.empty() && i < 2) {
                if (i == 0) {
                    second = operands_stack.top();
                } else {
                    first = operands_stack.top();
                }
                operands_stack.pop();
                ++i;
            }
            
            // Combine the operands and the operator within parentheses
            operands_stack.push("(" + first + std::string(1, chr) + second + ")");
        } else {
            // Push operands onto the stack as single-character strings
            operands_stack.push(std::string(1, chr));
        }
    }
    
    // Pop the final infix expression from the stack
    while (!operands_stack.empty()) {
        infix += operands_stack.top();
        operands_stack.pop();
    }
    
    return infix;
}

int main() {
    std::string postfix;
    std::cout << "Enter the postfix expression: ";
    std::cin >> postfix;
    
    std::stack<std::string> operands_stack;
    std::string infix = postfix_to_infix(postfix, operands_stack);
    
    std::cout << "Postfix expression: " << postfix << std::endl;
    std::cout << "Infix expression: " << infix << std::endl;
    
    return 0;
}
