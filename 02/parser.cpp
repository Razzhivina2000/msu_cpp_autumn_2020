#include <iostream>
#include <ctype.h>
#include <functional>
#include "parser.h"

void default_function() {}
void default_function2(long long i) {}
void default_function3(std::string i) {}

Parser::Parser(): StartCallback(default_function), DigitTokenCallback(default_function2), StringTokenCallback(default_function3), EndCallback(default_function) {}

void Parser::TokenParser(const std::string &s) {
    StartCallback();
    std::string token = "";
    int is_digit = 1;
    for (int i = 0; i < s.size(); i++) {
        if(isspace(s[i])) {
            if(token != "") {
                if(is_digit) {
                    long long digit_token = strtoll(token.c_str(), nullptr, 10);
                    DigitTokenCallback(digit_token);
                } else {
                    StringTokenCallback(token);
                }
                token = "";
                is_digit = 1;
            }
        } else {
            token += s[i];
            if(is_digit && !isdigit(s[i])) {
                is_digit = 0;
            }
        }
    }
    if(token != "") {
        if(is_digit) {
            long long digit_token = strtoll(token.c_str(), nullptr, 10);
            DigitTokenCallback(digit_token);
        } else {
            StringTokenCallback(token);
        }
    }
    EndCallback();
}
void Parser::SetStartCallback(std::function<void()> func) {
    StartCallback = func;
}
void Parser::SetEndCallback(std::function<void()> func) {
    EndCallback = func;
}
void Parser::SetDigitTokenCallback(std::function<void(const long long &)> func) {
    DigitTokenCallback = func;
}
void Parser::SetStringTokenCallback(std::function<void(const std::string &)> func) {
    StringTokenCallback = func;
}


