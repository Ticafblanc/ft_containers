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

int main(){
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::vector<int>            i(200,45);
    std::vector<int>::iterator it = i.begin();
    std::vector<int>::iterator ite = i.end();

//    ft::vector<char>            ft_void;
//    std::vector<char>           std_void;
//    ft::vector<int>             ft_alloc(std::allocator<int>);
//    std::vector<int>            std_alloc(std::allocator<int>);
//    ft::vector<double>          ft_count(5, 5.5);
//    std::vector<double>         std_count(5, 5.5);
    ft::vector<int>             ft_integral(200, 45);
    std::vector<int>             std_integral(200, 45);
    std::vector<std::vector<int> >            ft_input(it,it + 200);
    ft::vector<std::vector<int> >             std_inputit(it, it + 200);
//    ft::vector<std::string>          ft_is_integral(5, 45.67,std::allocator<std::string>());
//    std::vector<std::string>         std_is_integral(5, 45.67,std::allocator<std::string>());


	std::cout << std::endl;
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    return 0;
}