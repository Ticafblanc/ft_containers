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


int vector_test(){
    ft::vector<int> v;
    ft::vector<int> vv;
    ft::vector<int> vector(3, 3);
    ft::vector<int> tmp(1000, 4);
    ft::vector<int> tmp2(tmp.begin(), tmp.end());

    v.push_back(tmp2.size());
    v.push_back(tmp2.capacity());
    for (size_t i = 0; i < tmp.size(); ++i)
        v.push_back(tmp2[i]);
    tmp.assign(2600 , 1);
    vector.assign(4200 , 1);
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    try { vv.insert(vv.begin(), v.begin(), v.end());
    }
    catch (...) {
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
    for (int i = 0; i < COUNT; ++i)
        vector.push_back(i);
    v.push_back(*(vector.erase(vector.begin() + 8)));
    v.push_back(*(vector.begin() + 82));
    v.push_back(vector.size());
    ft::vector<int>::iterator it = v.begin();
    for (std::size_t i = 0; i < v.size(); ++i, ++it) {
        std::cout<< *it << std::endl;
    }

    return 0;
}