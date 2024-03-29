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

#include "../Include/Unit_test.hpp"

int utility_test(){

    //Test ft::pair https://en.cppreference.com/w/cpp/utility/pair/pair

    std::cout << "####  Test >> ft::paire  ####" << std::endl;

    ft::pair<int, float> p1;
    std::cout << "(1) Value-initialized: " << "(" << p1.first << ", " << p1.second << ")" << std::endl;


    ft::pair<int, double> p2(42, 3.1415);
    std::cout << "(2) Initialized with two values: " << "(" << p2.first << ", " << p2.second << ")" << std::endl;

    ft::pair<char, int> p4(p2);
    std::cout << "(2) Initialized with two values: " << "(" << p2.first << ", " << p2.second << ")" << std::endl;

    ft::pair<int, std::string> v(23, "coucou23");
    ft::pair<int, std::string> v1(22, "coucou22");
    ft::pair<int, std::string> v2(23, "coucou23encore");
    std::cout << ((v < v1) ? v.second : v1.second) << std::endl;
    std::cout << ((v > v1) ? v.second : v1.second) << std::endl;
    std::cout << ((v == v2) ? v.second : v2.second) << std::endl << std::endl;

    //Test ft::make_paire https://en.cppreference.com/w/cpp/utility/pair/make_pair

    std::cout << "####  Test >> ft::make_paire  ####" << std::endl;
    int n = 1;
    int a[5] = {1, 2, 3, 4, 5};

    // build a pair from two ints
    ft::pair<int, int> p5 = ft::make_pair(n, a[1]);
    std::cout << "The value of p1 is "
              << "(" << p5.first << ", " << p5.second << ")\n";

    // build a pair from a reference to int and an array (decayed to pointer)
    ft::pair<int, int*> p6 = ft::make_pair(n, a);
    n = 7;
    std::cout << "The value of p2 is "
              << "(" << p6.first << ", " << p6.second[1] << ")\n";


    return (0);
}
