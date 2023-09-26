#include <iostream>
#include <string>
#include <stack>

// Function to check if a character is an operator
bool is_operator(char chr) {
    return (chr == '(' || chr == ')' || chr == '^' || chr == '+' || chr == '-' || chr == '*' || chr == '/');
}

// Function to determine precedence of operators
// Returns 1 for higher precedence, -1 for lower precedence, and 0 for equal precedence
int get_precedence(char operatorPush, char operatorTop) {
    if ((operatorPush == '^' && operatorTop != '^') ||
        ((operatorPush == '*' || operatorPush == '/') && (operatorTop != '*' && operatorTop != '/'))) {
        return 1;
    } else if ((operatorPush != '^' && operatorTop == '^') ||
               ((operatorPush != '*' && operatorPush != '/') && (operatorTop == '*' || operatorTop == '/'))) {
        return -1;
    } else {
        return 0;
    }
}

// Function to convert infix expression to prefix expression
std::string infix_to_prefix(const std::string& infix, std::stack<char>& operators_stack) {
    std::string prefix = "";

    // Iterate through the infix expression in reverse
    for (auto it = infix.rbegin(); it != infix.rend(); ++it) {
        char chr = *it;

        // Ignore spaces
        if (chr == ' ') {
            continue;
        }

        if (is_operator(chr)) {
            switch (chr) {
                case ')':
                    operators_stack.push(chr);
                    break;
                case '(':
                    // Pop operators from the stack until a matching ')' is found
                    while (!operators_stack.empty()) {
                        char operatorTop = operators_stack.top();
                        operators_stack.pop();
                        if (operatorTop == ')') {
                            break;
                        } else {
                            prefix = operatorTop + prefix;
                        }
                    }
                    break;
                default:
                    if (operators_stack.empty()) {
                        operators_stack.push(chr);
                    } else {
                        // Pop operators with higher or equal precedence
                        while (true) {
                            char operatorTop = operators_stack.top();
                            int precedence = get_precedence(chr, operatorTop);
                            if (precedence > 0 || operatorTop == '(' || operatorTop == ')') {
                                operators_stack.push(chr);
                                break;
                            } else {
                                prefix = operatorTop + prefix;
                                operators_stack.pop();
                                if (operators_stack.empty()) {
                                    operators_stack.push(chr);
                                    break;
                                }
                            }
                        }
                    }
                    break;
            }
        } else {
            // Append operands to the prefix expression
            prefix = chr + prefix;
        }
    }

    // Pop any remaining operators from the stack
    while (!operators_stack.empty()) {
        prefix = operators_stack.top() + prefix;
        operators_stack.pop();
    }

    return prefix;
}

int main() {
    std::string infix;
    std::cout << "Enter the infix expression: ";
    std::cin >> infix;

    std::stack<char> operators_stack;
    std::string prefix = infix_to_prefix(infix, operators_stack);

    std::cout << "Infix expression: " << infix << std::endl;
    std::cout << "Prefix expression: " << prefix << std::endl;

    return 0;
}
