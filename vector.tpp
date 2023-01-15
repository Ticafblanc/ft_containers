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
        _ptr_start = (count == 0) ? 0 : static_cast<T*>(_alloc.allocate(count));
        _ptr_finish = _ptr_start;
        _ptr_end = _ptr_start + count;
        std::cout << count << std::endl;
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
class vector : private Vector_base<T, Allocator> {

private:
    typedef Vector_base<T, Allocator>                                           _Base;
    typedef vector<T, Allocator>                                                _Vector;

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

public:
        /*Default constructor. Constructs an empty container with a default-constructed allocator.*/
    vector() : _Base(){}

    /*Constructs an empty container with the given allocator alloc*/
    explicit vector(const Allocator& alloc )  : _Base(alloc){}

    /*Constructs the container with count copies of elements with value value.*/
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
                    : _Base(count, alloc) { V_finish() = insert(begin(), count, value); };

    /* Constructs the container with the contents of the range [first, last).
     This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
     if InputIt is an integral type.
     */
    template <class InputIt>
    vector(InputIt first, InputIt last,
           const allocator_type& alloc = allocator_type()) : _Base(alloc)
    { init_InputIt(first, last, typename ft::is_integral<InputIt>::type()); };

    vector( const _Vector& other ) : _Base(other._Base::_alloc)
    { assign(other.begin(), other.end()); };

    ~vector() { _Base::_alloc.destroy(V_start()); };

    /*Copy assignment operator. Replaces the contents with a copy of the contents of other.*/
    _Vector&        operator=( const vector& other )
    {
        if (&other != this)
            assign(other.begin(), other.end());
        return *this;
    };

    /*Replaces the contents of the container.
    *Replaces the contents with count copies of value value*/
    void            assign( size_type count, const value_type& value )
    {
        _resize(count);
        insert(V_start(), value);
    };

    /*Replaces the contents with copies of those in the range [first, last).
     * The behavior is undefined if either argument is an iterator into *this.
     * This overload has the same effect as overload (1) if InputIt is an integral type. */
    template< class InputIt>
    void            assign( InputIt first, InputIt last ) { assign_Input(first, last); };

    /*Returns the allocator associated with the container. */
    allocator_type  get_allocator() const { return allocator_type(); };//test par heritage

private:

    template<class InputIt>
    void    assign_Input(  InputIt first,
                           typename ft::enable_if<!ft::is_integral<InputIt>::type::value, InputIt>::type last)
    { clear(); init_rang(first, last, typename ft::iterator_traits<InputIt>::iterator_category(), 1); };

    template< class Integral >
    void    assign_Input(  Integral first,
                           typename ft::enable_if<ft::is_integral<Integral>::type::value, Integral>::type last)
    { assign(static_cast<size_type>(first), static_cast<value_type>(last)); };

    /* otherwise (first and last are just input iterators),
    the copy constructor of T is called O(N) times, and
    reallocation occurs O(log N) times.*/
    template <class InputIt>
    void init_rang (InputIt first, InputIt last, std::input_iterator_tag, int flag)
    {
        std::cout<< "in input iterator constructor"<<std::endl;
        for ( ; first != last; ++first)
            push_back(*first);//call de copy constructor
    };

    /*   Given the distance between first and last as N ,
    if first and last are both forward, bidirectional or random-access iterators,
    the copy constructor of T is only called N  times, and
    no reallocation occurs.*/
    template <class InputIt>
    void init_rang (InputIt first, InputIt last, std::random_access_iterator_tag, int flag)
    {
        _resize(last - first);
        if (flag)
            insert(V_start(), first, last);
        else
            std::memmove(V_start(), first,
                         static_cast<std::size_t>(last - first) * sizeof(value_type));
        V_finish() = V_start() + (last - first);
    };

    /*
     This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
     if InputIt is an integral type.*/
    template <class Integral>
    void init_InputIt (Integral  first, Integral last, true_type)
    { insert(V_start(), static_cast<size_type >(first), static_cast<value_type >(last)); };

    /*define the iterator tag*/
    template <class InputIt>
    void init_InputIt (InputIt  first, InputIt last, false_type)
    { init_rang(first, last, typename ft::iterator_traits<InputIt>::iterator_category(), 0); };

/*
*====================================================================================
*|                                   Element Access                                 |
*====================================================================================
*/

public:

    /*Returns a reference to the element at specified location pos,
     * with bounds checking.If pos is not within the range of the container,
     * an exception of type std::out_of_range is thrown. */
    reference       at(size_type pos)
    {
        check_size(pos);
        return V_start()[pos];
    };
    const_reference at(size_type pos) const
    {
        check_size(pos);
        return V_start()[pos];
    };

    /*Returns a reference to the element at specified location pos.
     * No bounds checking is performed.*/
    reference       operator[] (size_type pos)          { return *(begin() + pos); };
    const_reference operator[] (size_type pos) const    { return *(begin() + pos); };

    /*Returns a reference to the first element in the container.
     * Calling front on an empty container is undefined.*/
    reference       front()         { return *V_start(); };
    const_reference front() const   { return *V_start(); };

    /*Returns a reference to the last element in the container.
     * Calling back on an empty container causes undefined behavior. */
    reference       back()          { return *(V_end()- 1); };
    const_reference back() const    { return *(V_end()- 1); };

    /*Returns pointer to the underlying array serving as element storage. The pointer
     * is such that range [data(); data()+size()) is always a valid range, even if the
     * container is empty (data() is not dereferenceable in that case).*/
    T*          data()              { V_start(); };
    const T*    data() const        { V_start(); };

private:

    /*std::out_of_range if !(pos < size())*/
    void        check_size(std::size_t pos)
    {
        if (!(pos < size()))
            throw std::out_of_range("ft::vector");
    };


/*
*====================================================================================
*|                                      Iterator                                    |
*====================================================================================
*/

public:

    iterator        begin()         { return this->_Base::_ptr_start; };
    const_iterator  begin() const   { return this->_Base::_ptr_start; };
    iterator        end()           { return this->_Base::_ptr_end; };
    const_iterator  end()   const   { return this->_Base::_ptr_end; };

    reverse_iterator        rbegin()            { return end(); };
    reverse_iterator        rend()              { return begin(); };
    const_reverse_iterator  rbegin()    const   { return end(); };
    const_reverse_iterator  rend()      const   { return begin(); };

private:

    iterator&       V_start()       { return this->_Base::_ptr_start; };
    iterator&       V_finish()      { return this->_Base::_ptr_finish; };
    iterator&       V_end()         { return this->_Base::_ptr_end; };
    iterator        finish()        { return this->_Base::_ptr_finish; };
    const_iterator  finish()   const{ return this->_Base::_ptr_finish; };



/*
*====================================================================================
*|                                     Capacity                                     |
*====================================================================================
*/

public:

    /*Checks if the container has no elements, i.e. whether begin() == end().*/
    bool        empty()     const   { return V_start() == V_finish(); };

    /*Returns the number of elements in the container,
     * i.e. std::distance(begin(), end()).*/
    size_type   size()      const   { return finish() - begin(); };

    /*Returns the maximum number of elements the container is able to
     * hold due to system or library implementation limitations, i.e.
     * std::distance(begin(), end()) for the largest container.*/
    size_type   max_size()  const
    { return std::numeric_limits<size_type>::max() / sizeof(value_type); };

    /* increase the capacity of the vector (the total number of elements
     * that the vector can hold without requiring
     * reallocation) to a value that's greater or equal to new_cap. If
     * new_cap is greater than the current capacity(),
     * new storage is allocated, otherwise the function does nothing.
     * reserve() does not change the size of the vector.
     * if new_cap is greater than capacity(), all iterators, including
     * the past-the-end iterator, and all references
     * to the elements are invalidated. Otherwise, no iterators or
     * references are invalidated*/
    void        reserve(size_type new_cap)
    {
        if (max_size() > new_cap)
        {
            const size_t save_size = size();
            const size_t save_capacity = capacity() - 1;
            iterator V_new_start;
            try
            {
                V_new_start = this->_Base::_alloc.allocate(new_cap);
                std::uninitialized_copy(V_start(), V_finish(), V_new_start);
                clear();
                //this->_Base::_alloc.deallocate(V_start(), 0);
                V_start() = V_new_start;
                V_finish() = V_new_start + save_size;
                V_end() = V_new_start + new_cap;

            }
            catch (std::bad_alloc &e)
            {
                this->_Base::_alloc.deallocate(V_new_start, new_cap);
            }
        }
        else
            throw std::length_error("ft::vector");

    };

    /*Returns the number of elements that the container has currently
     * allocated space for.*/
    size_type   capacity()  const
    { return static_cast<size_type>(end() - begin()); };

/*
*====================================================================================
*|                                    Modifiers                                     |
*====================================================================================
*/


public:

    /*Erases all elements from the container. After this call, size() returns zero.
     * Invalidates any references, pointers, or iterators referring to contained elements.
     * Any past-the-end iterators are also invalidated.
     * Leaves the capacity() of the vector unchanged (note: the standard's restriction on
     * the changes to capacity is in the specification of vector::reserve, see [1])*/
    void            clear(){ erase(V_start(), V_finish()); };

    /*
     * Causes reallocation if the new size() is greater than the old capacity().
     * If the new size() is greater than
     * capacity(), all iterators and references are invalidated. Otherwise, only
     * the iterators and references before
     * the insertion point remain valid. The past-the-end iterator is also invalidated.
     * inserts value before pos
     * Exceptions
     * If an exception is thrown when inserting a single element at the end, and T is
     * CopyInsertable or std::is_nothrow_move_constructible<T>::value is true, there
     * are no effects (strong exception guarantee).
     */
    iterator        insert( const_iterator pos, const T& value )
    {
        size_type St = 1;
        iterator rIt = insert( pos, St, value );
        this->_Base::_alloc.construct(pos, value);
        V_finish()++;
        return rIt;
    };

    /*inserts count copies of the value before pos.*/
    iterator        insert( const_iterator pos, size_type count, const T& value )
    {
        iterator M_pos = const_cast<iterator>(pos);
        size_type Save_pos = pos - begin();
        if ((V_finish() - V_start()) + count + 1 >= V_end() - V_start())
            reserve(New_size (begin(), end(), count));
//        std::cout << "size = " << M_pos - finish() << std::endl;
//        if (M_pos != finish())
        std::copy_backward(M_pos, finish(), finish() + count);
//        std::cout<<"coucou"<<std::endl;

        for(size_type St = 0; St != count + count; ++St, ++pos)
            this->_Base::_alloc.construct(pos, value);
        V_finish()++;
        return const_cast<iterator>((count == 0)? pos : V_start() + Save_pos);
    };

    /*inserts elements from range [first, last) before pos.*/
    template <class InputIt>
    iterator        insert(const_iterator pos, InputIt first, InputIt last)
    {
        size_type Save_pos = pos - begin();
        //init_rang(pos, first, last, typename ft::iterator_traits<InputIt>::iterator_category());
        return const_cast<iterator>((first == last) ? pos : V_start() + Save_pos);
    };

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
    iterator        erase(iterator pos)
    {
        std::copy(pos + 1, V_finish()--, pos);
        this->_Base::_alloc.destroy(V_finish() + 1);
        return pos;
    };

    //Removes the elements in the range [first, last).
    iterator        erase(iterator first, iterator last)
    {
        iterator        It = std::copy(last, V_finish(), first);
        for(; It != V_finish(); ++It)
            this->_Base::_alloc.destroy(It);
        V_finish() = V_finish() - (last - first);
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
    void        push_back(const value_type& value)
    {
        if (V_end() != V_end())
            _Base::_alloc.construct(V_end()++, value);
        else
            insert(V_end(), value);
    };

    /*Removes the last element of the container.
    Calling pop_back on an empty container results in undefined behavior.
    Iterators and references to the last element, as well as the end()
     iterator, are invalidated.*/
    void        pop_back()
    {
        iterator tmp = V_end()--;
        _Base::_alloc.destroy(tmp);
    };

    /*Resizes the container to contain count elements.
    If the current size is greater than count, the container is reduced
     to its first count elements.
    If the current size is less than count,
    1) additional default-inserted elements are appended
    2) additional copies of value are appended.*/
    void        resize(size_type count, T value = T())
    {
        _resize(count);
        insert( (V_finish() + 1), value );
    };

    /*
     * Exchanges the contents of the container with those of other.
     * Does not invoke any move, copy, or swap operations on individual
     * elements.All iterators and references remain valid. The
     * past-the-end iterator is invalidated.*/
    void        swap(vector& other)
    {
        std::swap(V_start(), other.V_start());
        std::swap(V_end(), other.V_end());
        std::swap(V_end(), other.V_end());
    };

private:

    /*calcule the new size for reserve*/
    size_t New_size(iterator begin, iterator end, size_t count)
    {
        size_t new_size = (V_end() - V_start() != 0) ? 2 * (V_end() - V_start()) : 1;
        if ((V_end() - V_start()) + count >= new_size)
            New_size(begin, end, count - new_size);
        std::cout << "new size = " << new_size << std::endl;
        return new_size;
    }

    /*forward the pos and the first to last*/
    template <class InputIt>
    void init_rang (const_iterator pos, InputIt first, InputIt last, std::input_iterator_tag)
    {
        iterator mem_first = first;
        for ( size_t F_pos = 0; first != last; ++F_pos, ++first)
            insert(pos + F_pos, *first);//voir si manage de la destruction de la class original
    }

    /*allocate memory and copy the valeu*/
    template <class InputIt>
    void init_rang (const_iterator pos, InputIt first, InputIt last, std::random_access_iterator_tag)
    {
        if ((V_finish() - V_start()) + (last - first) + 1 >= V_end() - V_start())
            reserve(New_size (begin(), end(), static_cast<size_t>(last - first)));
        V_end() = V_start() + (last - first);
        std::memmove(V_start(), first,
                     static_cast<std::size_t>(last - first) * sizeof(value_type));
        V_finish() = V_start() + (last - first);
    }

    /*resize the container only*/
    void    _resize(size_type count)
    {
        if (count < size())
            erase(V_start() + count, V_end());
        else
            reserve(count);
    };

    /*swap two iterator */
//    iterator swap_it(iterator& It1, iterator& It2)
//    {
//        iterator  *tmp = It1;
//        It1 = It2;
//        It2 = tmp;
//    }


};// end of class vector

/*
*====================================================================================
*|                                 Non Membre fonction                              |
*====================================================================================
*/

/*Checks if the contents of lhs and rhs are equal,
 * that is, they have the same number of elements and each element
 * in lhs compares equal with the element in rhs at the same position.*/
template< class T, class Alloc >
bool operator==( const std::vector<T,Alloc>& lhs,
                 const std::vector<T,Alloc>& rhs )
{
    if (lhs.size() == rhs.size())
        return equal(lhs.V_start(), lhs.V_end(), rhs.V_start());
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
    return ft::lexicographical_compare(lhs.V_start(), lhs.V_end(),
                            rhs.V_start(), rhs.V_end());
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


__FT_CONTAINERS_END_NAMESPACE

#endif //VECTOR_TPP
