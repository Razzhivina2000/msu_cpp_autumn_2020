#include <iostream>
#include "vector.h"

template<class T>
T* allocator<T>::allocate(size_t count)
{
    T* ptr = nullptr;

    if (count != 0) {
        ptr = new T[count];
    }
    return ptr;
}

template<class T>
void allocator<T>::deallocate(T* ptr)
{
    delete [] ptr;
}

template <class T>
Iterator<T>::Iterator(T* current) : current_(current)
{
}

template <class T>
bool Iterator<T>::operator==(const Iterator& other) const
{
    return current_ == other.current_;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator& other) const
{
    return !(*this == other);
}

template <class T>
void Iterator<T>::operator++()
{
    ++current_;
}

template <class T>
T& Iterator<T>::operator*() const
{
    return *current_;
}

template <class T>
Reverse_Iterator<T>::Reverse_Iterator(T* current) : current_(current)
{
}

template <class T>
bool Reverse_Iterator<T>::operator==(const Reverse_Iterator& other) const
{
    return current_ == other.current_;
}

template <class T>
bool Reverse_Iterator<T>::operator!=(const Reverse_Iterator& other) const
{
    return !(*this == other);
}

template <class T>
void Reverse_Iterator<T>::operator++()
{
    --current_;
}

template <class T>
T& Reverse_Iterator<T>::operator*() const
{
    return *current_;
}

template < class T, class Alloc >
vector<T, Alloc>::vector() = default;

template < class T, class Alloc >
vector<T, Alloc>::vector(size_t count, const T& defaultValue) : size_(count), capacity_(count) {
    data_ = Alloc().allocate(count);
    for(size_t i = 0; i < count; i++) {
        data_[i] = defaultValue;
    }
}

template < class T, class Alloc >
vector<T, Alloc>::vector(std::initializer_list<T> values) :
    size_(values.size()), capacity_(values.size())
{
    data_ = Alloc().allocate(values.size());
    std::copy(values.begin(), values.end(), data_);
}

template < class T, class Alloc >
vector<T, Alloc>::vector(const vector<T>& other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = Alloc().allocate(other.capacity_);
    for(size_t i = 0; i < other.size_; i++) {
        data_[i] = other[i];
    }
}

template < class T, class Alloc >
vector<T, Alloc>::vector(vector<T>&& other) : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

template < class T, class Alloc >
vector<T>& vector<T, Alloc>::operator=(const vector<T>& other) {
    if(this == &other) {
        return *this;
    }
    Alloc().deallocate(data_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = Alloc().allocate(capacity_);
    for(size_t i = 0; i < other.size_; i++) {
        data_[i] = other[i];
    }
    return *this;
}

template < class T, class Alloc >
vector<T>& vector<T, Alloc>::operator=(vector<T>&& other) {
    if(this == &other) {
        return *this;
    }
    Alloc().deallocate(data_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
    
    return *this;
}

template < class T, class Alloc >
T& vector<T, Alloc>::operator[](size_t pos) {
    if(pos >= size_) {
        throw std::out_of_range("Vector::operator[]");
    }
    return data_[pos];
}

template < class T, class Alloc >
const T& vector<T, Alloc>::operator[](size_t pos) const {
    if(pos >= size_) {
        throw std::out_of_range("Vector::operator[]");
    }
    return data_[pos];
};

template < class T, class Alloc >
void vector<T, Alloc>::push_back(const T& value) {
    if(size_ + 1 > capacity_) {
        reserve(capacity_ * 2);
    }
    data_[size_++] = value;
}

template < class T, class Alloc >
void vector<T, Alloc>::pop_back() {
    size_--;
}

template < class T, class Alloc >
template < class... Args >
void vector<T, Alloc>::emplace_back(Args&&... args) {
    push_back(T(std::forward<Args>(args)...));
}

template < class T, class Alloc >
bool vector<T, Alloc>::empty() const noexcept {
    return size_ == 0;
};

template < class T, class Alloc >
size_t vector<T, Alloc>::size() const noexcept {
    return size_;
}

template < class T, class Alloc >
void vector<T, Alloc>::clear() noexcept {
    size_ = 0;
}

template < class T, class Alloc >
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() noexcept {
    return iterator(data_);
}

template < class T, class Alloc >
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() noexcept {
    return iterator(data_ + size_);
}

template < class T, class Alloc >
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() noexcept {
    return reverse_iterator(data_ + size_ - 1);
}

template < class T, class Alloc >
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() noexcept {
    return reverse_iterator(data_ - 1);
}

template < class T, class Alloc >
void vector<T, Alloc>::resize(size_t count) {
    if(count > size_) {
        reserve(count);
        for(size_t i = size_; i < count; i++) {
            data_[i] = T();
        }
    }
    size_ = count;
}

template < class T, class Alloc >
void vector<T, Alloc>::reserve(size_t count) {
    if(count > capacity_) {
        T* tmp = Alloc().allocate(count);
        for(int i = 0; i < size_; i++) {
            tmp[i] = std::move(data_[i]);
        }
        Alloc().deallocate(data_);
        capacity_ = count;
        data_ = tmp;
    }
}

template < class T, class Alloc >
size_t vector<T, Alloc>::capacity() const noexcept {
    return capacity_;
}

template < class T, class Alloc >
vector<T, Alloc>::~vector() {
    Alloc().deallocate(data_);
}
