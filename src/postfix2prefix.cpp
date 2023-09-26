#include <iostream>
#include <string>
#include <stack>

// Function to check if a character is an operator
bool is_operator(char chr) {
    return (chr == '(' || chr == ')' || chr == '^' || chr == '+' || chr == '-' || chr == '*' || chr == '/');
}

// Function to convert postfix expression to prefix expression
std::string postfix_to_prefix(const std::string& postfix, std::stack<std::string>& operands_stack) {
    std::string prefix = "";

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

            // Combine the operands and the operator
            operands_stack.push(std::string(1, chr) + first + second);
        } else {
            // Push operands onto the stack as single-character strings
            operands_stack.push(std::string(1, chr));
        }
    }

    // Pop the final prefix expression from the stack
    while (!operands_stack.empty()) {
        prefix += operands_stack.top();
        operands_stack.pop();
    }

    return prefix;
}

int main() {
    std::string postfix;
    std::cout << "Enter the postfix expression: ";
    std::cin >> postfix;

    std::stack<std::string> operands_stack;
    std::string prefix = postfix_to_prefix(postfix, operands_stack);

    std::cout << "Postfix expression: " << postfix << std::endl;
    std::cout << "Prefix expression: " << prefix << std::endl;

    return 0;
}
