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

template< class Key, class Compare, class Allocator >
struct NodeBase {

private:
    typedef NodeBase<Key, Compare, Allocator> _self;
    Key         *_Key;
    Color       _Color;
    NodeBase    *_LeftChild;
    NodeBase    *_RightChild;
    NodeBase    *_Parent;
    Allocator   *_alloc;
    Compare     *_comp;

/*
*====================================================================================
*|                                     Member Type                                  |
*====================================================================================
*/

protected:

    typedef Key key_types;
    typedef key_types value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef key_compare value_compare;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef Allocator allocator_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

protected:

    NodeBase() {};

    explicit NodeBase(Key& key, Compare& comp, Allocator& alloc) : _Color(RED), _LeftChild(nullptr),
                                            _RightChild(nullptr), _Parent(nullptr) {
        _alloc = &alloc;
        _comp = &comp;
        _alloc->construct(_Key, key);

    };

    NodeBase(const _self &other) : _Color(other._Color), _LeftChild(other._LeftChild),
                                    _RightChild(other._RightChild), _Parent(other._Parent) {
        _alloc = &other._alloc;
        _comp = &other._comp;
        _alloc->construct(_Key, other._Key);

    };

    ~NodeBase() {
        _alloc->destroy(_Key);
    };

    Color getColor() { return _Color; };

    void setColor(Color color) { _Color = color; };

};

template< class Key, class Compare, class Allocator, class T = void >
struct Node : public NodeBase< Key, Compare, Allocator > {
    //add classe T to construct
};

template< class Key, class Compare, class Allocator >
struct Node< Key, Compare, Allocator > : public NodeBase< Key, Compare, Allocator > {

};


/*
*====================================================================================
*|                                 Non Membre fonction                              |
*====================================================================================
*/

template< class Key, class Compare, class Allocator >
inline bool operator<(const NodeBase< Key, Compare, Allocator >& lhs,
                      const NodeBase< Key, Compare, Allocator >& rhs) {
    return lhs._comp(lhs._Key, rhs._Key);
}

template< class Key, class Compare, class Allocator >
inline bool operator==(const NodeBase< Key, Compare, Allocator >& lhs,
                       const NodeBase< Key, Compare, Allocator >& rhs) {
    return !(rhs < lhs) && !(lhs < rhs);
}

template< class Key, class Compare, class Allocator >
inline bool operator!=(const NodeBase< Key, Compare, Allocator >& lhs,
                       const NodeBase< Key, Compare, Allocator >& rhs) {
    return !(lhs == rhs);
}

template< class Key, class Compare, class Allocator >
inline bool operator<=(const NodeBase< Key, Compare, Allocator >& lhs,
                       const NodeBase< Key, Compare, Allocator >& rhs) {
    return !(rhs < lhs);
}

template< class Key, class Compare, class Allocator >
inline bool operator>(const NodeBase< Key, Compare, Allocator >& lhs,
                      const NodeBase< Key, Compare, Allocator >& rhs) {
    return rhs < lhs;
}

template< class Key, class Compare, class Allocator >
inline bool operator>=(const NodeBase< Key, Compare, Allocator >& lhs,
                       const NodeBase< Key, Compare, Allocator >& rhs) {
    return !(lhs < rhs);
}

__FT_CONTAINERS_END_NAMESPACE

#endif //FT_CONTAINERS_NODE_TPP
