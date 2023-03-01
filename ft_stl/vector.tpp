/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vector.tpp                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 21:56:15 by mdoquocb          #+#    #+#              #
#    Updated: 2023/01/29 18:27:02 by mdoquocb         ###   ########.ca        #
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
class VectorBase {

protected:
    typedef Allocator                                                           allocator_type;

    VectorBase() : _ptr_begin(0), _ptr_end(0), _ptr_end_of_alloc(0) {}
    /*Solved allocator conflic*/
    explicit VectorBase(const Allocator&) : _ptr_begin(0), _ptr_end(0), _ptr_end_of_alloc(0) {}

    explicit VectorBase(std::size_t count, const Allocator&) : _ptr_begin(0), _ptr_end(0), _ptr_end_of_alloc(0){
        _ptr_begin = (count == 0) ? 0 : _alloc.allocate(count);
        _ptr_end = _ptr_begin;
        _ptr_end_of_alloc = _ptr_begin + count;
    }

    ~VectorBase() {
        _alloc.deallocate((_ptr_begin), (_ptr_end_of_alloc - _ptr_begin));
    };


protected:
    T* _ptr_begin;
    T* _ptr_end;
    T* _ptr_end_of_alloc;
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
class vector : private VectorBase<T, Allocator> {

private:
    typedef VectorBase<T, Allocator>                                            Base;
    typedef vector<T, Allocator>                                                Vector;

/*
*====================================================================================
*|                                     Member Type                                  |
*====================================================================================
*/

public:
    typedef T                                                                   value_type;
    typedef typename Base::allocator_type                                       allocator_type;
    typedef std::size_t                                                         size_type;
    typedef std::ptrdiff_t                                                      difference_type;
    typedef value_type&                                                         reference;
    typedef const value_type&                                                   const_reference;
    typedef typename Base::allocator_type::pointer                              pointer;
    typedef typename Base::allocator_type::const_pointer                        const_pointer;
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
    vector() : Base(){};

    /*Constructs an empty container with the given allocator alloc*/
    explicit vector(const Allocator& alloc )  : Base(alloc){};

    /*Constructs the container with count copies of elements with value value.*/
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
                    : Base(count, alloc) { insert(count, value); };

    /* Constructs the container with the contents of the range [first, last).
     This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
     if InputIt is an integral type.
     */
    template <class InputIt>
    vector(InputIt first, InputIt last,
           const allocator_type& alloc = allocator_type()) : Base(alloc)
    { Select_Input( begin(), first, last, static_cast<size_type>(last - first));  };

    vector( const Vector& other ) : Base(other.Base::_alloc)
    { assign(other.begin(), other.end());  };

    ~vector()
    { clear(); };

    /*Copy assignment operator. Replaces the contents with a copy of the contents of other.*/
    Vector&        operator=( const Vector& other )
    {

        if (&other != this)
            assign(other.begin(), other.end());


        return *this;
    };

    /*Replaces the contents of the container.
    *Replaces the contents with count copies of value value*/
    void            assign( size_type count, const value_type& value )
    {
        clear();
        insert(begin(),count, value);

    };

    /*Replaces the contents with copies of those in the range [first, last).
     * The behavior is undefined if either argument is an iterator into *this.
     * This overload has the same effect as overload (1) if InputIt is an integral type. */
    template< class InputIt>
    void            assign( InputIt first, InputIt last )
    {

        clear();
        Select_Input( begin(), first, last, last - first );

    };

    /*Returns the allocator associated with the container. */
    allocator_type  get_allocator() const { allocator_type(); };//test par heritage


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
        return begin()[pos];

    };

    const_reference at(size_type pos) const
    {

        check_size(pos);
        return begin()[pos];

    };

    /*Returns a reference to the element at specified location pos.
     * No bounds checking is performed.*/
    reference       operator[] (size_type pos)          { return at(pos); };
    const_reference operator[] (size_type pos) const    { return at(pos); };

    /*Returns a reference to the first element in the container.
     * Calling front on an empty container is undefined.*/
    reference       front()         { return *begin(); };
    const_reference front() const   { return *begin(); };

    /*Returns a reference to the last element in the container.
     * Calling back on an empty container causes undefined behavior. */
    reference       back()          { return *(end()- 1); };
    const_reference back() const    { return *(end()- 1); };

    /*Returns pointer to the underlying array serving as element storage. The pointer
     * is such that range [data(); data()+size()) is always a valid range, even if the
     * container is empty (data() is not dereferenceable in that case).*/
    T*          data()              { begin(); };
    const T*    data() const        { begin(); };

private:

    /*std::out_of_range if !(pos < size())*/
    void        check_size(size_type pos)
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

    iterator                begin()                 { return this->Base::_ptr_begin; };
    const_iterator          begin()         const   { return this->Base::_ptr_begin; };
    iterator                end()                   { return this->Base::_ptr_end; };
    const_iterator          end()           const   { return this->Base::_ptr_end;; };
    reverse_iterator        rbegin()                { return reverse_iterator (end()); };
    reverse_iterator        rend()                  { return reverse_iterator (begin()); };
    const_reverse_iterator  rbegin()        const   { return reverse_iterator (end()); };
    const_reverse_iterator  rend()          const   { return reverse_iterator (begin()); };

private:

    iterator&               Rbegin()                { return this->Base::_ptr_begin; };
    iterator&               Rend_of_alloc()         { return this->Base::_ptr_end_of_alloc; };
    iterator&               Rend()                  { return this->Base::_ptr_end; };
    iterator                end_of_alloc()          { return this->Base::_ptr_end_of_alloc; };
    const_iterator          end_of_alloc()  const   { return this->Base::_ptr_end_of_alloc; };

/*
*====================================================================================
*|                                     Capacity                                     |
*====================================================================================
*/

public:

    /*Checks if the container has no elements, i.e. whether begin() == end().*/
    bool        empty()     const   { return begin() == end(); };

    /*Returns the number of elements in the container,
     * i.e. std::distance(begin(), end()).*/
    size_type   size()      const   { return (end() - begin()); };

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
            if ( new_cap > capacity() )
            {

                const size_type save_size = size();
                iterator V_new_start;
                try
                {

                    V_new_start = this->Base::_alloc.allocate(new_cap);
                    std::uninitialized_copy(begin(), end_of_alloc(), V_new_start);
                    clear();
                    this->Base::_alloc.deallocate(begin(), capacity());
                    Rbegin() = V_new_start;
                    Rend() = V_new_start + save_size;
                    Rend_of_alloc() = V_new_start + new_cap;

                }
                catch (std::bad_alloc &e)
                {
                    this->Base::_alloc.deallocate(V_new_start, new_cap);
                }
            }
        }
        else
            throw std::length_error("ft::vector");


    };

    /*Returns the number of elements that the container has currently
     * allocated space for.*/
    size_type   capacity()  const
    { return static_cast<size_type>(end_of_alloc() - begin()); };

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
    void            clear(){ erase(begin(), end()); };

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

        iterator Pos = const_cast<iterator>(pos);
        To_Make_Place(Pos, 1, 0);
        this->Base::_alloc.construct(Pos, value);
        return Pos;
    };

    /*inserts count copies of the value before pos.*/
    iterator        insert( const_iterator pos, size_type count, const T& value )
    {

        iterator Pos = const_cast<iterator>(pos);
        To_Make_Place(Pos, count, count + size());
        for(size_type St = 0; St < count ; ++St, ++Pos) {
            this->Base::_alloc.construct(Pos, value);
        }

        return (count == 0)? const_cast<iterator>(pos) : Pos;
   };

    /*inserts elements from range [first, last) before pos.*/
    template <class InputIt>
    iterator        insert(const_iterator pos, InputIt first, InputIt last)
    {

        size_type Save_pos = pos - begin();
        Select_Input(pos, first, last, 0);


        return (first == last) ? const_cast<iterator>(pos) : begin() + Save_pos;
    };

private:

    /*make place to put value in*/
    void      To_Make_Place(iterator& Pos, size_type count, size_type SpecSize)
    {

        if (size() + count > capacity()){
            size_type Save_pos = Pos - begin();
            reserve((SpecSize != 0) ? SpecSize : New_size (count));
            Pos = begin() + Save_pos;
        }
        if ((end_of_alloc() - Pos) > 0)//si comportement identique
            std::copy_backward(Pos, end(), end() + count);
        Rend() += count;
    };

    /*calcule the new size for reserve*/
    size_type New_size( size_type count )
    {

        size_type new_size = (capacity() != 0) ? 2 * capacity() : count;
        while (capacity() + count > new_size)
            new_size += 2 * new_size;


        return new_size;
    };


    /*
     * This constructor has the same effect as
     * vector/insert(static_cast<size_type>(first),static_cast<value_type>(last)
     * if InputIt is an integral type for constructor/insert*/
    template< class Integral >
    void        Select_Input(  const_iterator pos, Integral first,
                           typename ft::enable_if<ft::is_integral<Integral>::value, Integral>::type last,
                           size_type SpecSize)
    {
        (void)SpecSize;
        insert(pos, static_cast<size_type>(first), static_cast<const value_type>(last));

    };

    /*   Given the distance between first and last as N ,
    if first and last are both forward, bidirectional or random-access iterators,
    the copy constructor of T is only called N  times, and
    no reallocation occurs.*/
    template <class InputIt>
    void        Select_Input(   const_iterator pos,
                                typename ft::enable_if<ft::is_random_access_iterator
                                    <typename ft::iterator_traits_if
                                    <InputIt, !is_integral
                                    <InputIt>::value>::iterator_category>::value, InputIt>::type first,
                                InputIt last, size_type SpecSize)
    {

        size_type oldCap = capacity();
        size_type oldSiz = size();
        iterator Pos = const_cast<iterator>(pos);
        To_Make_Place(Pos, static_cast<size_type>(last - first), SpecSize);
        try{
            std::uninitialized_copy(first, last, Pos);
        }
        catch (...)
        {
            std::copy_backward(Pos + static_cast<size_type>(last - first), end_of_alloc(), Pos);
            Rend() = begin() + oldSiz;
            Rend_of_alloc() = begin() + oldCap;
            throw;
        }

    };

    /* otherwise (first and last are just input iterators),
      the copy constructor of T is called O(N) times, and
      reallocation occurs O(log N) times.*/
    template< class InputIt >
    void        Select_Input(   const_iterator pos,
                                typename ft::enable_if<ft::is_input_iterator
                                   <typename ft::iterator_traits_if
                                   <InputIt, !ft::is_integral
                                   <InputIt>::value>::iterator_category>::value, InputIt>::type first,
                                InputIt last, size_type SpecSize)
    {

        (void)pos; (void)SpecSize;
        for ( ; first != last; ++first)
            push_back(*first);

    };



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
    /*Removes the element at pos.*/
    iterator        erase(iterator pos)
    {
        if (pos != end())
            std::copy(pos + 1, end(), pos);
        this->Base::_alloc.destroy(--Rend() + 1);


        return pos;
    };

    /*Removes the elements in the range [first, last).*/
    iterator        erase(iterator first, iterator last)
    {

        if ( first && last && (last - first) > 0 )
        {
            iterator  B = begin();
            if ( (end() - last) > 0 )
                B = std::copy(last, end_of_alloc(), first);
            for(; B != end(); ++B)
                this->Base::_alloc.destroy(B);
            Rend() = end() - (last - first);
        }


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

        if (size() >= capacity())
            reserve(New_size (1));
        this->Base::_alloc.construct(++Rend() - 1, value);

     };

    /*Removes the last element of the container.
    Calling pop_back on an empty container results in undefined behavior.
    Iterators and references to the last element, as well as the end()
     iterator, are invalidated.*/
    void        pop_back()
    { erase(end());  };

    /*Resizes the container to contain count elements.
    If the current size is greater than count, the container is reduced
     to its first count elements.
    If the current size is less than count,
    1) additional default-inserted elements are appended
    2) additional copies of value are appended.*/
    void        resize(size_type count, T value = T())
    {

        if (count < size())
            erase(begin() + count, end());
        else if (count > size()){
            if (count > capacity())
                reserve(New_size (count- size()));
            insert( end(), count - size(), value );
        }


    };

    /*
     * Exchanges the contents of the container with those of other.
     * Does not invoke any move, copy, or swap operations on individual
     * elements.All iterators and references remain valid. The
     * past-the-end iterator is invalidated.*/
    void        swap(vector& other)
    {

        std::swap(Rend_of_alloc(), other.Rend_of_alloc());
        std::swap(Rbegin(), other.Rbegin());
        std::swap(Rend(), other.Rend());


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
inline bool operator== ( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
    if (lhs.size() == rhs.size())
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    return false;
};

template< class T, class Alloc >
inline bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ){ return !(lhs == rhs); };

/*3-6) Compares the contents of lhs and rhs lexicographically.
 * The comparison is performed
 * by a function equivalent to std::lexicographical_compare.*/
template< class T, class Alloc >
inline bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                            rhs.begin(), rhs.end());
};

template< class T, class Alloc >
inline bool operator<=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ) { return !(rhs < lhs); };

template< class T, class Alloc >
inline bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )  { return rhs < lhs; };

template< class T, class Alloc >
inline bool operator>=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ) { return !(lhs < rhs); };

__FT_CONTAINERS_END_NAMESPACE

namespace std {
    template<class T, class Alloc>
    inline void swap(ft::vector <T, Alloc> &lhs, ft::vector <T, Alloc> &rhs)
    { lhs.swap(rhs);  };
}

#endif //VECTOR_TPP
