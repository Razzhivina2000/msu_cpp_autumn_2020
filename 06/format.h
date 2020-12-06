#pragma once

#include <sstream>
#include <vector>

struct Error
{
    std::string message;
    Error(const std::string& str) : message(str) {}
};

std::stringstream ss_error;

std::string f(const std::string &str, const std::vector<std::string> &args) {
    std::string res = "";
    std::string num = "";
    bool p = false;
    size_t len = str.size();
    int k = args.size();
    for (size_t i = 0; i < len; ++i) {
        if(p) {
            if (str[i] >= '0' && str[i] <= '9') {
                num += str[i];
            } else if (str[i] == '}') {
                if(num == "") {
                    throw Error("FormatError: String is invalid");
                }
                int n;
                try {
                    n = std::stoi(num);
                } catch(const std::out_of_range&) {
                    throw Error("IndexError: index out of range");
                }
                if (n >= 0 && n < k)
                    res += args[n];
                else
                    throw Error("IndexError: index out of range");
                num = "";
                p = false;
            } else {
                throw Error("FormatError: String is invalid");
            }
        } else {
            if (str[i] == '{') {
                p = true;
            } else {
                res += str[i];
            }
        }
    }
    if(p) {
        throw Error("FormatError: String is invalid");
    }
    return res;
}

template<class Arg>
std::string to_string(Arg&& arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

template<class Arg, class... Args>
inline std::string f(const std::string& str, std::vector<std::string>& arguments, Arg&& arg, Args&& ... args) {
    arguments.push_back(to_string(std::forward<Arg>(arg)));
    return f(str, arguments, std::forward<Args>(args)...);
}

template<class Arg, class... Args>
std::string format(const std::string& str, Arg&& arg, Args&&... args) {
    std::vector<std::string> arguments;
    std::string result;
    try {
        result = f(str, arguments, std::forward<Arg>(arg), std::forward<Args>(args)...);
    }
    catch (const Error &e)
    {
        ss_error << e.message << std::endl;
    }
    return result;
}
