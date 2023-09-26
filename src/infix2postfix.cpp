#include <iostream>
#include <string>
#include <stack>

// Function to check if a character is an operator
bool is_operator(char chr) {
    return (chr == '(' || chr == ')' || chr == '^' || chr == '+' || chr == '-' || chr == '*' || chr == '/');
}

// Function to determine the precedence of operators
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

// Function to convert infix expression to postfix expression
std::string infix_to_postfix(const std::string& infix, std::stack<char>& operators_stack) {
    std::string postfix = "";

    // Iterate through the infix expression character by character
    for (char chr : infix) {
        if (chr == ' ') {
            continue; // Skip whitespace
        }
        if (is_operator(chr)) {
            switch (chr) {
                case '(':
                    operators_stack.push(chr);
                    break;
                case ')':
                    // Pop operators from the stack until a matching '(' is found
                    while (!operators_stack.empty()) {
                        char operatorTop = operators_stack.top();
                        operators_stack.pop();
                        if (operatorTop == '(') {
                            break;
                        } else {
                            postfix += operatorTop;
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
                            if (precedence > 0 || operatorTop == '(' || operatorTop == ')' || (precedence == 0 && chr == '^')) {
                                operators_stack.push(chr);
                                break;
                            } else {
                                postfix += operatorTop;
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
            postfix += chr; // Append operands to the postfix expression
        }
    }

    // Pop any remaining operators from the stack
    while (!operators_stack.empty()) {
        postfix += operators_stack.top();
        operators_stack.pop();
    }

    return postfix;
}

int main() {
    std::string infix;
    std::cout << "Enter the infix expression: ";
    std::cin >> infix;

    std::stack<char> operators_stack;
    std::string postfix = infix_to_postfix(infix, operators_stack);

    std::cout << "Infix expression: " << infix << std::endl;
    std::cout << "Postfix expression: " << postfix << std::endl;

    return 0;
}
