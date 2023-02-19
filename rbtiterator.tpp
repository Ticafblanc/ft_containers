/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rbtiterator.tpp                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 12:26:02 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/29 12:26:04 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include "ft_containers.hpp"
#include "red_black_tree.tpp"

#ifndef FT_CONTAINERS_RBTITERATOR_TPP
#define FT_CONTAINERS_RBTITERATOR_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    template< class Key, class Node >
    struct rbtiterator : public std::iterator<std::bidirectional_iterator_tag,
                                            Key, Key, const Key *, Key> {
    private:

        typedef rbtiterator< Key, Node> _self;
        typedef RedBlackTree< Key, Node> _rbt;
        Node*                           _node;

    /*
    *====================================================================================
    *|                                     Member Type                                  |
    *====================================================================================
    */

    protected:

        typedef Key             key_types;
        typedef key_types       value_type;
        typedef Node            node_type;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

    public:

        rbtiterator() : _node(nullptr){};

        explicit rbtiterator(Node* tmp) : _node(tmp) {};

        rbtiterator(const _self &other) : _node(other._node) {};

        ~rbtiterator(){};

        _self& operator=( const _self& other){
            _node = other._node;
            return *this;
        };

        Key& operator*() const { return *(_node->_Key); }
        Key* operator->() const { return &(operator*()); }

        _self& operator++() {

            return *this;
        };

        _self operator++(int) {
            _self Tmp = *this;

            return Tmp;
        };

        _self& operator--() {
            _Rbt::predecessor(_node);
            return *this;
        };

        _self  operator--(int) {
            _self Tmp = *this;
            _Rbt::predecessor(_node);
            return Tmp;
        };

    };
__FT_CONTAINERS_END_NAMESPACE


#endif //FT_CONTAINERS_RBTITERATOR_TPP
