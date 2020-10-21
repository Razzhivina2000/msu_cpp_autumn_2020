class Parser
{
    std::function<void()> StartCallback;
    std::function<void()> EndCallback;
    std::function<void(const long long &)> DigitTokenCallback;
    std::function<void(const std::string &)> StringTokenCallback;
public:
    Parser();
    void TokenParser(const std::string &s);
    void SetStartCallback(std::function<void()> func);
    void SetEndCallback(std::function<void()> func);
    void SetDigitTokenCallback(std::function<void(const long long &)> func);
    void SetStringTokenCallback(std::function<void(const std::string &)> func);
};
