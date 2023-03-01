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


int map_test(){
    ft::vector<int> v;
    ft::map<int, int> mp;

    for (int i = 0, j = 10; i < COUNT ; ++i, ++j) {
        mp.insert(ft::make_pair(i, j));
    }
    ft::map<int, int> mp2(mp.begin(), mp.end());
    ft::map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < COUNT ; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    ft::pair<ft::map<int, int>::iterator , bool> pair = mp.insert(ft::make_pair(7, 7));
    it = mp.begin();
    v.push_back(it->first);
    v.push_back(it->second);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second);
    mp.insert(ft::make_pair(9, 9));
    ft::pair<ft::map<int, int>::iterator , bool> pair2 = mp.insert(ft::make_pair(9, 9));
    ft::map<int, int>::iterator it2 = pair.first;
    v.push_back(it2->first);
    v.push_back(it2->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second);
    for (int i = 0, j = 0; i < COUNT ; ++i, ++j) {
        mp.insert(ft::make_pair(i, j));
    }
    ft::map<int, int>::iterator it3 = mp.begin();
    for (; it3 != mp.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    v.push_back(mp.size());
    v.push_back(mp.erase(3));
    for (int i = 0, j = 0; i < COUNT ; ++i, ++j)
        mp.insert(ft::make_pair(i, j));
    it = mp.begin();
    v.push_back(it->first);
    v.push_back(mp.erase(-5));
    v.push_back(mp.size());
    v.push_back(mp.erase(0));
    v.push_back(mp.size());
    it = mp.begin();
    v.push_back(it->first);
    ft::map<int,  int>::iterator it4 = mp.begin();
    for (; it4 != mp.end(); it4 = mp.begin())
        mp.erase(it4->first);
    v.push_back(mp.erase(30));
    v.push_back(mp.size());
    for (int i = 0, j = 0; i < COUNT ; ++i, ++j)
        mp2.insert(ft::make_pair(i, j));
    mp2.erase(2);
    mp2.erase(7);
    it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    ft::vector<int>::iterator It = v.begin();
    for (std::size_t i = 0; i < v.size(); ++i, ++It) {
        std::cout<< *It << std::endl;
    }
    return 0;
}