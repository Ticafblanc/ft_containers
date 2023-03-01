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

#ifndef FT_CONTAINERS_UNIT_TEST_HPP
# define FT_CONTAINERS_UNIT_TEST_HPP

#include <iostream>
#include <chrono>
#include <deque>
#include <unistd.h>
#include <iostream>
#include <fstream>


#define MAX_RAM 4294967296
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
    #include "../vector.tpp"
    #include "../map.tpp"
    #include "../set.tpp"
    #include "../stack.tpp"
    #include "../type_traits.tpp"
    #include "../iterator.tpp"
    #include "../algorithm.tpp"
    #include "../utility.tpp"
#endif

int utility_test();

#endif //FT_CONTAINERS_UNIT_TEST_HPP
