#pragma once
#include <map>

template <typename T> class Sparse {
public:
    class reference {
    public:
        reference(Sparse<T>& sparse, size_t index) :
            sparse_{ sparse },
            index_{ index }            
        {}

        operator const T& () const{
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

    template<typename U = T>
    Sparse(std::size_t count, U&& sparse_value = T()) :
        count_{ count },
        sparse_default_value_{ std::forward<U>(sparse_value) }
    {}

    Sparse<T>::reference operator[](size_t index) {
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

    size_t  size()  const       { return count_; };
    void    clear() noexcept    { values_.clear(); }



private:
    std::map<size_t, T> values_;
    size_t              count_;
    const T             sparse_default_value_;
};
