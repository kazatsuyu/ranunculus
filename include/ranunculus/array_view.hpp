#ifndef RANUNCULUS_ARRAY_VIEW_HPP
#define RANUNCULUS_ARRAY_VIEW_HPP

#include <stdexcept>
#include <type_traits>
#include <iterator>
#include "utility.hpp"
#include "types.hpp"
#include "concepts.hpp"
#include "compare.hpp"

namespace ranunculus { namespace array_view {

namespace v1 {

template<typename T>
class flex_view;

template<typename T, size_t len>
class fixed_view {
public:
    using self_type = fixed_view;
    using value_type = T;
    using const_value_type = std::add_const<T>;
    using pointer = T*;
    using const_pointer = const_value_type*;
    using reference = T&;
    using const_reference = const_value_type&;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type = size_t;
private:
    pointer ptr;

    template<typename U, size_t src_len>
    using convertible = enable_when<
        (std::is_same<U, value_type>{}
         || std::is_same<std::add_const_t<U>, value_type>{})
        && (src_len >= len)
    >;
public:
    fixed_view() = delete;
    constexpr fixed_view(const self_type&) noexcept = default;
    constexpr fixed_view(self_type&&) noexcept = default;
    explicit constexpr fixed_view(pointer p) noexcept: ptr{p} {}
    template<typename U, size_t src_len, convertible<U, src_len> = nullptr>
    constexpr fixed_view(const fixed_view<U, src_len>& view) noexcept: ptr(view.data()) {}
    template<typename U, convertible<U, len> = nullptr>
    explicit constexpr fixed_view(const flex_view<U>& view): ptr(view.data()) {
        RANUNCULUS_EXCEPT_WHEN(view.size() < len, std::out_of_range);
    }

    template<typename U, size_t src_len, convertible<U, src_len> = nullptr>
    constexpr fixed_view& operator=(const fixed_view<U, src_len>& src) noexcept {
        assign(src.data());
        return *this;
    }

    constexpr void assign(const self_type& src) noexcept { ptr = src.ptr; }
    template<typename U, size_t src_len, convertible<U, src_len> = nullptr>
    constexpr void assign(const fixed_view<U, src_len>& src) noexcept { ptr = src.ptr; }
    constexpr void assign(pointer p) noexcept { ptr = p; }

    constexpr reference at(size_type n) const {
        RANUNCULUS_EXCEPT_WHEN(n >= len, std::out_of_range);
        return ptr[n];
    }
    constexpr reference operator[](size_type n) const noexcept { return ptr[n]; }
    constexpr reference front() const noexcept { return ptr[0]; }
    constexpr reference back() const noexcept { return ptr[len-1]; }
    constexpr pointer data() const noexcept { return ptr; }

    constexpr iterator begin() const noexcept { return ptr; }
    constexpr const_iterator cbegin() const noexcept { return begin(); }
    constexpr iterator end() const noexcept { return ptr + len; }
    constexpr const_iterator cend() const noexcept { return end(); }
    constexpr reverse_iterator rbegin() const noexcept { return end(); }
    constexpr const_reverse_iterator crbegin() const noexcept { return cend(); }
    constexpr reverse_iterator rend() const noexcept { return begin(); }
    constexpr const_reverse_iterator crend() const noexcept { return cbegin(); }

    constexpr bool empty() const noexcept { return !size(); }
    constexpr size_type size() const noexcept { return len; }
    constexpr size_type max_size() const noexcept { return size(); }

    constexpr void fill(const_reference val) const noexcept(std::is_nothrow_copy_assignable<value_type>{}) {
        for(reference v : *this) {
            v = val;
        }
    }
    constexpr void swap(self_type& target) noexcept {
        pointer tmp = ptr;
        ptr = target.ptr;
        target.ptr = tmp;
    }

    template<size_t b = 0, size_t e = len, enable_when<(b <= e)> = nullptr>
    constexpr fixed_view<value_type, e-b> slice() const noexcept { return {ptr + b}; }
    template<size_t new_len = 1, enable_when<(new_len <= len)> = nullptr>
    constexpr fixed_view<value_type, new_len> head() const noexcept { return {ptr}; }
    template<size_t new_len = 1, enable_when<(new_len <= len)> = nullptr>
    constexpr fixed_view<value_type, new_len> tail() const noexcept { return {ptr + len - new_len}; }

    friend constexpr bool operator==(const self_type& lhs, const self_type& rhs) noexcept(noexcept(compare::eq(lhs[0] == rhs[0]))) {
        if(lhs.ptr == rhs.ptr) { return true; }
        iterator itr = rhs.begin();
        for(auto &&v : lhs) {
            if(!compare::eq(v, *itr)) return false;
            ++itr;
        }
        return true;
    }
    friend constexpr bool operator!=(const self_type& lhs, const self_type& rhs) noexcept(noexcept(lhs == rhs)) {
        return !(lhs == rhs);
    }
    friend constexpr bool operator<(const self_type& lhs, const self_type& rhs) noexcept(noexcept(compare::lt(lhs[0], rhs[0]))) {
        if(lhs.ptr == rhs.ptr) { return false; }
        iterator itr = rhs.begin();
        for(auto &&v : lhs) {
            if(compare::lt(v, *itr)) return true;
            else if(compare::lt(*itr, v)) return false;
            ++itr;
        }
        return false;
    }
    friend constexpr bool operator<=(const self_type& lhs, const self_type& rhs) noexcept(noexcept(lhs < rhs)) {
        return !(rhs < lhs);
    }
    friend constexpr bool operator>=(const self_type& lhs, const self_type& rhs) noexcept(noexcept(lhs < rhs)) {
        return !(lhs < rhs);
    }
    friend constexpr bool operator>(const self_type& lhs, const self_type& rhs) noexcept(noexcept(lhs < rhs)) {
        return rhs < lhs;
    }
    friend constexpr void swap(self_type& lhs, self_type& rhs) noexcept {
        lhs.swap(rhs);
    }
};

template<typename T>
class flex_view {
public:
    using self_type = flex_view;
    using value_type = T;
    using const_value_type = std::add_const<T>;
    using pointer = T*;
    using const_pointer = const_value_type*;
    using reference = T&;
    using const_reference = const_value_type&;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type = size_t;
private:
    pointer begin_;
    pointer end_;
    template<typename U>
    using convertible = enable_when<
        (std::is_same<U, value_type>{} || std::is_same<std::add_const_t<U>, value_type>{})
    >;
public:
    flex_view() = delete;
    constexpr flex_view(const flex_view&) noexcept = default;
    constexpr flex_view(flex_view&&) noexcept = default;
    constexpr flex_view(pointer b, pointer e) noexcept: begin_{b}, end_{e} {}
    constexpr flex_view(pointer b, size_t len) noexcept: begin_{b}, end_{b+len} {}
    template<typename U, convertible<U> = nullptr>
    constexpr flex_view(const flex_view<U>& view) noexcept: flex_view(view.begin(), view.end()) {}
    template<typename U, size_t len, convertible<U> = nullptr>
    explicit constexpr flex_view(U (&a)[len]) noexcept: flex_view(a, len) {}
    template<typename U, size_t len, convertible<U> = nullptr>
    explicit constexpr flex_view(const fixed_view<U, len>& v) : flex_view(v.data(), len) {}

    constexpr flex_view& operator=(const flex_view&) noexcept = default;
    constexpr flex_view& operator=(flex_view&&) noexcept = default;
    template<typename U, convertible<U> = nullptr>
    constexpr flex_view& operator=(const flex_view<U>& src) noexcept { assign(src.begin(), src.end()); return *this; }

    constexpr void assign(const self_type& src) noexcept { assign(src.begin(), src.end()); }
    constexpr void assign(pointer b, pointer e) noexcept { begin_ = b; end_ = e; }
    constexpr void assign(pointer b, size_t len) noexcept { assign(b, b + len); }
    template<typename U, convertible<U> = nullptr>
    constexpr void assign(const flex_view<U>& src) noexcept { assign(src.begin(), src.end()); }
    template<typename U, size_t len, convertible<U> = nullptr>
    constexpr void assign(U (&a)[len]) noexcept { assign(a, len); }
    template<typename U, size_t len, convertible<U> = nullptr>
    constexpr void assign(const fixed_view<U, len>& src) noexcept { assign(src.data(), len); }

    constexpr reference at(size_type n) const {
        RANUNCULUS_EXCEPT_WHEN(n >= size(), std::out_of_range);
        return begin_[n];
    }
    constexpr reference operator[](size_type n) const noexcept { return begin_[n]; }
    constexpr reference front() const noexcept { return begin_[0]; }
    constexpr reference back() const noexcept { return *(end_ - 1); }
    constexpr pointer data() const noexcept { return begin_; }

    constexpr iterator begin() const noexcept { return begin_; }
    constexpr const_iterator cbegin() const noexcept { return begin_; }
    constexpr iterator end() const noexcept { return end_; }
    constexpr const_iterator cend() const noexcept { return end_; }
    constexpr reverse_iterator rbegin() const noexcept { return end_; }
    constexpr const_reverse_iterator crbegin() const noexcept { return end_; }
    constexpr reverse_iterator rend() const noexcept { return begin_; }
    constexpr const_reverse_iterator crend() const noexcept { return begin_; }

    constexpr bool empty() const noexcept { return !size(); }
    constexpr size_type size() const noexcept { return end_ - begin_; }
    constexpr size_type max_size() const noexcept { return size(); }

    constexpr void fill(const_reference val) const noexcept(std::is_nothrow_copy_assignable<value_type>{}) {
        for(reference v : *this) {
            v = val;
        }
    }
    constexpr void swap(self_type& target) noexcept {
        self_type tmp = *this;
        assign(target);
        target.assign(tmp);
    }
    constexpr self_type slice(size_type b = 0) const noexcept { return slice(b, size()); }
    constexpr self_type slice(size_type b, size_type e) const noexcept {
        pointer b_ = std::max RANUNCULUS_MACRO_WORKAROUND (begin_, std::min RANUNCULUS_MACRO_WORKAROUND (begin_ + b, end_));
        pointer e_ = std::max RANUNCULUS_MACRO_WORKAROUND (b_,  std::min RANUNCULUS_MACRO_WORKAROUND (begin_ + e, end_));
        return {b_, e_};
    }
    constexpr self_type head(size_type len = 1) const noexcept { return slice(0, len); }
    constexpr self_type tail(size_type len = 1) const noexcept { return slice(size()-std::min RANUNCULUS_MACRO_WORKAROUND (len, size())); }

    constexpr void shrink(size_type new_size) noexcept {
        end_ = begin_ + std::min RANUNCULUS_MACRO_WORKAROUND (size(), new_size);
    }

    friend constexpr bool operator==(const self_type& lhs, const self_type& rhs) noexcept(noexcept(compare::eq(lhs[0] == rhs[0]))) {
        if(lhs.ptr == rhs.ptr) { return true; }
        iterator itr = rhs.begin();
        for(auto &&v : lhs) {
            if(!compare::eq(v, *itr)) return false;
            ++itr;
        }
        return true;
    }
    friend constexpr bool operator!=(const self_type& lhs, const self_type& rhs) noexcept(noexcept(lhs == rhs)) {
        return !(lhs == rhs);
    }
    friend constexpr bool operator<(const self_type& lhs, const self_type& rhs) noexcept(noexcept(compare::lt(lhs[0], rhs[0]))) {
        if(lhs.ptr == rhs.ptr) { return false; }
        iterator itr = rhs.begin();
        for(auto &&v : lhs) {
            if(compare::lt(v, *itr)) return true;
            else if(compare::lt(*itr, v)) return false;
            ++itr;
        }
        return false;
    }
    friend constexpr bool operator<=(const self_type& lhs, const self_type& rhs) noexcept(noexcept(lhs < rhs)) {
        return !(rhs < lhs);
    }
    friend constexpr bool operator>=(const self_type& lhs, const self_type& rhs) noexcept(noexcept(lhs < rhs)) {
        return !(lhs < rhs);
    }
    friend constexpr bool operator>(const self_type& lhs, const self_type& rhs) noexcept(noexcept(lhs < rhs)) {
        return rhs < lhs;
    }
    friend constexpr void swap(self_type& lhs, self_type& rhs) noexcept {
        lhs.swap(rhs);
    }
};

} // namespace v1

using namespace v1;

}} // namespace ranunculus::array_view

#endif
