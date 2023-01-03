/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    algorithm.tpp                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 20:55:25 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/26 20:55:30 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include <ft_containers.hpp>

#ifndef FT_CONTAINERS_ALGORITHM_TPP
# define FT_CONTAINERS_ALGORITHM_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    //ft::equal
/*Parameters
first1, last1 	- 	the first range of the elements to compare
first2, last2 	- 	the second range of the elements to compare
policy 	- 	the execution policy to use. See execution policy for details.
p 	- 	binary predicate which returns true if the elements should be treated as equal.

The signature of the predicate function should be equivalent to the following:

bool pred(const Type1 &a, const Type2 &b);

While the signature does not need to have const &, the function must not modify the objects passed to it and must be
 able to accept all values of type (possibly const) Type1 and Type2 regardless of value category (thus, Type1 & is not
 allowed, nor is Type1 unless for Type1 a move is equivalent to a copy (since C++11)).
The types Type1 and Type2 must be such that objects of types InputIt1 and InputIt2 can be dereferenced and then
 implicitly converted to Type1 and Type2 respectively.*/

/*Return value
If the length of the range [first1, last1) does not equal the length of the range [first2, last2), returns false

If the elements in the two ranges are equal, returns true.

Otherwise returns false.*/

//Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)),
// and false otherwise.

template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!(*first1 == *first2))
        {
            return false;
        }
    }
    return true;
}

template< class InputIt1, class InputIt2,class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!p(*first1, *first2))
        {
            return false;
        }
    }
    return true;
}



    //ft::lexicographical_compare

/*Parameters
first1, last1 	- 	the first range of elements to examine
first2, last2 	- 	the second range of elements to examine
policy 	- 	the execution policy to use. See execution policy for details.
comp 	- 	comparison function object (i.e. an object that satisfies the requirements of Compare) which return
 true if the first argument is less than the second.

The signature of the comparison function should be equivalent to the following:

bool cmp(const Type1 &a, const Type2 &b);

While the signature does not need to have const &, the function must not modify the objects passed to it and must be
 able to accept all values of type (possibly const) Type1 and Type2 regardless of value category (thus, Type1 & is not
 allowed, nor is Type1 unless for Type1 a move is equivalent to a copy (since C++11)).
The types Type1 and Type2 must be such that objects of types InputIt1 and InputIt2 can be dereferenced and then
 implicitly converted to both Type1 and Type2.*/

/*Return value
true if the first range is lexicographically less than the second, otherwise false.*/

/*Exceptions

The overloads with a template parameter named ExecutionPolicy report errors as follows:

    If execution of a function invoked as part of the algorithm throws an exception and ExecutionPolicy is
    one of the standard policies, std::terminate is called. For any other ExecutionPolicy, the behavior is
    implementation-defined.
    If the algorithm fails to allocate memory, std::bad_alloc is thrown. */

//Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).

// Elements are compared using operator<.

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2 )
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
    {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
    return (first1 == last1) && (first2 != last2);
}

//Elements are compared using the given binary comparison function comp.

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2, Compare comp )
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
    {
        if (comp(*first1, *first2))
            return true;
        if (comp(*first2, *first1))
            return false;
    }
    return (first1 == last1) && (first2 != last2);
}

__FT_CONTAINERS_END_NAMESPACE

#endif //FT_CONTAINER_LEXICOGRAPHICAL_COMPARE_TPP
