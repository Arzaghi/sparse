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
            return iter != sparse_.values_.end() ? iter->second : sparse_.defaultValue();
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

    class Iterator {
    public:

        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;        

        Iterator(Sparse<T>& sparse, size_t index) :
            sparse_{ sparse }, index_{ index }
        {}

        Iterator& operator=(const Iterator& rawIterator) {
            sparse_ = Sparse(rawIterator.sparse_);
            index_ = rawIterator.index_;
            return *this;
        }

        bool operator==(const Iterator& rawIterator) const { return (index_ == rawIterator.index_ && sparse_.values_.begin() == rawIterator.sparse_.values_.begin()); }
        bool operator!=(const Iterator& rawIterator) const { return !((*this) == rawIterator); }

        Iterator& operator+=(const ptrdiff_t& movement) { index_ += movement; return (*this); }
        Iterator& operator-=(const ptrdiff_t& movement) { index_ -= movement; return (*this); }
        Iterator& operator++() { ++index_; return (*this); }
        Iterator& operator--() { --index_; return (*this); }
        Iterator  operator++(int) { auto temp(*this); ++index_; return temp; }
        Iterator  operator--(int) { auto temp(*this); --index_; return temp; }
        Iterator  operator+(const ptrdiff_t& movement) { auto oldPtr = index_; index_ += movement; auto temp(*this); index_ = oldPtr; return temp; }
        Iterator  operator-(const ptrdiff_t& movement) { auto oldPtr = index_; index_ -= movement; auto temp(*this); index_ = oldPtr; return temp; }

        //difference_type  operator-(const Iterator& rawIterator) { return index_ - rawIterator.index_; }

        reference operator*() { return sparse_[index_]; }
        reference* operator->() { return &sparse_[index_]; }

        inline bool operator<(const Iterator& rawIterator) const { return index_ < rawIterator.index_; }
        inline bool operator<=(const Iterator& rawIterator) const { return index_ <= rawIterator.index_; }        
        inline bool operator>(const Iterator& rawIterator) const { return index_ > rawIterator.index_; }        
        inline bool operator>=(const Iterator& rawIterator) const { return index_ >= rawIterator.index_; }

    protected:

        Sparse<T>& sparse_;
        size_t      index_;
    };

    class Const_Iterator  {
    public:

        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;

        Const_Iterator(const Sparse<T>& sparse, size_t index) :
            sparse_{ sparse }, index_{ index }
        {}

        Const_Iterator& operator=(const Const_Iterator& rawIterator) = default;        

        bool operator==(const Const_Iterator& rawIterator) const { return (index_ == rawIterator.index_ && sparse_.values_.begin() == rawIterator.sparse_.values_.begin()); }
        bool operator!=(const Const_Iterator& rawIterator) const { return !((*this) == rawIterator); }

        Const_Iterator& operator+=(const ptrdiff_t& movement) { index_ += movement; return (*this); }
        Const_Iterator& operator-=(const ptrdiff_t& movement) { index_ -= movement; return (*this); }
        Const_Iterator& operator++() { ++index_; return (*this); }
        Const_Iterator& operator--() { --index_; return (*this); }
        Const_Iterator  operator++(int) { auto temp(*this); ++index_; return temp; }
        Const_Iterator  operator--(int) { auto temp(*this); --index_; return temp; }
        Const_Iterator  operator+(const ptrdiff_t& movement) { auto oldPtr = index_; index_ += movement; auto temp(*this); index_ = oldPtr; return temp; }
        Const_Iterator  operator-(const ptrdiff_t& movement) { auto oldPtr = index_; index_ -= movement; auto temp(*this); index_ = oldPtr; return temp; }

        difference_type       operator-(const Const_Iterator& rawIterator) { return index_ - rawIterator.index_; }
                
        const T& operator*() const { return sparse_[index_]; }
        const T* operator->() const { return &sparse_[index_]; }

    protected:

        const Sparse<T>& sparse_;
        size_t      index_;
    };

    class Reverse_Iterator : public Iterator{
    public:
        Reverse_Iterator(Sparse<T>& sparse, size_t index) : Iterator(sparse, index) {}
        ~Reverse_Iterator() {}
        
        Reverse_Iterator& operator=(const Reverse_Iterator& rawIterator) = default;        
        
        Reverse_Iterator& operator+=(const ptrdiff_t& movement) { Iterator::index_ -= movement; return (*this); }
        Reverse_Iterator& operator-=(const ptrdiff_t& movement) { Iterator::index_ += movement; return (*this); }
        Reverse_Iterator& operator++() { --Iterator::index_; return (*this); }
        Reverse_Iterator& operator--() { ++Iterator::index_; return (*this); }
        Reverse_Iterator  operator++(int) { auto temp(*this); --Iterator::index_; return temp; }
        Reverse_Iterator  operator--(int) { auto temp(*this); ++Iterator::index_; return temp; }
        Reverse_Iterator  operator+(const ptrdiff_t& movement) { auto oldPtr = Iterator::index_; Iterator::index_ -= movement; auto temp(*this); Iterator::index_ = oldPtr; return temp; }
        Reverse_Iterator  operator-(const ptrdiff_t& movement) { auto oldPtr = Iterator::index_; Iterator::index_ += movement; auto temp(*this); Iterator::index_ = oldPtr; return temp; }
    };

    class Const_Reverse_Iterator : public Const_Iterator {
    public:
        Const_Reverse_Iterator(const Sparse<T>& sparse, size_t index) : Const_Iterator(sparse, index) {}
        ~Const_Reverse_Iterator() {}

        Const_Reverse_Iterator& operator=(const Const_Reverse_Iterator& rawIterator) = default;

        Const_Reverse_Iterator& operator+=(const ptrdiff_t& movement) { Const_Iterator::index_ -= movement; return (*this); }
        Const_Reverse_Iterator& operator-=(const ptrdiff_t& movement) { Const_Iterator::index_ += movement; return (*this); }
        Const_Reverse_Iterator& operator++() { --Const_Iterator::index_; return (*this); }
        Const_Reverse_Iterator& operator--() { ++Const_Iterator::index_; return (*this); }
        Const_Reverse_Iterator  operator++(int) { auto temp(*this); --Const_Iterator::index_; return temp; }
        Const_Reverse_Iterator  operator--(int) { auto temp(*this); ++Const_Iterator::index_; return temp; }
        Const_Reverse_Iterator  operator+(const ptrdiff_t& movement) { auto oldPtr = Const_Iterator::index_; Const_Iterator::index_ -= movement; auto temp(*this); Const_Iterator::index_ = oldPtr; return temp; }
        Const_Reverse_Iterator  operator-(const ptrdiff_t& movement) { auto oldPtr = Const_Iterator::index_; Const_Iterator::index_ += movement; auto temp(*this); Const_Iterator::index_ = oldPtr; return temp; }
    };

    using iterator               =   Iterator;
    using const_iterator         =   Const_Iterator;
    using reverse_iterator       =   Reverse_Iterator;
    using const_reverse_iterator =   Const_Reverse_Iterator;

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
        if (iter != values_.end()) return iter->second; else return defaultValue();
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

    inline iterator                 begin()             { return iterator((*this), 0); }    
    inline iterator                 end()               { return iterator(*this, count_); }
    inline const_iterator           begin()     const   { return cbegin(); }
    inline const_iterator           end()       const   { return cend(); }
    inline const_iterator           cbegin()    const   { return const_iterator((*this), 0); }
    inline const_iterator           cend()      const   { return const_iterator(*this, count_); }

    inline reverse_iterator         rbegin()            { return reverse_iterator(*this, count_ - 1); }
    inline reverse_iterator         rend()              { return reverse_iterator(*this, -1); }
    inline const_reverse_iterator   rbegin()    const   { return crbegin(); }
    inline const_reverse_iterator   rend()      const   { return crend(); }
    inline const_reverse_iterator   crbegin()   const   { return const_reverse_iterator(*this, count_ - 1); }
    inline const_reverse_iterator   crend()     const   { return const_reverse_iterator(*this, count_ - 1); }

    inline const T& defaultValue() const { return sparse_default_value_; }    

private:
    std::map<size_t, T> values_;
    size_t              count_;
    T                   sparse_default_value_;
};


template <typename T> inline static bool operator<(const typename Sparse<T>::iterator& lhs, const typename Sparse<T>::iterator& rhs) { return true; }
template <typename T> inline static bool operator<(const typename Sparse<T>::const_iterator& lhs, const typename Sparse<T>::const_iterator& rhs) { return true; }