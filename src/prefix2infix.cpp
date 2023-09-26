#include <iostream>
#include <string>
#include <stack>

// Function to check if a character is an operator
bool is_operator(char chr) {
    return (chr == '(' || chr == ')' || chr == '^' || chr == '+' || chr == '-' || chr == '*' || chr == '/');
}

// Function to convert prefix expression to infix expression
std::string prefix_to_infix(const std::string& prefix, std::stack<std::string>& operands_stack) {
    std::string infix = "";

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
    std::string prefix;
    std::cout << "Enter the prefix expression: ";
    std::cin >> prefix;

    std::stack<std::string> operands_stack;
    std::string infix = prefix_to_infix(prefix, operands_stack);

    std::cout << "Prefix expression: " << prefix << std::endl;
    std::cout << "Infix expression: " << infix << std::endl;

    return 0;
}
