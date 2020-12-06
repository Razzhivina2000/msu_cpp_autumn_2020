#pragma once

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;
public:
    explicit Serializer(std::ostream& out) : out_(out)
    {
    }
    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
    
private:
    Error process(bool val)
    {
        if(val) {
            out_ << "true" << Separator;
        } else {
            out_ << "false" << Separator;
        }
        return Error::NoError;
    }
    
    Error process(uint64_t val)
    {
        out_ << val << Separator;
        return Error::NoError;
    }
    
    template <class T, class... ArgsT>
    Error process(T val, ArgsT... args)
    {
        process(val);
        return process(args...);
    }
};

class Deserializer
{
    std::istream& in_;
public:
    explicit Deserializer(std::istream& in) : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }
    
private:
    Error process(bool& val)
    {
        std::string text;
        in_ >> text;
        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }
    
    Error process(uint64_t& val)
    {
        std::string text;
        in_ >> text;
        try {
            uint64_t tmp = std::stoull(text);
            val = tmp;
        } catch (const std::logic_error&) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template <class T, class... ArgsT>
    Error process(T& val, ArgsT&... args)
    {
        Error err1 = process(val);
        if(err1 == Error::CorruptedArchive) {
            return err1;
        }
        Error err2 = process(args...);
        if(err2 == Error::CorruptedArchive) {
            return err2;
        }
        return Error::NoError;
    }
};
