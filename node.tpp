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

#ifndef FT_CONTAINERS_NODE_TPP
#define FT_CONTAINERS_NODE_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    enum Color { RED, BLACK };

    template< class Key >
    struct NodeBase {

    private:
        typedef NodeBase<Key> _self;
        Key         *_Key;
        Color       _Color;
        NodeBase    *_LeftChild;
        NodeBase    *_RightChild;
        NodeBase    *_Parent;
        std::size_t _Size;


    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

    protected:

        NodeBase() : _Key(nullptr), _Color(BLACK), _LeftChild(nullptr),
                     _RightChild(nullptr), _Parent(nullptr), _Size(0){};

        explicit NodeBase(Key* key, Color color) : _Key(key), _Color(color), _LeftChild(nullptr),
                                                _RightChild(nullptr), _Parent(nullptr), _Size(0) { };

        NodeBase(const _self &other) : _Color(other._Color), _LeftChild(other._LeftChild),
                                        _RightChild(other._RightChild), _Parent(other._Parent) {
            _Key = Key(other.key);
        };

        ~NodeBase() {};

    };

    template< class Key, class T = void >
    struct Node : public NodeBase< Key > {
        //add classe T to construct
    };

    template< class Key >
    struct Node< Key > : public NodeBase< Key > {

    };


__FT_CONTAINERS_END_NAMESPACE


#endif //FT_CONTAINERS_NODE_TPP
