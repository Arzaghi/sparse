#pragma once
#include <map>

template <typename T> class Sparse {
public:
    class reference {
    public:
        reference(Sparse<T>& sparse, size_t index) :
            sparse_{ sparse }, index_{ index }
        {}

        operator const T& () const {
            auto iter = sparse_.values_.find(index_);
            if (iter != sparse_.values_.end()) return iter->second; else return sparse_.sparse_default_value_;
        }

        template<typename U>
        reference& operator=(U&& val) {
            auto x = sparse_.values_.emplace(index_, std::forward<U>(val));
            if (!x.second) x.first->second = std::forward<U>(val);
            return *this;
        }

    private:
        Sparse<T>& sparse_;
        size_t      index_;
    };
    
    class const_iterator {
    public:
        const_iterator(const Sparse<T>& sparse_, size_t index) :
            sparse_{sparse_}, index_{index}
        {}

        const T& operator*() const { return sparse_[index_]; }
        const T* operator->() const { return &sparse_[index_]; }
        bool operator==(const const_iterator& rhs) { return &sparse_ == &rhs.sparse_ && index_ == rhs.index_; }
        bool operator!=(const const_iterator& rhs) { return !(*this == rhs); }

        Sparse<T>::const_iterator operator++() { ++index_; return *this; }
        Sparse<T>::const_iterator operator--() { --index_; return *this; }
        Sparse<T>::const_iterator operator++(int) { index_++; return *this; }
        Sparse<T>::const_iterator operator--(int) { index_--; return *this; }
        const_iterator operator+(size_t idx) const { return const_iterator(sparse_, index_ + idx); }
        const_iterator operator-(size_t idx) const { return const_iterator(sparse_, index_ - idx); }
        const_iterator operator+=(size_t idx) { index_ += idx; return *this; }
        const_iterator operator-=(size_t idx) { index_ -= idx; return *this; }

    private:
        const Sparse<T>& sparse_;
        size_t      index_;
    };

    class const_reverse_iterator {
    public:
        const_reverse_iterator(const Sparse<T>& sparse_, size_t index) :
            sparse_{ sparse_ }, index_{ index }
        {}

        const T& operator*() const { return sparse_[index_]; }
        const T* operator->() const { return &sparse_[index_]; }
        bool operator==(const const_reverse_iterator& rhs) { return &sparse_ == &rhs.sparse_ && index_ == rhs.index_; }
        bool operator!=(const const_reverse_iterator& rhs) { return !(*this == rhs); }

        Sparse<T>::const_iterator operator++() { --index_; return *this; }
        Sparse<T>::const_iterator operator--() { ++index_; return *this; }
        Sparse<T>::const_iterator operator++(int) { index_--; return *this; }
        Sparse<T>::const_iterator operator--(int) { index_++; return *this; }
        const_reverse_iterator operator+(size_t idx) const { return const_reverse_iterator(sparse_, index_ - idx); }
        const_reverse_iterator operator-(size_t idx) const { return const_reverse_iterator(sparse_, index_ + idx); }
        const_reverse_iterator operator+=(size_t idx) { index_ -= idx; return *this; }
        const_reverse_iterator operator-=(size_t idx) { index_ += idx; return *this; }

    private:
        const Sparse<T>& sparse_;
        size_t      index_;
    };

    template<typename... Args>
    Sparse(size_t count, Args&&... sparse_value):
        count_{ count }, 
        sparse_default_value_{ std::forward<Args>(sparse_value)... }
    {}

    inline Sparse<T>::reference operator[](size_t index) {
#if _ITERATOR_DEBUG_LEVEL>0
        if (index >= count_) throw std::out_of_range("index out of range");
#endif               
        return reference(*this, index);
    }

    const T& operator[](size_t index) const {
        #if _ITERATOR_DEBUG_LEVEL>0
        if (index >= count_) throw std::out_of_range("index out of range");
        #endif               
        auto iter = values_.find(index);
        if (iter != values_.end()) return iter->second; else return sparse_default_value_;
    }

    inline size_t size() const { return count_; };
    inline size_t count() const { return values_.size(); }
    inline void clear() noexcept { values_.clear(); }

    Sparse<T>::reference at(size_t index) {
        if (index >= size()) throw std::out_of_range("index out of range");
        return (*this)[index];
    }
    const T& at(size_t index) const {
        if (index >= size()) throw std::out_of_range("index out of range");
        return (*this)[index];
    }

    inline std::map<size_t, T>& map() { return values_; }
    inline bool empty() { return values_.empty(); }
    inline const_iterator begin() const { return const_iterator(*this, 0); }
    inline const_iterator end() const { return const_iterator(*this, count_); }
    inline const_iterator cbegin() const { return begin(); }
    inline const_iterator cend() const { return end(); }
    inline const_reverse_iterator rbegin() const { return const_reverse_iterator(*this, count_ - 1); }
    inline const_reverse_iterator rend() const { return const_reverse_iterator(*this, -1); }
    inline const_reverse_iterator crbegin() const { return rbegin(); }
    inline const_reverse_iterator crend() const { return rend(); }

private:
    std::map<size_t, T> values_;
    size_t              count_;
    const T             sparse_default_value_;
};
