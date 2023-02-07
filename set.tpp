/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    set.tpp                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 21:56:15 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/27 21:56:18 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include "ft_containers.hpp"
#include "red_black_tree.tpp"

#ifndef FT_CONTAINERS_SET_TPP
# define FT_CONTAINERS_SET_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set : private red_black_tree< Key, Compare, Allocator, void >{

private:
    typedef red_black_tree< Key, Compare, Allocator, void >                         Base;

/*
*====================================================================================
*|                                     Member Type                                  |
*====================================================================================
*/

public:

};

__FT_CONTAINERS_END_NAMESPACE

#endif //FT_CONTAINERS_SET_TPP
