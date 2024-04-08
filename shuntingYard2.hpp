#include <string>
#include <stack>
#include <cmath>

class Calculator {
private:
    std::string equation;

    // Helper function to convert infix notation to postfix notation
    std::string infixToPostfix(const std::string &infix) {
        std::stack<char> operators;
        std::string postfix;
        
        for (char token : infix) {
            if (isdigit(token) || token == 'x' || token == '.') {
                postfix += token;
            } else if (token == '+' || token == '-' || token == '*' || token == '/') {
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(token);
            } else if (token == '(') {
                operators.push(token);
            } else if (token == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.pop(); // Pop '('
            }
        }
        
        while (!operators.empty()) {
            postfix += operators.top();
            operators.pop();
        }
        
        return postfix;
    }

    // Helper function to determine precedence of operators
    int precedence(char op) {
        if (op == '+' || op == '-')
            return 1;
        else if (op == '*' || op == '/')
            return 2;
        else
            return 0; // Parentheses
    }

    // Helper function to evaluate postfix notation
    double evaluatePostfix(const std::string &postfix, double x) {
        std::stack<double> operands;
        
        for (char token : postfix) {
            if (isdigit(token) || token == 'x' || token == '.') {
                if (token == 'x')
                    operands.push(x);
                else
                    operands.push(token - '0');
            } else {
                double op2 = operands.top();
                operands.pop();
                double op1 = operands.top();
                operands.pop();
                
                switch (token) {
                    case '+':
                        operands.push(op1 + op2);
                        break;
                    case '-':
                        operands.push(op1 - op2);
                        break;
                    case '*':
                        operands.push(op1 * op2);
                        break;
                    case '/':
                        operands.push(op1 / op2);
                        break;
                }
            }
        }
        
        return operands.top();
    }

public:
    Calculator(const std::string &equation) : equation(equation) {}

    // Function to calculate y value using x
    double calculateY(double x) {
        std::string postfix = infixToPostfix(equation);
        return evaluatePostfix(postfix, x);
    }
};
