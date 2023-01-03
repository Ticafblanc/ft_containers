/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utility.tpp                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 20:47:15 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/26 20:47:28 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include "ft_containers.hpp"

#ifndef FT_CONTAINERS_UTILITY_TPP
# define FT_CONTAINERS_UTILITY_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

//ft::pair

/*Parameters
        x 	- 	value to initialize the first element of this pair
        y 	- 	value to initialize the second element of this pair
        p 	- 	pair of values used to initialize both elements of this pair
        first_args 	- 	tuple of constructor arguments to initialize the first element of this pair
        second_args 	- 	tuple of constructor arguments to initialize the second element of this pair
        Exceptions

Does not throw exceptions unless one of the specified operations (e.g. constructor of an element) throws.*/

template<class T1, class T2>
struct pair {
    //Member types
    typedef T1 first_type;
    typedef T2 second_type;

    //Member objects
    first_type first;
    second_type second;

    //Constructors
    //Default constructor. Value-initializes both elements of the pair, first and second.
    pair() : first(), second() {};

    //Initializes first with x and second with y.
    pair(const T1 &x, const T2 &y) : first(x), second(y) {};

    // Initializes first with p.first and second with p.second.
    template<class U1, class U2>
    pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {};

    //Destructors
    ~pair() {};

    pair<T1, T2> &operator=(const pair<T1, T2> &pr) {
        first = pr.first;
        second = pr.second;
        return *this;
    };
};

/*Parameters
lhs, rhs 	- 	pairs to compare
Return value
1) true if both lhs.first == rhs.first and lhs.second == rhs.second, otherwise false
2) !(lhs == rhs)
3) If lhs.first<rhs.first, returns true. Otherwise, if rhs.first<lhs.first, returns false. Otherwise,
 if lhs.second<rhs.second, returns true. Otherwise, returns false.
4) !(rhs < lhs)
5) rhs < lhs
6) !(lhs < rhs)
7) synth_three_way(lhs.first, rhs.first) if it is not equal to 0, otherwise synth_three_way(lhs.second, rhs.second),
 where synth_three_way is an exposition-only function object performing synthesized three-way comparison.*/

//Tests if both elements of lhs and rhs are equal, that is, compares lhs.first with rhs.first and lhs.second with
// rhs.second.
template <class T1, class T2>
bool operator== (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
};

template <class T1, class T2>
bool operator!= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    return !(lhs == rhs);
};

//Compares lhs and rhs lexicographically by operator<, that is, compares the first elements and only if they are
// equivalent, compares the second elements
template <class T1, class T2>
bool operator<  (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    if (lhs.first < rhs.first)
        return lhs.second < rhs.second;
    return lhs.first < rhs.first;
};

template <class T1, class T2>
bool operator>  (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    if (lhs.first > rhs.first)
        return lhs.second > rhs.second;
    return lhs.first > rhs.first;
};

template <class T1, class T2>
bool operator<= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    if (lhs.first <= rhs.first)
        return lhs.second <= rhs.second;
    return lhs.first <= rhs.first;
};

template <class T1, class T2>
bool operator>= (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) {
    if (lhs.first >= rhs.first)
        return lhs.second >= rhs.second;
    return lhs.first >= rhs.first;
};

//ft::make_pair

/*Parameters
t, u 	- 	the values to construct the pair from
Return value

A std::pair object containing the given values. */

//creates a pair object of type, defined by the argument types
//Creates a ft::pair object, deducing the target type from the types of arguments.
template <class T1, class T2>
ft::pair<T1, T2> make_pair(T1 t, T2 u) {
    return ft::pair<T1, T2>(t, u);
};

__FT_CONTAINERS_END_NAMESPACE

#endif //PAIR
