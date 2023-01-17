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

/* Private base classe manage Allocator*/
template <class T, class Allocator>
class Vector_base {

public:
    typedef Allocator                                                           allocator_type;

    Vector_base() : _ptr_start(0), _ptr_finish(0), _ptr_end(0) {}
    /*Solved allocator conflic*/
    Vector_base(const Allocator&) : _ptr_start(0), _ptr_finish(0), _ptr_end(0) {}

    Vector_base(std::size_t count, const Allocator&) : _ptr_start(0), _ptr_finish(0), _ptr_end(0){
        _ptr_start = (count == 0) ? 0 : _alloc.allocate(count);
        _ptr_finish = _ptr_start;
        _ptr_end = _ptr_start + count;
    }

    ~Vector_base() {_alloc.deallocate(_ptr_start, (_ptr_end - _ptr_start)); };

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
*====================================================================================
*|                                     Member Type                                  |
*====================================================================================
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
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:
        /*Default constructor. Constructs an empty container with a default-constructed allocator.*/
    vector() : _Base(){__INFOMF__}

    /*Constructs an empty container with the given allocator alloc*/
    explicit vector(const Allocator& alloc )  : _Base(alloc){__INFOMF__}

    /*Constructs the container with count copies of elements with value value.*/
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
                    : _Base(count, alloc) {__INFOMF__ insert(static_cast<iterator>(V_start()), count, value); __INFOMFNL__};

    /* Constructs the container with the contents of the range [first, last).
     This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
     if InputIt is an integral type.
     */
    template <class InputIt>
    vector(InputIt first, InputIt last,
           const allocator_type& alloc = allocator_type()) : _Base(alloc)
    {__INFOMF__ select_Input(first, last, 0); };

    vector( const _Vector& other ) : _Base(other._Base::_alloc)
    {__INFOMF__ assign(other.begin(), other.end()); __INFOMFNL__};

    ~vector()
    {__INFOMF__
        for(iterator It = V_start(); It != V_end(); ++It)
            _Base::_alloc.destroy(V_start());
    };

    /*Copy assignment operator. Replaces the contents with a copy of the contents of other.*/
    _Vector&        operator=( const _Vector& other )
    {__INFOMF__
        if (&other != this)
            assign(other.begin(), other.end() - 1);
        __INFOMFNL__
        return *this;
    };

    /*Replaces the contents of the container.
    *Replaces the contents with count copies of value value*/
    void            assign( size_type count, const value_type& value )
    {__INFOMF__
        resize(count);
        erase(V_start(), V_finish());
        insert(V_start(),count, value);
        __INFOMFNL__
    };

    /*Replaces the contents with copies of those in the range [first, last).
     * The behavior is undefined if either argument is an iterator into *this.
     * This overload has the same effect as overload (1) if InputIt is an integral type. */
    template< class InputIt>
    void            assign( InputIt first, InputIt last ) {__INFOMF__ select_Input(first, last, 1); __INFOMFNL__};

    /*Returns the allocator associated with the container. */
    allocator_type  get_allocator() const {__INFOMF__ return allocator_type(); };//test par heritage

private:

    /*
     * This constructor has the same effect as
     * vector(static_cast<size_type>(first),static_cast<value_type>(last), a)
     * if InputIt is an integral type for constructor*/
    template< class Integral >
    void    select_Input(  Integral first,
                           typename ft::enable_if<ft::is_integral<Integral>::value, Integral>::type last,
                           int flag)
    {__INFOMF__ assign(static_cast<size_type>(first), static_cast<value_type>(last)); __INFOMFNL__};

    /* otherwise (first and last are just input iterators),
    the copy constructor of T is called O(N) times, and
    reallocation occurs O(log N) times.*/
    template< class InputIt >
    void    select_Input(  typename iterator_traits<typename ft::enable_if
                            <ft::is_random_access_iterator
                            <typename ft::iterator_traits
                            <typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type
                            >::iterator_category>::value, InputIt>::type>::pointer first,
                            InputIt last, int flag)
    {__INFOMF__
        resize(last - first);
        erase(V_start(), V_finish());
        if (flag)
            insert(V_start(), first, last);
        else
            std::memmove(V_start(), first,
                         static_cast<size_type>(last - first));// * sizeof(value_type));
        V_finish() = V_start() + (last - first);
    __INFOMFNL__};

    /*   Given the distance between first and last as N ,
    if first and last are both forward, bidirectional or random-access iterators,
    the copy constructor of T is only called N  times, and
    no reallocation occurs.*/
    template< class InputIt >
    void    select_Input(  typename iterator_traits<typename ft::enable_if
                            <ft::is_input_iterator
                            <typename ft::iterator_traits
                            <typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type
                            >::iterator_category>::value, InputIt>::type>::pointer first,
                            InputIt last, int flag)
    {__INFOMF__
        for ( ; first != last; ++first)
            push_back(*first);
             __INFOMFNL__
    };

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
    {__INFOEA__
        check_size(pos);
        return V_start()[pos];
    };
    const_reference at(size_type pos) const
    {__INFOEA__
        check_size(pos);
        return V_start()[pos];
    };

    /*Returns a reference to the element at specified location pos.
     * No bounds checking is performed.*/
    reference       operator[] (size_type pos)          {__INFOEA__ return *(begin() + pos); };
    const_reference operator[] (size_type pos) const    {__INFOEA__ return *(begin() + pos); };

    /*Returns a reference to the first element in the container.
     * Calling front on an empty container is undefined.*/
    reference       front()         {__INFOEA__ return *V_start(); };
    const_reference front() const   {__INFOEA__ return *V_start(); };

    /*Returns a reference to the last element in the container.
     * Calling back on an empty container causes undefined behavior. */
    reference       back()          {__INFOEA__ return *(V_end()- 1); };
    const_reference back() const    {__INFOEA__ return *(V_end()- 1); };

    /*Returns pointer to the underlying array serving as element storage. The pointer
     * is such that range [data(); data()+size()) is always a valid range, even if the
     * container is empty (data() is not dereferenceable in that case).*/
    T*          data()              {__INFOEA__ V_start(); };
    const T*    data() const        {__INFOEA__ V_start(); };

private:

    value_type*&    V_start()       {__INFOIT__ return this->_Base::_ptr_start; };
    value_type*&    V_finish()      {__INFOIT__ return this->_Base::_ptr_finish; };
    value_type*&    V_end()         {__INFOIT__ return this->_Base::_ptr_end; };
    value_type*     Vc_start()  const   {__INFOIT__ return this->_Base::_ptr_start; };
    value_type*     Vc_finish() const   {__INFOIT__ return this->_Base::_ptr_finish; };
    value_type*     Vc_end()    const   {__INFOIT__ return this->_Base::_ptr_end; };

    /*std::out_of_range if !(pos < size())*/
    void        check_size(size_type pos)
    {__INFOEA__
        if (!(pos < size()))
            throw std::out_of_range("ft::vector");
    };

/*
*====================================================================================
*|                                      Iterator                                    |
*====================================================================================
*/

public:

    iterator                begin()             {__INFOIT__ return this->_Base::_ptr_start; };
    const_iterator          begin()     const   {__INFOIT__ return this->_Base::_ptr_start; };
    iterator                end()               {__INFOIT__ return this->_Base::_ptr_end; };

    const_iterator          end()       const   {__INFOIT__ return this->_Base::_ptr_end; };
    reverse_iterator        rbegin()            {__INFOIT__ return end(); };
    reverse_iterator        rend()              {__INFOIT__ return begin(); };
    const_reverse_iterator  rbegin()    const   {__INFOIT__ return end(); };

/*
*====================================================================================
*|                                     Capacity                                     |
*====================================================================================
*/

public:

    /*Checks if the container has no elements, i.e. whether begin() == end().*/
    bool        empty()     const   {__INFOCA__ return V_start() == V_finish(); };

    /*Returns the number of elements in the container,
     * i.e. std::distance(begin(), end()).*/
    size_type   size()      const   {__INFOCA__ return (Vc_finish() - Vc_start()); };

    /*Returns the maximum number of elements the container is able to
     * hold due to system or library implementation limitations, i.e.
     * std::distance(begin(), end()) for the largest container.*/
    size_type   max_size()  const
    {__INFOCA__ return std::numeric_limits<size_type>::max() / sizeof(value_type); };

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
    {__INFOCA__
        if (max_size() > new_cap)
        {
            const size_type save_size = size();
            const size_type save_capacity = capacity() - 1;
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
        __INFOCANL__
    };

    /*Returns the number of elements that the container has currently
     * allocated space for.*/
    size_type   capacity()  const
    {__INFOCA__ return static_cast<size_type>(Vc_end() - Vc_start()); };

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
    void            clear(){__INFOMO__ erase(V_start(), V_finish()); __INFOMONL__};

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
    {__INFOMO__
        size_type St = 1;
        iterator rIt = insert( pos, St, value );
//        std::cout <<*pos << " "<<pos << std::endl;
        this->_Base::_alloc.construct(pos, value);
//        std::cout <<*pos <<pos << std::endl;
        V_finish()++;
        __INFOMONL__
        return rIt;
    };

    /*inserts count copies of the value before pos.*/
    iterator        insert( const_iterator pos, size_type count, const T& value )
    {__INFOMO__
        size_type Save_pos = pos - begin();
        if (count > capacity())
            reserve(New_size (V_finish(), V_end(), count));
        std::copy_backward(const_cast<iterator>(pos), V_finish(), V_finish() + count);
        for(size_type St = 0; St < count ; ++St, ++pos, ++V_finish())
            this->_Base::_alloc.construct(pos, value);
        __INFOMONL__
        return const_cast<iterator>((count == 0)? pos : V_start() + Save_pos);
   };

    /*inserts elements from range [first, last) before pos.*/
    template <class InputIt>
    iterator        insert(const_iterator pos, InputIt first, InputIt last)
    {__INFOMO__
        size_type Save_pos = pos - V_finish();
        init_rang(pos, first, last, typename ft::iterator_traits<InputIt>::iterator_category());
        __INFOMONL__
        return const_cast<iterator>((first == last) ? pos : V_start() + Save_pos);
    };

private:

    /*calcule the new size for reserve*/
    size_type New_size(iterator _begin, iterator _end, size_type count)
    {__INFOMO__
        size_type new_size = (end() - begin() != 0) ? 2 * (end() - begin()) : 1;
        if ((end() - begin()) + count >= new_size)
            return New_size(_begin, _end, count - new_size);
        __INFOMONL__
        return new_size;
    }

    /*forward the pos and the first to last*/
    template <class InputIt>
    void init_rang (const_iterator pos, InputIt first, InputIt last, std::input_iterator_tag)
    {__INFOMO__
        iterator mem_first = first;
        for ( size_type F_pos = 0; first != last; ++F_pos, ++first)
            insert(pos + F_pos, *first);//voir si manage de la destruction de la class original
        __INFOMONL__
    }

    /*allocate memory and copy the valeu*/
    template <class InputIt>
    void init_rang (const_iterator pos, InputIt first, InputIt last, std::random_access_iterator_tag)
    {__INFOMO__
        if (size() + (last - first) >= capacity())
            reserve(New_size (V_start(), V_end(), static_cast<size_type>(last - first)));
        V_end() = V_start() + (last - first);
        std::memmove(V_start(), first,
                     static_cast<size_type>(last - first) * sizeof(value_type));
        V_finish() = V_start() + (last - first);
        __INFOMONL__
    }

public:

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
    {__INFOMO__
        if (pos != V_finish()) {
            std::copy(pos + 1, V_finish()--, pos);
            this->_Base::_alloc.destroy(V_finish() + 1);
        }
        else
            this->_Base::_alloc.destroy(V_finish());
        __INFOMONL__
        return pos;
    };

    //Removes the elements in the range [first, last).
    iterator        erase(iterator first, iterator last)
    {__INFOMO__
        iterator        It = std::copy(last, V_finish(), first);
        for(; It != V_finish(); ++It)
            this->_Base::_alloc.destroy(It);
        V_finish() = V_finish() - (last - first);
        __INFOMONL__
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
    {__INFOMO__
        if (size() < capacity())
            _Base::_alloc.construct(V_finish()++, value);
        else
            insert(V_finish(), value);
        __INFOMONL__
    };

    /*Removes the last element of the container.
    Calling pop_back on an empty container results in undefined behavior.
    Iterators and references to the last element, as well as the end()
     iterator, are invalidated.*/
    void        pop_back()
    {__INFOMO__
        iterator tmp = V_end()--;
        _Base::_alloc.destroy(tmp);
        __INFOMONL__
    };

    /*Resizes the container to contain count elements.
    If the current size is greater than count, the container is reduced
     to its first count elements.
    If the current size is less than count,
    1) additional default-inserted elements are appended
    2) additional copies of value are appended.*/
    void        resize(size_type count, T value = T())
    {__INFOMO__
        if (count < size()) {
            erase(V_start() + count, V_end());
        }
        else if (count > size()){
            reserve(count);
            insert( V_finish(), value );
        }

        __INFOMONL__
    };

    /*
     * Exchanges the contents of the container with those of other.
     * Does not invoke any move, copy, or swap operations on individual
     * elements.All iterators and references remain valid. The
     * past-the-end iterator is invalidated.*/
    void        swap(vector& other)
    {__INFOMO__
        std::swap(V_start(), other.V_start());
        std::swap(V_end(), other.V_end());
        std::swap(V_end(), other.V_end());
        __INFOMONL__
    };


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
inline bool operator==( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{__INFONM__
    if (lhs.size() == rhs.size())
        return equal(lhs.V_start(), lhs.V_end(), rhs.V_start());
    return false;
};

template< class T, class Alloc >
inline bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ){__INFONM__ return !(lhs == rhs); };

/*3-6) Compares the contents of lhs and rhs lexicographically.
 * The comparison is performed
 * by a function equivalent to std::lexicographical_compare.*/
template< class T, class Alloc >
inline bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{__INFONM__
    return ft::lexicographical_compare(lhs.V_start(), lhs.V_end(),
                            rhs.V_start(), rhs.V_end());
};

template< class T, class Alloc >
inline bool operator<=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ) {__INFONM__ return !(rhs < lhs); };

template< class T, class Alloc >
inline bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )  {__INFONM__ return rhs < lhs; };

template< class T, class Alloc >
inline bool operator>=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ) {__INFONM__ return !(lhs < rhs); };

//template <class T>
//void swap (vector<T>& x, vector<T>& y) { x.swap(y); };//a valider


__FT_CONTAINERS_END_NAMESPACE

#endif //VECTOR_TPP
