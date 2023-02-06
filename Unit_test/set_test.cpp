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
#include <set>
#include <map>
#include <iostream>
#include <iterator>
#include "../stack.tpp"

int main(){
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();


    std::set<int> test;
    test.insert(4);
    test.insert(4);
    test.insert(4);
    test.insert(4);
    test.insert(4);

    for(int i= 0; i < 5 ; ++i){
        std::cout << *test.find(i)<<std::endl;
    }

	std::cout << std::endl;
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    return 0;
}