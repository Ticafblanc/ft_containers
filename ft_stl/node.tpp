/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    node.tpp                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 12:26:02 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/29 12:26:04 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include "ft_containers.hpp"
#include "utility.tpp"

#ifndef FT_CONTAINERS_NODE_TPP
#define FT_CONTAINERS_NODE_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    enum Color { RED, BLACK };

    template< class Key >
    struct nodeSet {

        typedef nodeSet<Key> _self;
        Key         *_Key;
        Color       _Color;
        nodeSet    *_LeftChild;
        nodeSet    *_RightChild;
        nodeSet    *_Parent;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

        explicit nodeSet(Color color, nodeSet* _nul)
                : _Key(nullptr), _Color(color), _LeftChild(_nul),
                _RightChild(_nul), _Parent(_nul){};

        ~nodeSet() {};

    /*
    *====================================================================================
    *|                                    Modifiers                                     |
    *====================================================================================
    */

        void        swap(_self& other)
        {
            std::swap(_Key, other._Key);
            std::swap(_Color, other._Color);
            std::swap(_LeftChild, other._LeftChild);
            std::swap(_RightChild, other._RightChild);
            std::swap(_Parent, other._Parent);
        };
    };

__FT_CONTAINERS_END_NAMESPACE

namespace std {
    template<class Key>
    inline void swap(ft::nodeSet<Key>&lhs, ft::nodeSet<Key> &rhs)
    { lhs.swap(rhs);  };
};

#endif //FT_CONTAINERS_NODE_TPP
