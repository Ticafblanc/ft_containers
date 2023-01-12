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
#include "algorithm.tpp"


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

/*
*=============================================================
*|                     Member Type                           |
*=============================================================
*/

public:
    typedef T                                                                   value_type;
    typedef typename _Base::allocator_type                                      allocator_type;
    typedef std::size_t                                                         size_type;
    typedef std::ptrdiff_t                                                      difference_type;
    typedef value_type&                                                         reference;
    typedef const value_type&                                                   const_reference;
    typedef typename _Base::allocator_type::pointer                             pointer;
    typedef typename _Base::allocator_type::const_pointer                       const_pointer;
    typedef value_type*                                                         iterator;
    typedef const value_type*                                                   const_iterator;
    typedef ft::reverse_iterator<iterator>                                      reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                                const_reverse_iterator;

/*
*=============================================================
*|                     Member Fonction                       |
*=============================================================
*/

        /*Default constructor. Constructs an empty container with a default-constructed allocator.*/
    vector() : _Base(){}

    /*Constructs an empty container with the given allocator alloc*/
    explicit vector(const Allocator& alloc )  : _Base(alloc){}

    /*Constructs the container with count copies of elements with value value.*/
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
                    : _Base(count, alloc) {
        V_finish() = init<value_type *, size_type, T>(V_begin(), count, value);
    }

    /* Constructs the container with the contents of the range [first, last).
     This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
     if InputIt is an integral type.
     */
    template <class InputIt>
    vector(InputIt first, InputIt last,
           const allocator_type& alloc = allocator_type()) : _Base(alloc)
    {
        init_InputIt(first, last, typename ft::is_integral<InputIt>::type());
    };

//    vector(const vector& x) {
//        container_ = NULL;
//        alloc = x.alloc;
//        size_ = 0;
//        capacity_ = 0;
//        assign(x.begin(), x.end());
//    };

    vector& operator= (const vector& x)
    {
        if (&x == this)
            return *this;
        assign(x.begin(), x.end());
        return *this;
    };

    ~vector () { _Base::_alloc.destroy(V_begin()); };

private:

    /*struct initialise by meta*/
    /*init vector */
    template <class Iter, class Size, class iT>
    inline Iter init (Iter ptr, Size count, const iT& value)
    {
        for (size_t i = 0; i < count; i++, ++ptr)
        {
            *ptr = value;
        }
        return ptr;
    }

    /* otherwise (first and last are just input iterators),
    the copy constructor of T is called O(N) times, and
    reallocation occurs O(log N) times.*/
    template <class InputIt>
    void init_rang (InputIt first, InputIt last, std::input_iterator_tag)
    {
        std::cout<< "in input iterator constructor"<<std::endl;
       // for ( ; first != last; ++first)
           // push_back(*first);//call de copy constructor
    }

    /*   Given the distance between first and last as N ,
    if first and last are both forward, bidirectional or random-access iterators,
    the copy constructor of T is only called N  times, and
    no reallocation occurs.*/
    template <class InputIt>
    void init_rang (InputIt first, InputIt last, std::random_access_iterator_tag)
    {
        std::cout<< "in random iterator constructor"<<std::endl;
        V_begin() = this->_Base::_alloc.allocate(last - first);
        V_end() = V_begin() + (last - first);
        std::memmove(V_begin(), first,
                     static_cast<std::size_t>(last - first) * sizeof(value_type));
        V_finish() = V_begin() + (last - first);
    }

    /*
     This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
     if InputIt is an integral type.*/
    template <class Integral>
    void init_InputIt (Integral  first, Integral last, true_type)
    {
        std::cout<< "in integral haha iterator constructor"<<std::endl;
        V_begin() = this->_alloc.allocate(static_cast<size_type >(first));
        V_finish() = init(V_begin(), static_cast<size_type >(first), static_cast<value_type >(last));
        V_end() = V_begin() + static_cast<size_type >(first);
    }

    /*define the iterator tag*/
    template <class InputIt>
    void init_InputIt (InputIt  first, InputIt last, false_type)
    {
//        this->_Base::_ptr_start = this->_alloc.allocate((last - first) * sizeof(T));
//        this->_Base::_ptr_end = this->_Base::_ptr_start + (last -first);
        init_rang(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
    }


/*
*=============================================================
*|                     Element Access                        |
*=============================================================
*/



/*
*=============================================================
*|                     Iterator                              |
*=============================================================
*/

public:

    iterator begin()              { return this->_Base::_ptr_start; };
    const_iterator begin() const  { return this->_Base::_ptr_start; };
    iterator end()                { return this->_Base::_ptr_finish; };
    const_iterator end() const    { return this->_Base::_ptr_finish; };

    reverse_iterator rbegin()             { return end(); };
    reverse_iterator rend()               { return begin(); };
    const_reverse_iterator rbegin() const { return end(); };
    const_reverse_iterator rend() const   { return begin(); };

private:
    iterator V_begin()              { return &this->_Base::_ptr_start; };
    const_iterator V_begin() const  { return &this->_Base::_ptr_start; };
    iterator V_finish()             { return &this->_Base::_ptr_finish; };
    const_iterator V_finish() const { return &this->_Base::_ptr_finish; };
    iterator V_end()                { return &this->_Base::_ptr_end; };
    const_iterator V_end() const    { return &this->_Base::_ptr_end; };

/*
*=============================================================
*|                     Capacity                              |
*=============================================================
*/

public:

    /*Checks if the container has no elements, i.e. whether begin() == end().*/
    bool        empty()     const   { return V_begin() == V_finish(); };

    /*Returns the number of elements in the container, i.e. std::distance(begin(), end()).*/
    size_type   size()      const   { return V_finish() - V_begin(); };

    /*Returns the maximum number of elements the container is able to hold due to system or library implementation
     * limitations, i.e. std::distance(begin(), end()) for the largest container.*/
    size_type   max_size()  const   { return std::numeric_limits<size_type>::max() / sizeof(value_type); };

     /* increase the capacity of the vector (the total number of elements that the vector can hold without requiring
     * reallocation) to a value that's greater or equal to new_cap. If new_cap is greater than the current capacity(),
     * new storage is allocated, otherwise the function does nothing.
     * reserve() does not change the size of the vector.
     * if new_cap is greater than capacity(), all iterators, including the past-the-end iterator, and all references
     * to the elements are invalidated. Otherwise, no iterators or references are invalidated*/
//    void reserve (size_type new_cap) {
//         if (capacity() < new_cap)
//         {
//             iterator   tmp = this->_Base::_alloc.allocate(new_cap);
//
//             v.__construct_at_end(this->begin(), this->end());
//             swap(__v);
//             invalidate_all_iterators();
//         }
//        value_type *new_container = alloc_.allocate(new_cap);
//
//        for (size_type i = 0; i < size_; i++) {
//            alloc_.construct(&new_container[i], container_[i]);
//            alloc_.destroy(&container_[i]);
//        }
//        alloc_.deallocate(container_, capacity_);
//        capacity_ = new_cap;
//        container_ = new_container;
//    };

    /*Returns the number of elements that the container has currently allocated space for.*/
    size_type   capacity()  const   { return static_cast<size_type>(V_finish() - V_begin()); };

//

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





/*
*=============================================================
*|                     Modifiers                             |
*=============================================================
*/

public:

    void clear() { erase(begin(), end()); };

    /*
     * Causes reallocation if the new size() is greater than the old capacity(). If the new size() is greater than
     * capacity(), all iterators and references are invalidated. Otherwise, only the iterators and references before
     * the insertion point remain valid. The past-the-end iterator is also invalidated.
     * inserts value before pos
     */
    iterator insert ( const_iterator pos, const T& value )
    {
        if (this->end() != this->V_end())
        {
            std::copy_backward(pos , end(), pos + 1);
            this->_Base::_alloc.construct(pos, value);
        }
        else
        {
            size_t new_size = (this->V_end() - this->begin() != 0) ?
                              2 * (this->V_end() - this->begin()) : 1;
            //use reserve to manage the max size
            reserve(new_size);


        }
//
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

    /*Erases the specified elements from the container.
    Invalidates iterators and references at or after the point of the erase,
     including the end() iterator.
    The iterator pos must be valid and dereferenceable. Thus the end() iterator
     (which is valid, but is not dereferenceable) cannot be used as a value for pos.
    The  iterator first does not need to be dereferenceable if first == last:
    erasing an empty range is a no-op.

    Para   meters
    pos	-	iterator to the element to remove
    first, last	-	range of elements to remove
    Type requirements
    -T must meet the requirements of MoveAssignable.
    Return value
    Iterator following the last removed element.

    If pos refers to the last element, then the end() iterator is returned.
    If last == end() prior to removal, then the updated end() iterator is returned.

    If [first, last) is an empty range, then last is returned.*/
    //Removes the element at pos.
    iterator erase (iterator pos)
    {
        std::copy(pos + 1, end()--, pos);
        this->_Base::_alloc.destroy(end() + 1);
        return pos;
    };

    //Removes the elements in the range [first, last).
    iterator erase (iterator first, iterator last)
    {
        this->_Base::_alloc.destroy(std::copy(last, end(), first), end());
        end() = end() - (last - first);
        return first;
    };

    /*
    Appends the given element value to the end of the container.

    1) The new element is initialized as a copy of value.
    2) value is moved into the new element.
    If the new size() is greater than capacity() then all iterators and references
     (including the past-the-end iterator) are invalidated. Otherwise only the
     past-the-end iterator is invalidated.

    Parameters
    value	-	the value of the element to append
    Type requirements
    -T must meet the requirements of CopyInsertable in order to use overload (1).
    -T must meet the requirements of MoveInsertable in order to use overload (2).
     */
    void push_back (const value_type& value)
    {
        if (this->end() != this->V_end())
            this->_Base::_alloc.construct(end()++, value);
        else
            insert(this->end(), value);
    };

    /*Removes the last element of the container.
    Calling pop_back on an empty container results in undefined behavior.
    Iterators and references to the last element, as well as the end()
     iterator, are invalidated.*/
    void pop_back()
    {
        iterator tmp = end()--;
        this->_Base::_alloc.destroy(tmp);
    };

    /*Resizes the container to contain count elements.
    If the current size is greater than count, the container is reduced
     to its first count elements.
    If the current size is less than count,
    1) additional default-inserted elements are appended
    2) additional copies of value are appended.*/
    void resize (size_type count, T value = T())
    {
        if (count < size())
            erase(begin() + count, end());
        else
            insert(end(), count - size(), value);
    };

    /*
     * Exchanges the contents of the container with those of other.
     * Does not invoke any move, copy, or swap operations on individual
     * elements.All iterators and references remain valid. The
     * past-the-end iterator is invalidated.*/
    void swap (vector& other)
    {
        std::swap(this->begin(), other.begin());
        std::swap(this->end(), other.end());
        std::swap(this->V_end(), other.V_end());
    };

//private:
//    iterator swap_it(iterator& It1, iterator& It2)
//    {
//        iterator  *tmp = It1;
//        It1 = It2;
//        It2 = tmp;
//    }


};// end of class vector

/*
*=============================================================
*|                     Non Membre fonction                   |
*=============================================================
*/

/*Checks if the contents of lhs and rhs are equal,
 * that is, they have the same number of elements and each element
 * in lhs compares equal with the element in rhs at the same position.*/
template< class T, class Alloc >
bool operator==( const std::vector<T,Alloc>& lhs,
                 const std::vector<T,Alloc>& rhs )
{
    if (lhs.size() == rhs.size())
        return equal(lhs.begin(), lhs.end(), rhs.begin());
    return false;
};

template< class T, class Alloc >
bool operator!=( const std::vector<T,Alloc>& lhs,
                 const std::vector<T,Alloc>& rhs ){ return !(lhs == rhs); };

/*3-6) Compares the contents of lhs and rhs lexicographically.
 * The comparison is performed
 * by a function equivalent to std::lexicographical_compare.*/
template< class T, class Alloc >
bool operator<( const std::vector<T,Alloc>& lhs,
                const std::vector<T,Alloc>& rhs )
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                            rhs.begin(), rhs.end());
};

template< class T, class Alloc >
bool operator<=( const std::vector<T,Alloc>& lhs,
                 const std::vector<T,Alloc>& rhs ) { return !(rhs < lhs); };

template< class T, class Alloc >
bool operator>( const std::vector<T,Alloc>& lhs,
                const std::vector<T,Alloc>& rhs )  { return rhs < lhs; };

template< class T, class Alloc >
bool operator>=( const std::vector<T,Alloc>& lhs,
                 const std::vector<T,Alloc>& rhs ) { return !(lhs < rhs); };

//template <class T>
//void swap (vector<T>& x, vector<T>& y) { x.swap(y); };//a valider

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
