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
#include "node.tpp"

#ifndef FT_CONTAINERS_RBTITERATOR_TPP
#define FT_CONTAINERS_RBTITERATOR_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

template< class Key, class Node >
struct rbtiterator : public std::iterator<std::bidirectional_iterator_tag,
                                        Key, Key, const Key *, Key> {
private:

    typedef rbtiterator< Key, Node> _self;
    Node*                          _node;

/*
*====================================================================================
*|                                     Member Type                                  |
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
        if (_node->_RightChild){
            _node = _node->_RightChild;
            while (_node->_LeftChild)
                _node = _node->_LeftChild;
        }
        else {
            Node* Tnode = _node->_Parent;
            while (_node == Tnode->_RightChild) {
                _node = Tnode;
                Tnode = _node->_Parent;
            }
            if (_node->_RightChild != Tnode)
                _node = Tnode;
        }
        return *this;
    };

    _self operator++(int) {
        _self Tmp = *this;
        operator++();
        return Tmp;
    };

    _self& operator--() {
        if (_node->_LeftChild){
            _node = _node->_LeftChild;
            while (_node->_RightChild)
                _node = _node->_RightChild;
        }
        else {
            Node* Tnode = _node->_Parent;
            while (_node == Tnode->_LeftChild) {
                _node = Tnode;
                Tnode = _node->_Parent;
            }
            if (_node->_LeftChild != Tnode)
                _node = Tnode;
        }
        return *this;
    };

    _self  operator--(int) {
        _self Tmp = *this;
        operator--();
        return Tmp;
    };

};
__FT_CONTAINERS_END_NAMESPACE


#endif //FT_CONTAINERS_RBTITERATOR_TPP
