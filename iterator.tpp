/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    iterator.tpp                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 19:02:25 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/27 19:02:28 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include "ft_containers.hpp"

#ifndef FT_CONTAINERS_ITERATOR_TPP
# define FT_CONTAINERS_ITERATOR_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

/*legacy iterator struct*/
template <class T, class Distance>
struct input_iterator {
    typedef std::input_iterator_tag             iterator_category;
    typedef T                                   value_type;
    typedef Distance                            difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
};

struct output_iterator {
    typedef std::output_iterator_tag            iterator_category;
    typedef void                                value_type;
    typedef void                                difference_type;
    typedef void                                pointer;
    typedef void                                reference;
};

template <class T, class Distance>
struct forward_iterator {
    typedef std::forward_iterator_tag           iterator_category;
    typedef T                                   value_type;
    typedef Distance                            difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
};

template <class T, class Distance>
struct bidirectional_iterator {
    typedef std::bidirectional_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef Distance                            difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
};

template <class T, class Distance>
struct random_access_iterator {
    typedef std::random_access_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef Distance                            difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
};

/*define iterator_category*/
template <class T, class Distance>
inline std::input_iterator_tag  iterator_category(const input_iterator<T, Distance>&)
{ return std::input_iterator_tag(); }

inline std::output_iterator_tag iterator_category(const output_iterator&)
{ return std::output_iterator_tag(); }

template <class T, class Distance>
inline std::forward_iterator_tag iterator_category(const forward_iterator<T, Distance>&)
{ return std::forward_iterator_tag(); }

template <class T, class Distance>
inline std::bidirectional_iterator_tag iterator_category(const bidirectional_iterator<T, Distance>&)
{ return std::bidirectional_iterator_tag(); }

template <class T, class Distance>
inline std::random_access_iterator_tag iterator_category(const random_access_iterator<T, Distance>&)
{ return std::random_access_iterator_tag(); }

template <class T>
inline std::random_access_iterator_tag iterator_category(const T*)
{ return std::random_access_iterator_tag(); }

/*traits of category*/
template <bool B>
struct is_iterator_tag { static const bool value = false; };

template <>
struct is_iterator_tag<true> { static const bool value = true; };

template <typename>
struct is_input_iterator { static const bool value = false; };

template <>
struct is_input_iterator<std::input_iterator_tag> { static const bool value = true; };

template <typename>
struct is_output_iterator { static const bool value = false; };

template <>
struct is_output_iterator<std::output_iterator_tag> { static const bool value = true; };

template <typename>
struct is_forward_iterator { static const bool value = false; };

template <>
struct is_forward_iterator<std::forward_iterator_tag> { static const bool value = true; };

template <typename>
struct is_bidirectional_iterator { static const bool value = false; };

template <>
struct is_bidirectional_iterator<std::bidirectional_iterator_tag> { static const bool value = true; };

template <typename>
struct is_random_access_iterator { static const bool value = false; };

template <>
struct is_random_access_iterator<std::random_access_iterator_tag> { static const bool value = true; };

    //ft::iterator_trait https://en.cppreference.com/w/cpp/iterator/iterator_traits

/*std::iterator_traits is the type trait class that provides uniform interface to the properties of LegacyIterator
 * types. This makes it possible to implement algorithms only in terms of iterators.

The template can be specialized for user-defined iterators so that the information about the iterator can be retrieved
 even if the type does not provide the usual typedefs.*/

template <class Iter>
struct iterator_traits {
    typedef typename Iter::difference_type   difference_type;
    typedef typename Iter::value_type        value_type;
    typedef typename Iter::pointer           pointer;
    typedef typename Iter::reference         reference;
    typedef typename Iter::iterator_category iterator_category;
};

template <class T>
struct iterator_traits <T*> {
    typedef std::ptrdiff_t                  difference_type;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits <const T*> {
    typedef std::ptrdiff_t                  difference_type;
    typedef T                               value_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
    typedef std::random_access_iterator_tag iterator_category;
};

    //ft::reverse_iterator https://en.cppreference.com/w/cpp/iterator/reverse_iterator

/*std::reverse_iterator is an iterator adaptor that reverses the direction of a given iterator, which must be at
 * least a LegacyBidirectionalIterator or model bidirectional_iterator (since C++20). In other words, when provided
 * with a bidirectional iterator, std::reverse_iterator produces a new iterator that moves from the end to the
 * beginning of the sequence defined by the underlying bidirectional iterator.

For a reverse iterator r constructed from an iterator i, the relationship &*r == &*(i-1) is always true (as long as
 r is dereferenceable); thus a reverse iterator constructed from a one-past-the-end iterator dereferences to the last
 element in a sequence.

This is the iterator returned by member functions rbegin() and rend() of the standard library containers.*/

template< class Iter >
class reverse_iterator : public std::iterator<typename iterator_traits<Iter>::iterator_category,
                                                typename iterator_traits<Iter>::value_type,
                                                typename iterator_traits<Iter>::difference_type,
                                                typename iterator_traits<Iter>::pointer,
                                                typename iterator_traits<Iter>::reference>{
private:
    typedef std::iterator<typename iterator_traits<Iter>::iterator_category,
            typename iterator_traits<Iter>::value_type,
            typename iterator_traits<Iter>::difference_type,
            typename iterator_traits<Iter>::pointer,
            typename iterator_traits<Iter>::reference>              _Vector;
public:
    typedef Iter                                                    iterator_type;
    typedef typename _Vector::iterator_category                     iterator_category;
    typedef typename _Vector::value_type                            value_type;
    typedef typename _Vector::difference_type                       difference_type;
    typedef typename _Vector::pointer                               pointer;
    typedef typename _Vector::reference                             reference;

    /*Parameters constructor
    x 	- 	iterator to adapt
    other 	- 	iterator adaptor to copy
    error   -   the effect of the default constructor was not specified */

    //Default constructor. The underlying iterator is value-initialized. Operations on the resulting iterator have
    // defined behavior if and only if the corresponding operations on a value-initialized Iter also have defined
    // behavior.
    reverse_iterator() : current(iterator_type()) {}

    //The underlying iterator is initialized with x
    explicit reverse_iterator (iterator_type x) : current(x) {}

    // The underlying iterator is initialized with that of other. This overload participates in overload resolution
    // only if U is not the same type as Iter and std::convertible_to<const U&, Iter> is modeled (since C++20).
    template <class U>
    reverse_iterator (const reverse_iterator<U>& other) : current(other.base()) {}

    /*destructor*/
    ~reverse_iterator() {}

    /*Parameters
    other 	- 	iterator adaptor to assign
    Return value
    *this
    ERROR   -   a std::reverse_iterator could be constructed, but not assigned, from
    another std::reverse_iterator with a different underlying iterator type*/
    template <class U>
    reverse_iterator& operator=( const reverse_iterator<U>& other )
    {
        this->current = other.base();
        return *this;
    }

    /*Returns the underlying base iterator. That is std::reverse_iterator(it).base() == it.
    The base iterator refers to the element that is next (from the std::reverse_iterator::iterator_type perspective)
     to the element the reverse_iterator is currently pointing to. That is &*(rit.base() - 1) == &*rit.*/
    iterator_type	base() const{ return (this->current); }

    // Equivalent to Iter tmp = current; return *--tmp;
    reference		operator*() const
    {
        iterator_type tmp = current;
        return (*(--tmp));
    }

    // Equivalent to return std::addressof(operator*());.
    pointer operator->() const{ return std::addressof(operator*()); }
//    pointer operator->() const {
//        iterator_type	tmp(this->_base_iterator);
//        tmp--;
//        return(tmp.operator->());
//        // return &(operator*());
//    }

    //Returns a reference to the element at specified relative location.
    //A reference to the element at relative location, that is, base()[-n-1].
    reference operator[] (difference_type n) const { return (base()[-n-1]); }

        //Pre-increments or pre-decrements by one respectively
    //*this.
    reverse_iterator& operator++()
    {
        --(this->current);
        return (*this);
    }

    reverse_iterator& operator--() {
        ++(this->current);
        return (*this);
    }

    //Post-increments or post-decrements by one respectively.
    // a copy of *this that was made before the change
    reverse_iterator operator++(int) {
        reverse_iterator tmp = *this;
        ++(*this->current);
        return tmp;
    }

    reverse_iterator operator--(int) {
        reverse_iterator tmp = *this;
        --(*this->current);
        return tmp;
    }

    //Returns an iterator which is advanced by n or -n positions respectively.
    //reverse_iterator(base()-n) or reverse_iterator(base()+n) respectively.
    reverse_iterator operator+ (difference_type n) const{ return ( reverse_iterator(this->base() - n)); }

    reverse_iterator operator- (difference_type n) const { return ( reverse_iterator(this->base() + n)); }

    //Advances the iterator by n or -n positions respectively.
    //*this
    reverse_iterator& operator+= (difference_type n)
    {
        this->current -= n;
        return(*this);
    }

    reverse_iterator& operator-= (difference_type n)
    {
        this->_base_iterator += n;
        return(*this);
    }

protected:
    //the underlying iterator of which base() returns a copy
    Iter current;
};

//lhs.base() == rhs.base()
template <typename Iterator1, typename Iterator2>
bool operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{ return (lhs.base() == rhs.base()); }

//lhs.base() != rhs.base()
template <typename Iterator1, typename Iterator2>
bool operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{ return (lhs.base() != rhs.base()); }

//lhs.base() > rhs.base()
template <typename Iterator1, typename Iterator2>
bool operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{ return (lhs.base() > rhs.base()); }

//lhs.base() >= rhs.base()
template <typename Iterator1, typename Iterator2>
bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{ return (lhs.base() >= rhs.base()); }

//lhs.base() < rhs.base()
template <typename Iterator1, typename Iterator2>
bool operator> (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{ return (lhs.base() < rhs.base()); }

//lhs.base() <= rhs.base()
template <typename Iterator1, typename Iterator2>
bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{ return (lhs.base() <= rhs.base()); }

//Parameters
//n 	- 	the number of positions to increment the iterator
//it 	- 	the iterator adaptor to increment
//Return value
//
//The incremented iterator, that is reverse_iterator<Iter>(it.base() - n)
template <class Iter>
reverse_iterator<Iter> operator+ (typename reverse_iterator<Iter>::difference_type n,
                                        const reverse_iterator<Iter>& it)
{ return (it.base() - n); }

//Parameters
//lhs, rhs 	- 	iterator adaptors to compute the difference of
//Return value
//
//rhs.base() - lhs.base()
template <typename Iterator1, typename Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator- (const reverse_iterator<Iterator1>& lhs,
                                                                    const reverse_iterator<Iterator2>& rhs)
{ return((rhs.base() - lhs.base())); }


__FT_CONTAINERS_END_NAMESPACE

#endif //FT_CONTAINERS_ITERATOR_TPP
