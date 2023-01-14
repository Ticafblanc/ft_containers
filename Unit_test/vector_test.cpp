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

#include "Unit_test.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <iterator>

int main(){
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::vector<bool>               b;
    std::vector<int>            i(200,45);
    std::vector<int>::iterator it;
    it.base();
    ft::vector<int>::iterator fit;
    fit.base();

//    //ft::vector<int>::iterator ite = i.end();
//    ft::vector<int>            fi(200,45);
//    ft::vector<int>::iterator fit = fi.begin();
//    std::cout << i.max_size() << std::endl;
//    std::cout << fi.max_size() << std::endl;
    size_t s = 99999999;
    int    c = 0;
//    std::istream_iterator<std::vector<int>, std::vector<int>::difference_type> in();
//    in = i.begin();

//    ft::vector<char>            ft_void;
//    std::vector<char>           std_void;
//    ft::vector<int>             ft_alloc(std::allocator<int>);
//    std::vector<int>            std_alloc(std::allocator<int>);
    ft::vector<int>          ft_count(s, c);
    std::cout << *(ft_count.end() - 1) << std::endl;
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    std::chrono::system_clock::time_point starts = std::chrono::system_clock::now();
    std::cout << std::endl;
    std::vector<int>         std_count(s, c);
    std::cout << (std_count.size()) << std::endl;
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - starts).count() << "ms" << std::endl;

//    int i1 = 200;
//    int i2= 45;
    ft::vector<int>             ft_integrl(200, 45);
    std::vector<int>             std_integral(200, 45);
//    ft::vector<int>             ft_integralv(i1, i2);
//    std::vector<int>             std_integralv(i1, i2);
//    std::vector<int>            ft_input = std::vector<int >(it, it + 200);
   // ft::vector<int>             std_input = ft::vector<int>(it, it + 200);


	std::cout << std::endl;
//    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
//            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    return 0;
}