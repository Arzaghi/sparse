#pragma once
#include <map>
#include <stdexcept>

template <typename T> class Sparse {
public:
    class proxy {
    public:
        proxy(Sparse<T>& sparse, size_t index) :
            sparse_{ sparse }, index_{ index }
        {}

        operator const T& () const {
            auto iter = sparse_.values_.find(index_);
            return iter != sparse_.values_.end() ? iter->second : sparse_.defaultValue();
        }

        template<typename U>
        proxy& operator=(U&& val) {
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
        using reference = proxy;

        Iterator() : sparse_{ nullptr }, index_{ 0 } {}
        Iterator(Sparse<T>& sparse, size_t index) : sparse_{ &sparse }, index_{ index } {}             

        Iterator& operator=(const Iterator& iter) { index_ = iter.index_; return *this; }
        Iterator& operator=(const difference_type& index) { index_ = index; return *this; }

        operator const difference_type& () const { return index_; }
        bool operator==(const Iterator& iter) const { return (index_ == iter.index_ && sparse_->values_.begin() == iter.sparse_->values_.begin()); }
        bool operator==(const difference_type& index) const { return (index_ == index); }
        bool operator!=(const Iterator& iter) const { return !((*this) == iter); }
        bool operator!=(const difference_type& index) const { return (index_ != index); }

        Iterator& operator+=(const difference_type& movement) { index_ += movement; return (*this); }
        Iterator& operator-=(const difference_type& movement) { index_ -= movement; return (*this); }

        Iterator& operator++() { ++index_; return (*this); }
        Iterator  operator++(int) { auto temp(*this); ++index_; return temp; }

        Iterator& operator--() { --index_; return (*this); }        
        Iterator  operator--(int) { auto temp(*this); --index_; return temp; }        

        Iterator  operator-(const Iterator& iter) const { return  Iterator(*sparse_, index_ - iter.index_); }
        Iterator  operator-(const difference_type& index) const { return Iterator(*sparse_, index_ - index); }
        Iterator  operator-(const int& index) const { return Iterator(*sparse_, index_ - index); }

        Iterator  operator+(const Iterator& iter) const { return  Iterator(*sparse_, index_ + iter.index_); }
        Iterator  operator+(const difference_type& index) const { return Iterator(*sparse_, index_ + index); }
        Iterator  operator+(const int& index) const { return Iterator(*sparse_, index_ + index); }

        proxy operator*() { return ((*sparse_)[index_]); }
        proxy* operator->() { return &((*sparse_)[index_]); }

        inline bool operator<(const Iterator& iter) const { return index_ < iter.index_; }
        inline bool operator<=(const Iterator& iter) const { return index_ <= iter.index_; }        
        inline bool operator>(const Iterator& iter) const { return index_ > iter.index_; }        
        inline bool operator>=(const Iterator& iter) const { return index_ >= iter.index_; }

    protected:
        Sparse<T>* sparse_;
        size_t     index_;
    };

    class Const_Iterator  {
    public:

        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;
        using reference = proxy;

        Const_Iterator(const Sparse<T>& sparse, size_t index) : sparse_{ &sparse }, index_{ index } {}
        Const_Iterator() : sparse_{ nullptr }, index_{ 0 } {}

        Const_Iterator& operator=(const Const_Iterator& iter)    { index_ = iter.index_; return *this; }
        Const_Iterator& operator=(const difference_type& index)         { index_ = index; return *this; }

        operator const difference_type& () const { return index_; }        
        bool operator==(const Const_Iterator& iter)  const { return (index_ == iter.index_ && sparse_->values_.begin() == iter.sparse_->values_.begin()); }
        bool operator==(const difference_type& index)       const { return (index_ == index); }
        bool operator!=(const Const_Iterator& iter)  const { return !((*this) == iter); }
        bool operator!=(const difference_type& index)       const { return (index_ != index); }


        Const_Iterator& operator+=(const difference_type& movement) { index_ += movement; return (*this); }
        Const_Iterator& operator-=(const difference_type& movement) { index_ -= movement; return (*this); }
        
        Const_Iterator& operator++()    { ++index_; return (*this); }
        Const_Iterator  operator++(int) { auto temp(*this); ++index_; return temp; }
        
        Const_Iterator& operator--()    { --index_; return (*this); }        
        Const_Iterator  operator--(int) { auto temp(*this); --index_; return temp; }        

        Const_Iterator  operator-(const Const_Iterator& iter) const { return  Const_Iterator(*sparse_, index_ - iter.index_); }
        Const_Iterator  operator-(const difference_type& index) const { return Const_Iterator(*sparse_, index_ - index); }
        Const_Iterator  operator-(const int& index) const { return Const_Iterator(*sparse_, index_ - index); }

        Const_Iterator  operator+(const Const_Iterator& iter) const { return  Const_Iterator(*sparse_, index_ + iter.index_); }
        Const_Iterator  operator+(const difference_type& index) const { return Const_Iterator(*sparse_, index_ + index); }
        Const_Iterator  operator+(const int& index) const { return Const_Iterator(*sparse_, index_ + index); }
                
        const T& operator*() const { return (*sparse_)[index_]; }
        const T* operator->() const { return &((*sparse_)[index_]); }

    protected:

        const Sparse<T>* sparse_;
        size_t      index_;
    };

    class Reverse_Iterator : public Iterator{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;
        using reference = proxy;

        Reverse_Iterator() : Iterator() {}
        Reverse_Iterator(Sparse<T>& sparse, size_t index) : Iterator(sparse, index) {}                
                
        operator const difference_type& ()               const { return Iterator::index_; }
        bool operator==(const Reverse_Iterator& iter)    const { return (Iterator::index_ == iter.index_ && Iterator::sparse_->values_.begin() == iter.sparse_->values_.begin()); }
        bool operator==(const difference_type& index)    const { return (Iterator::index_ == index); }
        bool operator!=(const Reverse_Iterator& iter)    const { return !((*this) == iter); }
        bool operator!=(const difference_type& index)    const { return (Iterator::index_ != index); }

        Reverse_Iterator& operator=(const Reverse_Iterator& iter) { Iterator::index_ = iter.index_; return *this; }
        Reverse_Iterator& operator=(const difference_type& index) { Iterator::index_ = index; return *this; }        
        
        Reverse_Iterator& operator+=(const difference_type& movement) { Iterator::index_ -= movement; return (*this); }
        Reverse_Iterator& operator-=(const difference_type& movement) { Iterator::index_ += movement; return (*this); }
        
        Reverse_Iterator& operator++() { --Iterator::index_; return (*this); }
        Reverse_Iterator  operator++(int) { auto temp(*this); --Iterator::index_; return temp; }

        Reverse_Iterator& operator--() { ++Iterator::index_; return (*this); }        
        Reverse_Iterator  operator--(int) { auto temp(*this); ++Iterator::index_; return temp; }   

        Reverse_Iterator  operator-(const Reverse_Iterator& iter)       const   { return Reverse_Iterator(*Iterator::sparse_, Iterator::index_ - iter.index_); }
        Reverse_Iterator  operator-(const difference_type& index)       const   { return Reverse_Iterator(*Iterator::sparse_, Iterator::index_ - index); }
        Reverse_Iterator  operator-(const int& index)                   const   { return Reverse_Iterator(*Iterator::sparse_, Iterator::index_ - index); }        
        Reverse_Iterator  operator+(const Reverse_Iterator& iter)       const   { return Reverse_Iterator(*Iterator::sparse_, Iterator::index_ + iter.index_); }
        Reverse_Iterator  operator+(const difference_type& index)       const   { return Reverse_Iterator(*Iterator::sparse_, Iterator::index_ + index); }
        Reverse_Iterator  operator+(const int& index)                   const   { return Reverse_Iterator(*Iterator::sparse_, Iterator::index_ + index); }
    };

    class Const_Reverse_Iterator : public Const_Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = T*;
        using reference = proxy;

        Const_Reverse_Iterator() : Const_Iterator() {}
        Const_Reverse_Iterator(const Sparse<T>& sparse, size_t index) :  Const_Iterator(sparse, index){}        
        
        operator const difference_type& () const { return Const_Iterator::index_; }
        bool operator==(const Const_Reverse_Iterator& iter)  const { return (Const_Iterator::index_ == iter.index_ && Const_Iterator::sparse_->values_.begin() == iter.sparse_->values_.begin()); }
        bool operator==(const difference_type& index)       const { return (Const_Iterator::index_ == index); }
        bool operator!=(const Const_Reverse_Iterator& iter)  const { return !((*this) == iter); }
        bool operator!=(const difference_type& index)       const { return (Const_Iterator::index_ != index); }

        Const_Reverse_Iterator& operator=(const Const_Reverse_Iterator& iter) { Const_Iterator::index_ = iter.index_; return *this; }
        Const_Reverse_Iterator& operator=(const difference_type& index) { Const_Iterator::index_ = index; return *this; }

        Const_Reverse_Iterator& operator+=(const ptrdiff_t& movement) { Const_Iterator::index_ -= movement; return (*this); }
        Const_Reverse_Iterator& operator-=(const ptrdiff_t& movement) { Const_Iterator::index_ += movement; return (*this); }
        
        Const_Reverse_Iterator& operator++() { --Const_Iterator::index_; return (*this); }
        Const_Reverse_Iterator  operator++(int) { auto temp(*this); --Const_Iterator::index_; return temp; }

        Const_Reverse_Iterator& operator--() { ++Const_Iterator::index_; return (*this); }        
        Const_Reverse_Iterator  operator--(int) { auto temp(*this); ++Const_Iterator::index_; return temp; }

        Const_Reverse_Iterator  operator-(const Const_Reverse_Iterator& iter) const { return  Const_Reverse_Iterator(*Const_Iterator::sparse_, Const_Iterator::index_ - iter.index_); }
        Const_Reverse_Iterator  operator-(const difference_type& index) const { return Const_Reverse_Iterator(*Const_Iterator::sparse_, Const_Iterator::index_ - index); }
        Const_Reverse_Iterator  operator-(const int& index) const { return Const_Reverse_Iterator(*Const_Iterator::sparse_, Const_Iterator::index_ - index); }

        Const_Reverse_Iterator  operator+(const Const_Reverse_Iterator& iter) const { return  Const_Reverse_Iterator(*Const_Iterator::sparse_, Const_Iterator::index_ + iter.index_); }
        Const_Reverse_Iterator  operator+(const difference_type& index) const { return Const_Reverse_Iterator(*Const_Iterator::sparse_, Const_Iterator::index_ + index); }
        Const_Reverse_Iterator  operator+(const int& index) const { return Const_Reverse_Iterator(*Const_Iterator::sparse_, Const_Iterator::index_ + index); }
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

    inline Sparse<T>::proxy operator[](size_t index) {
#if _ITERATOR_DEBUG_LEVEL>0
        if (index >= count_) throw std::out_of_range("index out of range");
#endif               
        return proxy(*this, index);
    }

    const T& operator[](size_t index) const {
        #if _ITERATOR_DEBUG_LEVEL>0
        if (index >= count_) throw std::out_of_range("index out of range");
        #endif               
        auto iter = values_.find(index);        
        return (iter != values_.end() ? iter->second : defaultValue());
    }

    inline size_t size() const { return count_; };
    inline size_t count() const { return values_.size(); }
    inline void clear() noexcept { values_.clear(); }

    Sparse<T>::proxy at(size_t index) {
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
    inline const_iterator           cbegin()    const   { return const_iterator(*this, 0); }
    inline const_iterator           cend()      const   { return const_iterator(*this, count_); }

    inline reverse_iterator         rbegin()            { return reverse_iterator(*this, count_ - 1); }
    inline reverse_iterator         rend()              { return reverse_iterator(*this, -1); }
    inline const_reverse_iterator   rbegin()    const   { return crbegin(); }
    inline const_reverse_iterator   rend()      const   { return crend(); }
    inline const_reverse_iterator   crbegin()   const   { return const_reverse_iterator(*this, count_ - 1); }
    inline const_reverse_iterator   crend()     const   { return const_reverse_iterator(*this, -1); }

    inline const T& defaultValue() const { return sparse_default_value_; }    

private:
    std::map<size_t, T> values_;
    size_t              count_;
    T                   sparse_default_value_;
};
