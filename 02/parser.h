#pragma once

class Parser
{
    std::function<void()> StartCallback;
    std::function<void()> EndCallback;
    std::function<void(long long)> DigitTokenCallback;
    std::function<void(const std::string &)> StringTokenCallback;
public:
    Parser();
    void Callback(const std::string &token, int is_digit);
    void TokenParser(const std::string &s);
    void SetStartCallback(std::function<void()> func);
    void SetEndCallback(std::function<void()> func);
    void SetDigitTokenCallback(std::function<void(long long)> func);
    void SetStringTokenCallback(std::function<void(const std::string &)> func);
};
