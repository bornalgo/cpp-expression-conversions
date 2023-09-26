#include <iostream>
#include <string>
#include <stack>

// Function to check if a character is an operator
bool is_operator(char chr) {
    return (chr == '(' || chr == ')' || chr == '^' || chr == '+' || chr == '-' || chr == '*' || chr == '/');
}

// Function to convert prefix expression to postfix expression
std::string prefix_to_postfix(const std::string& prefix, std::stack<std::string>& operands_stack) {
    std::string postfix = "";

    // Iterate through the prefix expression in reverse
    for (auto iter = prefix.rbegin(); iter != prefix.rend(); ++iter) {
        char chr = *iter;
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
            operands_stack.push(first + second + std::string(1, chr));
        } else {
            // Push operands onto the stack as single-character strings
            operands_stack.push(std::string(1, chr));
        }
    }

    // Pop the final postfix expression from the stack
    while (!operands_stack.empty()) {
        postfix += operands_stack.top();
        operands_stack.pop();
    }

    return postfix;
}

int main() {
    std::string prefix;
    std::cout << "Enter the prefix expression: ";
    std::cin >> prefix;

    std::stack<std::string> operands_stack;
    std::string postfix = prefix_to_postfix(prefix, operands_stack);

    std::cout << "Prefix expression: " << prefix << std::endl;
    std::cout << "Postfix expression: " << postfix << std::endl;

    return 0;
}
