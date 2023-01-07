/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vector.tpp                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 21:56:15 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/27 21:56:18 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include "ft_containers.hpp"
#include "iterator.tpp"
#include "type_traits.tpp"

#ifndef FT_CONTAINERS_VECTOR_TPP
# define FT_CONTAINERS_VECTOR_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

/*class Vectore base to resolve muti conflict*/
template <class T, class Allocator>
class Vector_base {


public:
    typedef Allocator                                                           allocator_type;

    Vector_base() : _ptr_start(0), _ptr_finish(0), _ptr_end(0) {}
    /*Solved allocator conflic*/
    Vector_base(const Allocator&) : _ptr_start(0), _ptr_finish(0), _ptr_end(0) {}

    Vector_base(size_t count, const Allocator&) : _ptr_start(0), _ptr_finish(0), _ptr_end(0){
        _ptr_start = (count == 0) ? 0 : static_cast<T*>(_alloc.allocate(count * sizeof(T)));
        _ptr_finish = _ptr_start;
        _ptr_end = _ptr_start + count;
    }

    ~Vector_base() {
        if ((_ptr_end - _ptr_start) != 0) {
            _alloc.deallocate(_ptr_start, (_ptr_end - _ptr_start));
        }
    }

    /*Returns the allocator associated with the container.*/
    allocator_type get_allocator() const { return allocator_type(); }

protected:
    T* _ptr_start;
    T* _ptr_finish;
    T* _ptr_end;
    allocator_type _alloc;

};
/*The elements are stored contiguously, which means that elements can be accessed not only through iterators, but also
 using offsets to regular pointers to elements. This means that a pointer to an element of a vector may be passed to
 any function that expects a pointer to an element of an array.
The storage of the vector is handled automatically, being expanded as needed. Vectors usually occupy more space than
 static arrays, because more memory is allocated to handle future growth. This way a vector does not need to reallocate
 each time an element is inserted, but only when the additional memory is exhausted. The total amount of allocated
 memory can be queried using capacity() function. Extra memory can be returned to the system via a call to
 shrink_to_fit(). (since C++11)
Reallocations are usually costly operations in terms of performance. The reserve() function can be used to eliminate
 reallocations if the number of elements is known beforehand.
The complexity (efficiency) of common operations on vectors is as follows:
Random access - constant O(1)
Insertion or removal of elements at the end - amortized constant O(1)
Insertion or removal of elements - linear in the distance to the end of the vector O(n)
std::vector (for T other than bool) meets the requirements of Container, AllocatorAwareContainer, SequenceContainer ,
 ContiguousContainer (since C++17) and ReversibleContainer.
Member functions of std::vector are constexpr: it is possible to create and use std::vector objects in the evaluation
 of a constant expression.
However, std::vector objects generally cannot be constexpr, because any dynamically allocated storage must be released
 in the same evaluation of constant expression.
(since C++20)
Template parameters
T	-	The type of the elements.
T must meet the requirements of CopyAssignable and CopyConstructible.	(until C++11)
The requirements that are imposed on the elements depend on the actual operations performed on the container. Generally,
 it is required that element type is a complete type and meets the requirements of Erasable, but many member functions
 impose stricter requirements.	(since C++11)
(until C++17)
The requirements that are imposed on the elements depend on the actual operations performed on the container. Generally,
 it is required that element type meets the requirements of Erasable, but many member functions impose stricter
 requirements. This container (but not its members) can be instantiated with an incomplete element type if the allocator
 satisfies the allocator completeness requirements.
Feature-test macro	Value	Std	Comment
__cpp_lib_incomplete_container_elements	201505L	(C++17)	Minimal incomplete type support
(since C++17)
Allocator	-	An allocator that is used to acquire/release memory and to construct/destroy the elements in that memory
 . The type must meet the requirements of Allocator. The behavior is undefined (until C++20)The program is ill-formed
 (since C++20) if Allocator::value_type is not the same as T.*/

template <class T, class Allocator = std::allocator<T> >
class vector : protected Vector_base<T, Allocator> {

private:
    typedef Vector_base<T, Allocator>                                           _Base;

public:
    typedef T                                                                   value_type;
    typedef typename _Base::allocator_type                                      allocator_type;
    typedef std::size_t                                                         size_type;
    typedef std::ptrdiff_t                                                      difference_type;
    typedef value_type&                                                         reference;
    typedef const value_type&                                                   const_reference;
    typedef typename _Base::allocator_type::pointer                             pointer;
    typedef typename _Base::allocator_type::const_pointer                       const_pointer;
    typedef ft::iterator_traits<value_type>                                     iterator;
    typedef ft::iterator_traits<const value_type>                               const_iterator;
    typedef ft::reverse_iterator<iterator>                                      reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                                const_reverse_iterator;


    /*Default constructor. Constructs an empty container with a default-constructed allocator.*/
    vector() : _Base(){}

    /*Constructs an empty container with the given allocator alloc*/
    explicit vector(const Allocator& alloc )  : _Base(alloc){}

    /*Constructs the container with count copies of elements with value value.*/
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
                    : _Base(count, alloc) {
        _Base::_ptr_finish = init<value_type *, size_type, T>(_Base::_ptr_start, count, value);
    }

    /* Constructs the container with the contents of the range [first, last).
     This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
     if InputIt is an integral type.*/
    template <class InputIt>
    vector(InputIt first, InputIt last,
           const allocator_type& alloc = allocator_type())
           : _Base(alloc){
        //typedef typename ft::is_integral<InputIt>::value   Integral;
        std::cout << ft::is_integral<InputIt>::value << std::endl;
        //ft::enable_if< ft::is_integral<InputIt>::value > tp;
        init_InputIt(first, last, ft::enable_if< !ft::is_integral<InputIt>::value >);
    };

//    vector(const vector& x) {
//        container_ = NULL;
//        alloc = x.alloc;
//        size_ = 0;
//        capacity_ = 0;
//        assign(x.begin(), x.end());
//    };

    vector& operator= (const vector& x) {
        if (&x == this)
            return *this;
        assign(x.begin(), x.end());
        return *this;
    };

    ~vector() { _Base::_alloc.destroy(_Base::_ptr_start); };

//private:
//
//    allocator_type _alloc;

    /*struct initialise by meta*/
    /*init vector */
    template <class Iter, class Size, class iT>
    inline Iter init(Iter ptr, Size count, const iT& value)
    {
        for (size_t i = 0; i < count; i++, ++ptr)
            *ptr = value;
        return ptr;
    }

    /*copy
    template <class InputIt>
    void init_rang(InputIt first, InputIt last, std::input_iterator_tag)
    {
        for ( ; first != last; ++first)
            push_back(*first);
    }

    // This function is only called by the constructor.
    template <class _ForwardIterator>
    void init_rang(_ForwardIterator __first,
                             _ForwardIterator __last, std::forward_iterator_tag)
    {
        size_type __n = 0;
        distance(__first, __last, __n);
        _M_start = _M_allocate(__n);
        _M_end_of_storage = _M_start + __n;
        _M_finish = uninitialized_copy(__first, __last, _M_start);
    }
*/
    /* is integrale type
     vector(static_cast<size_type>(first), static_cast<value_type>(last), a) if InputIt is an integral typ
     */
    template <class InputIt, typename type>
    void init_InputIt(InputIt first, InputIt last) {
        std::cout <<"false" << std::endl;
//        this->ptr_start = allocator_type::allocator(static_cast<size_type >(S_first));
//        this->ptr_finish = init(ptr_start, static_cast<size_type >(S_first), static_cast<value_type >(V_last));
//        this->ptr_end = ptr_start + static_cast<size_type >(S_first);
//
//        _M_range_initialize(__first, __last, __ITERATOR_CATEGORY(__first));
    }

    template <class Integral>
    void init_InputIt(Integral Size_first, Integral Value_last) {
        std::cout <<"true" << std::endl;
//        this->ptr_start = allocator_type::allocator(static_cast<size_type >(S_first));
//        this->ptr_finish = init(ptr_start, static_cast<size_type >(S_first), static_cast<value_type >(V_last));
//        this->ptr_end = ptr_start + static_cast<size_type >(S_first);
    }





    /*if is not integral type move value memory to the container vector*/



//    iterator begin()              { return iterator(container_); };
//    const_iterator begin() const  { return const_iterator(container_); };
//    iterator end()                { return iterator(container_ + size_); };
//    const_iterator end() const    { return const_iterator(container_ + size_); };
//
//    reverse_iterator rbegin()             { return reverse_iterator(end()); };
//    reverse_iterator rend()               { return reverse_iterator(begin()); };
//    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
//    const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); };
//
//    size_type size() const      { return size_; };
//    size_type max_size() const  { return alloc_.max_size(); };
//
//    void resize (size_type n, value_type val = value_type()) {
//        if (n > capacity_) {
//            if (capacity_ == 0)
//                reserve(n);
//            else {
//                if (size_ * 2 >= n)
//                    reserve(size_ * 2);
//                else
//                    reserve(n);
//            }
//        }
//        while (size_ < n) {
//            push_back(val);
//        }
//        while (size_ > n) {
//            pop_back();
//        };
//    }
//
//    size_type capacity() const  { return capacity_; };
//    bool      empty() const     { return size_ == 0; };
//
//    void reserve (size_type n) {
//        if (n > max_size())
//            throw std::length_error("vector::reserve");
//        if (n < capacity_)
//            return;
//
//        value_type *new_container = alloc_.allocate(n);
//
//        for (size_type i = 0; i < size_; i++) {
//            alloc_.construct(&new_container[i], container_[i]);
//            alloc_.destroy(&container_[i]);
//        }
//        alloc_.deallocate(container_, capacity_);
//        capacity_ = n;
//        container_ = new_container;
//    };
//
//    reference operator[] (size_type n) { return container_[n]; };
//    const_reference operator[] (size_type n) const { return container_[n]; };
//
//    reference at (size_type n) {
//        if (n >= size_) {
//            std::stringstream ss;
//            ss << "vector";
//            throw std::out_of_range(ss.str().c_str());
//        }
//        return container_[n];
//    };
//    const_reference at (size_type n) const {
//        if (n >= size_) {
//            std::stringstream ss;
//            ss << "vector";
//            throw std::out_of_range(ss.str().c_str());
//        }
//        return container_[n];
//    };
//
//    reference front() { return container_[0]; };
//    const_reference front() const { return container_[0]; };
//
//    reference back() { return container_[size_ - 1]; };
//    const_reference back() const { return container_[size_ - 1]; };
//
//    template <class InputIterator>
//    void assign (InputIterator first, InputIterator last,
//                 typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
//        clear();
//        InputIterator tmp = first;
//        difference_type n = 0;
//
//        while (tmp != last) {
//            n++;
//            tmp++;
//        }
//
//        reserve(n);
//        insert(begin(), first, last);
//    };
//
//    void assign (size_type n, const value_type& val) {
//        clear();
//        reserve(n);
//        insert(begin(), n, val);
//    };
//
//    void push_back (const value_type& val) {
//        if (size_ + 1 > capacity_) {
//            if (capacity_ == 0)
//                reserve(1);
//            else
//                reserve(capacity_ * 2);
//        }
//        alloc_.construct(&container_[size_], val);
//        size_++;
//    };
//
//    void pop_back() {
//        if (size_) {
//            alloc_.destroy(&container_[size_ - 1]);
//            size_--;
//        }
//    };
//
//    iterator insert (iterator position, const value_type& val) {
//        size_type index = position - begin();
//
//        if (size_ + 1 > capacity_) {
//            if (capacity_ == 0)
//                reserve(1);
//            else
//                reserve(capacity_ * 2);
//        }
//        size_++;
//        if (index < size_) {
//            for (size_type i = size_ - 1; i > index; i--) {
//                alloc_.construct(&container_[i], container_[i - 1]);
//                alloc_.destroy(&container_[i - 1]);
//            }
//        }
//        alloc_.construct(&container_[index], val);
//        return iterator(&container_[index]);
//    };
//
//    void insert (iterator position, size_type n, const value_type& val) {
//        size_type index = position - begin();
//
//        if (size_ + n > capacity_) {
//            if (capacity_ == 0)
//                reserve(n);
//            else {
//                if (size_ * 2 >= size_ + n)
//                    reserve(size_ * 2);
//                else
//                    reserve(size_ + n);
//            }
//        }
//
//        for (size_type i = n + size_ - 1; i > index + n - 1; i--) {
//            alloc_.construct(&container_[i], container_[i - n]);
//            alloc_.destroy(&container_[i - n]);
//        }
//        for (size_type i = index; i < index + n; i++) {
//            alloc_.construct(&container_[i], val);
//            size_++;
//        }
//    }
//
//    template <class InputIterator>
//    void insert (iterator position, InputIterator first, InputIterator last,
//                 typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
//        size_type offset = position - begin();
//        InputIterator tmp = first;
//        difference_type n = 0;
//
//        while (tmp != last) {
//            n++;
//            tmp++;
//        }
//
//        if (size_ + n > capacity_) {
//            if (capacity_ == 0)
//                reserve(n);
//            else {
//                if (size_ * 2 >= size_ + n)
//                    reserve(size_ * 2);
//                else
//                    reserve(size_ + n);
//            }
//        }
//
//        for (size_type i = n + size_ - 1; i > offset + n - 1; i--) {
//            alloc_.construct(&container_[i], container_[i - n]);
//            alloc_.destroy(&container_[i - n]);
//        }
//        for (size_type i = offset; i < offset + n; i++) {
//            alloc_.construct(&container_[i], *first);
//            first++;
//            size_++;
//        }
//    };
//
//    iterator erase (iterator position) {
//        size_type index = position - begin();
//
//        alloc_.destroy(&container_[index]);
//        size_--;
//        if (index < size_) {
//            for (size_type i = index; i < size_; i++) {
//                alloc_.construct(&container_[i], container_[i + 1]);
//                alloc_.destroy(&container_[i + 1]);
//            }
//        }
//        return iterator(&container_[index]);
//    };
//
//    iterator erase (iterator first, iterator last) {
//        size_type start = first - begin();
//        difference_type offset = last - first;
//
//        if (first == last)
//            return iterator(first);
//
//        for (iterator it = first; it != last; it++)
//            alloc_.destroy(&(*it));
//
//        size_ -= offset;
//        if (start < size_) {
//            for (size_type i = start; i < size_; i++) {
//                alloc_.construct(&container_[i], container_[i + offset]);
//                alloc_.destroy(&container_[i + offset]);
//            }
//        }
//        return iterator(&container_[start]);
//    };
//
//    void swap (vector& x) {
//        value_type *tmp = x.container_;
//        size_type tmp_size = x.size_;
//        size_type tmp_capacity = x.capacity_;
//
//        x.container_ = container_;
//        container_ = tmp;
//
//        x.size_ = size_;
//        size_ = tmp_size;
//
//        x.capacity_ = capacity_;
//        capacity_ = tmp_capacity;
//    };
//
//    void clear() { erase(begin(), end()); };
//
//    value_type      *container_;
//    allocator_type  alloc_;
//    size_type       size_;
//    size_type       capacity_;
//};
//
//template <class T>
//bool operator== (const vector<T>& lhs, const vector<T>& rhs) {
//    if (lhs.size() != rhs.size())
//        return false;
//    for (size_t i = 0; i < lhs.size(); i++) {
//        if (lhs[i] != rhs[i])
//            return false;
//    }
//    return true;
//
//
//};
//
//template <class T>
//bool operator!= (const vector<T>& lhs, const vector<T>& rhs) { return !(lhs == rhs); };
//
//template <class T>
//bool operator<  (const vector<T>& lhs, const vector<T>& rhs) {
//    typename vector<T>::const_iterator it1 = lhs.begin();
//    typename vector<T>::const_iterator it2 = rhs.begin();
//
//    while (it1 != lhs.end() && it2 != rhs.end()) {
//        if (*it1 < *it2)
//            return true;
//        else if (*it1 > *it2)
//            return false;
//        it1++;
//        it2++;
//    }
//    return (it2 != rhs.end());
};

template <class T>
bool operator<= (const vector<T>& lhs, const vector<T>& rhs) { return !(rhs < lhs); };

template <class T>
bool operator>  (const vector<T>& lhs, const vector<T>& rhs) { return rhs < lhs; };

template <class T>
bool operator>= (const vector<T>& lhs, const vector<T>& rhs) { return !(lhs < rhs); };

template <class T>
void swap (vector<T>& x, vector<T>& y) { x.swap(y); };

/*  Specializations
The standard library provides a specialization of std::vector for the type bool, which may be optimized for space
 efficiency.

 std::vector<bool>
 std::vector<bool> is a possibly space-efficient specialization of std::vector for the type bool.
The manner in which std::vector<bool> is made space efficient (as well as whether it is optimized at all) is
 implementation defined. One potential optimization involves coalescing vector elements such that each element
 occupies a single bit instead of sizeof(bool) bytes.
std::vector<bool> behaves similarly to std::vector, but in order to be space efficient, it:
Does not necessarily store its elements as a contiguous array.
Exposes class std::vector<bool>::reference as a method of accessing individual bits. In particular, objects of
 this class are returned by operator[] by value.
Does not use std::allocator_traits::construct to construct bit values.
Does not guarantee that different elements in the same container can be modified concurrently by different threads.*/

//    template <class Allocator>
//    class vector<bool, Allocator>{
//        typedef bool                                    value_type;
//        typedef Allocator                               Allocator_type;
//        typedef
//    };

__FT_CONTAINERS_END_NAMESPACE

#endif //VECTOR_TPP
