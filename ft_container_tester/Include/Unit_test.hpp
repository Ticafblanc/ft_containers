/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unit_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 07:21:01 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/12/30 07:21:05 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef UNIT_TEST_HPP
# define UNIT_TEST_HPP

#include <iostream>
#include <deque>
#include <unistd.h>

#define MAX_RAM 4234545
#define BUFFER_SIZE 4096

struct Buffer
{
    int idx;
    char buff[BUFFER_SIZE];

};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))


#if REAL  //CREATE A REAL STL EXAMPLE
    #include <stack>
    #include <type_traits>
    #include <algorithm>
    #include <iterator>
    #include <utility>
    #include <vector>
    #include <map>
    #include <set>
    namespace ft = std;
#else
    #include "../../ft_stl/vector.tpp"
    #include "../../ft_stl/map.tpp"
    #include "../../ft_stl/set.tpp"
    #include "../../ft_stl/stack.tpp"
    #include "../../ft_stl/type_traits.tpp"
    #include "../../ft_stl/iterator.tpp"
    #include "../../ft_stl/algorithm.tpp"
    #include "../../ft_stl/utility.tpp"
#endif

int utility_test(void);
int type_traits(void);
int stack_test(void);
int vector_test(void);
int map_test(void);
int set_test(void);

#endif //FT_CONTAINERS_UNIT_TEST_HPP
