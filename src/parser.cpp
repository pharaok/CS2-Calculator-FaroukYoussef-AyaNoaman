#include <iostream>
#include "parser.h"
#include "calculator.h"
using std::cin, std::cout, std::to_string;

// typedef long double ld;


string parseBrackets(string expression) {
    int start_count = 0;
    int stop_count = 0;
    int start_ind = 0;

    for (int i = 0; i < expression.length(); ++i) {
        if (expression[i] == '(') {
            if (!start_count) {
                start_ind = i;
            }

            ++start_count;
        } else if (expression[i] == ')') {
            ++stop_count;
        }

        if (start_count && start_count == stop_count) {
            return expression.substr(start_ind + 1, (i - 1 - start_ind));
        }
    }

    return "Missing brackets";
}


long double compute(string expression) {
    string part = "";
    bool point;

    for (int i = 0; i < expression.length(); ++i) {
        point = false;

        // if (expression[i] == ' ') continue;
        if (string("0123456789.").find(expression[i]) != string::npos) {
            part += expression[i];
            if (expression[i] == '.') point = true;


        } else if (!part.empty() && string("+-*/!").find(expression[i]) != string::npos) {
            switch (expression[i]) {
                case '+':
                    // if (point) return add(stold(part), compute(expression.substr(i + 1)));
                     return add(stold(part), compute(expression.substr(i + 1)));

                case '-':
                    // if (point) return sub(stold(part), compute(expression.substr(i + 1)));
                     return sub(stold(part), compute(expression.substr(i + 1)));

                case '*':
                    return mult(stold(part), compute(expression.substr(i + 1)));

                case '/':
                    return div(stold(part), compute(expression.substr(i + 1)));
                
                case '!':
                    return compute(to_string(fact(stoll(part))) + expression.substr(i + 1));
            }

        } else if (part.empty() && string("gl(").find(expression[i]) != string::npos) {
            switch (expression[i]) {
                case 'g': {
                    string content = parseBrackets(expression.substr(i));
                    int comma_ind = content.find(',');
                    int end_ind = i + content.length();
                    string first_item = content.substr(0, comma_ind - 1);
                    string second_item = content.substr(comma_ind + 1, content.length() - comma_ind - 1);
                    if (end_ind == expression.length() - 1) {
                        return gcd(stoll(first_item), stoll(second_item));
                    } else {
                        return compute(to_string(gcd(stoll(first_item), stoll(second_item))) + expression.substr(end_ind + 1));
                    }
                }

                case 'l': {
                    string content = parseBrackets(expression.substr(i));
                    int comma_ind = content.find(',');
                    int end_ind = i + content.length() + 1;
                    string first_item = content.substr(0, comma_ind - 1);
                    string second_item = content.substr(comma_ind + 1, content.length() - comma_ind - 1);
                    if (end_ind == expression.length() - 1) {
                        return lcm(stoll(first_item), stoll(second_item));
                    } else {
                        return compute(to_string(lcm(stoll(first_item), stoll(second_item))) + expression.substr(end_ind + 1));
                    }
                }
                
                case '(':
                    string content = parseBrackets(expression.substr(i));
                    int end_ind = i + content.length() + 1;
                    if (end_ind == expression.length() - 1) {
                        return compute(content);
                    } else {
                        return compute(to_string(compute(content)) + expression.substr(end_ind + 1));
                    }
                    // a ( b+c)
                    // 01234567
                    //   i    end
                    // length = 4
            }
        }
    }

    return stold(part);
}


int main() {
    cout << compute("8 * (13 + 2) * 2") << "\n";
}