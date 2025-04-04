#include "parser.h"
#include "calculator.h"
#include <iostream>
using std::cin, std::cout, std::to_string, std::string;
using namespace calculator;

// typedef long double ld;

string parseBrackets(string expression) {
  int start_count = 0; // number of "(" opening brackets
  int stop_count = 0;  // number of ")" closing brackets
  int start_ind = 0;

  for (int i = 0; i < expression.length(); ++i) {
    if (expression[i] == '(') {
      if (!start_count) {
        start_ind = i; // identified first opening bracket
      }
      ++start_count;
    } else if (expression[i] == ')') {
      ++stop_count;
    }

    if (start_count && start_count == stop_count) {
      // when the start_ind bracket is finally closed, the expression inside
      // will be returned
      return expression.substr(start_ind + 1, (i - 1 - start_ind));
    }
  }

  // If the first bracket was never closed:
  cout << "Missing brackets.\n";
  exit(1);
}

string parseMultDiv(string expression) {
  /**
   * Determines where the RHS of the multiplication/division ends to ensure
   * correct precedence.
   */

  string part = ""; // Expression to be returned
  bool sign = false;
  char a;

  for (int i = 0; i < expression.length(); ++i) {
    a = expression[i];

    if (string("*/+-").find(a) != string::npos) {
      if (sign)
        return part;
      sign = true;
    } else if (string("0123456789.").find(a) != string::npos) {
      part += a;
    } else if (a == ' ') {
      continue;
    } else if (a == '!') {
      part += a;
      return part;
    } else {
      return part;
    }
  }

  return part;
}

long double compute(string expression) {
  string part = "";
  bool point;

  for (int i = 0; i < expression.length(); ++i) {
    point = false;

    // if (expression[i] == ' ') continue;
    if (string("0123456789.").find(expression[i]) != string::npos) {
      part += expression[i];
      if (expression[i] == '.')
        point = true;

    } else if (!part.empty()) {
      switch (expression[i]) {
      case '+':
        // if (point) return add(stold(part), compute(expression.substr(i +
        // 1)));
        return add(stold(part), compute(expression.substr(i + 1)));

      case '-':
        // if (point) return sub(stold(part), compute(expression.substr(i +
        // 1)));
        return sub(stold(part), compute(expression.substr(i + 1)));

      case '*': {
        for (int j = i + 1; j < expression.length(); ++j) {
          char a = expression[j];

          if (a == ' ') {
            continue;
          } else if (string("0123456789").find(a) != string::npos) {
            string content = parseMultDiv(expression.substr(i));
            int end_ind = i + content.length();
            if (end_ind == expression.length() - 1) {
              return mult(stold(part), compute(content));
            } else {
              return compute(to_string(mult(stold(part), compute(content))) +
                             expression.substr(end_ind + 1));
            }
          } else if (string("(lg").find(a) != string::npos) {
            switch (a) {
            case '(': {
              string content = parseBrackets(expression.substr(j));
              int end_ind = j + content.length() + 1;
              if (end_ind == expression.length() - 1) {
                return mult(stold(part), compute(content));
              } else {
                return compute(to_string(mult(stold(part), compute(content))) +
                               expression.substr(end_ind + 1));
              }
            }

            case 'g': {
              string content = parseBrackets(expression.substr(j));
              int comma_ind = content.find(',');
              int end_ind = j + content.length() + 4;
              string first_item =
                  to_string(compute(content.substr(0, comma_ind)));
              string second_item = to_string(compute(content.substr(
                  comma_ind + 1, end_ind - expression.find(',') - 1)));
              if (end_ind == expression.length() - 1) {
                return gcd(stoll(first_item), stoll(second_item));
              } else {
                return compute(
                    to_string(mult(stold(part),
                                   (long double)gcd(stoll(first_item),
                                                    stoll(second_item)))) +
                    expression.substr(end_ind + 1));
              }
            }

            case 'l': {
              string content = parseBrackets(expression.substr(j));
              int comma_ind = content.find(',');
              int end_ind = j + content.length() + 4;
              string first_item =
                  to_string(compute(content.substr(0, comma_ind)));
              string second_item = to_string(compute(content.substr(
                  comma_ind + 1, end_ind - expression.find(',') - 1)));
              if (end_ind == expression.length() - 1) {
                return mult(stold(part), (long double)lcm(stoll(first_item),
                                                          stoll(second_item)));
              } else {
                return compute(
                    to_string(mult(stold(part),
                                   (long double)lcm(stoll(first_item),
                                                    stoll(second_item)))) +
                    expression.substr(end_ind + 1));
              }
            }
            }
          }
        }

        // return mult(stold(part), compute(expression.substr(i + 1)));
      }

      case '/':
        for (int j = i + 1; j < expression.length(); ++j) {
          char a = expression[j];

          if (a == ' ') {
            continue;
          } else if (string("0123456789").find(a) != string::npos) {
            string content = parseMultDiv(expression.substr(i));
            int end_ind = i + content.length();
            if (end_ind == expression.length() - 1) {
              return div(stold(part), compute(content));
            } else {
              return compute(to_string(div(stold(part), compute(content))) +
                             expression.substr(end_ind + 1));
            }
          } else if (string("(lg").find(a) != string::npos) {
            switch (a) {
            case '(': {
              string content = parseBrackets(expression.substr(j));
              int end_ind = j + content.length() + 1;
              if (end_ind == expression.length() - 1) {
                return div(stold(part), compute(content));
              } else {
                return compute(to_string(div(stold(part), compute(content))) +
                               expression.substr(end_ind + 1));
              }
            }

            case 'g': {
              string content = parseBrackets(expression.substr(j));
              int comma_ind = content.find(',');
              int end_ind = j + content.length() + 4;
              string first_item =
                  to_string(compute(content.substr(0, comma_ind)));
              string second_item = to_string(compute(content.substr(
                  comma_ind + 1, end_ind - expression.find(',') - 1)));
              if (end_ind == expression.length() - 1) {
                return gcd(stoll(first_item), stoll(second_item));
              } else {
                return compute(
                    to_string(div(stold(part),
                                  (long double)gcd(stoll(first_item),
                                                   stoll(second_item)))) +
                    expression.substr(end_ind + 1));
              }
            }

            case 'l': {
              string content = parseBrackets(expression.substr(j));
              int comma_ind = content.find(',');
              int end_ind = j + content.length() + 4;
              string first_item =
                  to_string(compute(content.substr(0, comma_ind)));
              string second_item = to_string(compute(content.substr(
                  comma_ind + 1, end_ind - expression.find(',') - 1)));
              if (end_ind == expression.length() - 1) {
                return div(stold(part), (long double)lcm(stoll(first_item),
                                                         stoll(second_item)));
              } else {
                return compute(
                    to_string(div(stold(part),
                                  (long double)lcm(stoll(first_item),
                                                   stoll(second_item)))) +
                    expression.substr(end_ind + 1));
              }
            }
            }
          }
        }

      case '!':
        return compute(to_string(fact(stoll(part))) + expression.substr(i + 1));

      case '(': {
        string content = parseBrackets(expression.substr(i));
        int end_ind = i + content.length() + 1;
        if (end_ind == expression.length() - 1) {
          return mult(stold(part), compute(content));
        } else {
          return compute(to_string(mult(stold(part), compute(content))) +
                         expression.substr(end_ind + 1));
        }
      }

      case 'g': {
        string content = parseBrackets(expression.substr(i));
        int comma_ind = content.find(',');
        int end_ind = i + content.length() + 4;
        string first_item = to_string(compute(content.substr(0, comma_ind)));
        string second_item = to_string(compute(
            content.substr(comma_ind + 1, end_ind - expression.find(',') - 1)));
        if (end_ind == expression.length() - 1) {
          return gcd(stoll(first_item), stoll(second_item));
        } else {
          return compute(to_string(mult(stold(part),
                                        (long double)gcd(stoll(first_item),
                                                         stoll(second_item)))) +
                         expression.substr(end_ind + 1));
        }
      }

      case 'l': {
        string content = parseBrackets(expression.substr(i));
        int comma_ind = content.find(',');
        int end_ind = i + content.length() + 4;
        string first_item = to_string(compute(content.substr(0, comma_ind)));
        string second_item = to_string(compute(
            content.substr(comma_ind + 1, end_ind - expression.find(',') - 1)));
        if (end_ind == expression.length() - 1) {
          return mult(stold(part),
                      (long double)lcm(stoll(first_item), stoll(second_item)));
        } else {
          return compute(to_string(mult(stold(part),
                                        (long double)lcm(stoll(first_item),
                                                         stoll(second_item)))) +
                         expression.substr(end_ind + 1));
        }
      }
      }

    } else if (part.empty()) {
      switch (expression[i]) {
      case 'g': {
        string content = parseBrackets(expression.substr(i));
        int comma_ind = content.find(',');
        int end_ind = i + content.length() + 4;
        string first_item = to_string(compute(content.substr(0, comma_ind)));
        string second_item = to_string(compute(
            content.substr(comma_ind + 1, end_ind - expression.find(',') - 1)));
        if (end_ind == expression.length() - 1) {
          return gcd(stoll(first_item), stoll(second_item));
        } else {
          return compute(to_string(gcd(stoll(first_item), stoll(second_item))) +
                         expression.substr(end_ind + 1));
        }
      }

      case 'l': {
        string content = parseBrackets(expression.substr(i));
        int comma_ind = content.find(',');
        int end_ind = i + content.length() + 4;
        string first_item = to_string(compute(content.substr(0, comma_ind)));
        string second_item = to_string(compute(
            content.substr(comma_ind + 1, end_ind - expression.find(',') - 1)));
        if (end_ind == expression.length() - 1) {
          return lcm(stoll(first_item), stoll(second_item));
        } else {
          return compute(to_string(lcm(stoll(first_item), stoll(second_item))) +
                         expression.substr(end_ind + 1));
        }
      }

      case '(': {
        string content = parseBrackets(expression.substr(i));
        int end_ind = i + content.length() + 1;
        if (end_ind == expression.length() - 1) {
          return compute(content);
        } else {
          return compute(to_string(compute(content)) +
                         expression.substr(end_ind + 1));
        }
      }
        // lcm(b,c)
        // 01234567
        // i    c e
        // length = 4
      }
    }
  }

  return stold(part);
}
