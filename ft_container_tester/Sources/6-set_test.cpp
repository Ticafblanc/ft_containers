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


int set_test(){
    ft::vector<int> v;
    ft::set<int> mp;

    for (int i = 0; i < COUNT ; ++i) {
        mp.insert(i);
    }
    ft::set<int> mp2(mp.begin(), mp.end());
    ft::set<int>::iterator it = mp2.begin();
    for (int i = 0; i < COUNT ; ++i, it++) {
        v.push_back(*it);
    }
    ft::pair<ft::set<int>::iterator , bool> pair = mp.insert(7);
    it = mp.begin();
    v.push_back(*it);
    mp.insert(9);
    ft::pair<ft::set<int>::iterator , bool> pair2 = mp.insert(9);
    ft::set<int>::iterator it2 = pair.first;
    v.push_back(*it2);

    for (int i = 0; i < COUNT ; ++i) {
        mp.insert(i);
    }
    ft::set<int>::iterator it3 = mp.begin();
    for (; it3 != mp.end(); ++it3) {
        v.push_back(*it3);
    }
    v.push_back(mp.size());
    v.push_back(mp.erase(3));
    for (int i = 0; i < COUNT ; ++i)
        mp.insert(i);
    it = mp.begin();
    v.push_back(*it);
    v.push_back(mp.erase(-5));
    v.push_back(mp.size());
    v.push_back(mp.erase(0));
    v.push_back(mp.size());
    it = mp.begin();
    v.push_back(*it);
    ft::set<int>::iterator it4 = mp.begin();
    for (; it4 != mp.end(); it4 = mp.begin())
        mp.erase(*it4);
    v.push_back(mp.erase(30));
    v.push_back(mp.size());
    for (int i = 0; i < COUNT ; ++i)
        mp2.insert(i);
    mp2.erase(2);
    mp2.erase(7);
    it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(*it3);
    }
    ft::vector<int>::iterator It = v.begin();
    for (std::size_t i = 0; i < v.size(); ++i, ++It) {
        std::cout<< *It << std::endl;
    }
    return 0;
}