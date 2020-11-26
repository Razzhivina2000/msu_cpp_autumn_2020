#pragma once

template<class T>
class allocator
{
public:
    T* allocate(size_t count);
    void deallocate(T* ptr);
};

template <class T>
class Iterator
    : public std::iterator<std::forward_iterator_tag, T>
{
    T* current_;

public:
    Iterator(T* current);

    bool operator==(const Iterator& other) const;

    bool operator!=(const Iterator& other) const;

    void operator++();

    T& operator*() const;
};

template <class T>
class Reverse_Iterator
    : public std::iterator<std::forward_iterator_tag, T>
{
    T* current_;

public:
    Reverse_Iterator(T* current);

    bool operator==(const Reverse_Iterator& other) const;

    bool operator!=(const Reverse_Iterator& other) const;

    void operator++();

    T& operator*() const;
};


template < class T, class Alloc = allocator<T> >
class vector {
    
    size_t capacity_ = 0;
    size_t size_ = 0;
    T* data_ = nullptr;
    
public:
    typedef Iterator<T> iterator;
    typedef Reverse_Iterator<T> reverse_iterator;
    
    vector();
    
    explicit vector(size_t count) : size_(count), capacity_(count) {
        data_ = Alloc().allocate(count);
    }
    
    vector(size_t count, const T& defaultValue);
    
    vector(const vector<T> &other);
    
    vector(std::initializer_list<T> values);
    
    T& operator[](size_t pos);
    
    const T& operator[](size_t pos) const;
    
    void push_back(const T& value);
    
    void pop_back();
    
    template < class... Args >
    void emplace_back(Args&&... args);
    
    bool empty() const noexcept;
    
    size_t size() const noexcept;
    
    void clear() noexcept;
    
    iterator begin() noexcept;
    
    iterator end() noexcept;

    reverse_iterator rbegin() noexcept;
    
    reverse_iterator rend() noexcept;
    
    void resize(size_t count);
    
    void reserve(size_t count);
    
    size_t capacity() const noexcept;
    
    ~vector();
};
