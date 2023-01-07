/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    type_traits.tpp                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 19:01:51 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/27 19:01:56 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include "ft_containers.hpp"

#ifndef FT_CONTAINERS_TYPE_TRAITS_TPP
# define FT_CONTAINERS_TYPE_TRAITS_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    //ft::enable_if

/*If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.

This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts, in particular for conditionally
 removing functions from the candidate set based on type traits, allowing separate function overloads or specializations
 based on those different type traits.

std::enable_if can be used in many forms, including:

    as an additional function argument (not applicable to operator overloads)
    as a return type (not applicable to constructors and destructors)
    as a class template or function template parameter

The behavior of a program that adds specializations for enable_if is undefined.*/
struct true_type {
};

struct false_type {
};

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };


    //ft::is_integral

/*Checks whether T is an integral type. Provides the member constant value which is equal to true, if T is the type
 * bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long long, or any implementation-
 * defined extended integer types, including any signed, unsigned, and cv-qualified variants. Otherwise, value is equal
 * to false.

The behavior of a program that adds specializations for is_integral or is_integral_v (since C++17) is undefined.
Template parameters
T 	- 	a type to check */


template <typename>
struct is_integral { static const bool value = false; };

template <>
struct is_integral<bool> { static const bool value = true; };

template <>
struct is_integral<char> { static const bool value = true; };

template <>
struct is_integral<short> { static const bool value = true; };

template <>
struct is_integral<int> { static const bool value = true; };

template <>
struct is_integral<long> { static const bool value = true; };

template <>
struct is_integral<long long> { static const bool value = true; };

template <>
struct is_integral<unsigned char> { static const bool value = true; };

template <>
struct is_integral<unsigned short> { static const bool value = true; };

template <>
struct is_integral<unsigned int> { static const bool value = true; };

template <>
struct is_integral<unsigned long> { static const bool value = true; };

template <>
struct is_integral<unsigned long long> { static const bool value = true; };

//supplement

template <class T>
struct id { typedef T type; }; //typedef meta


__FT_CONTAINERS_END_NAMESPACE

#endif //FT_CONTAINER_TYPE_TRAITS_TPP
