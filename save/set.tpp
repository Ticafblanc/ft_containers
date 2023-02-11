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
#include "vector.tpp"

#ifndef FT_CONTAINERS_SET_TPP
# define FT_CONTAINERS_SET_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

template< class Key, class Compare, class Allocator >
class setBase : ft::vector<Node<Key> >{

private:
    typedef setBase< Key, Compare, Allocator >                         self;
    typedef ft::vector<Node<Key> >                                     Base;

public:
    setBase() : Base(){}
    /*Solved allocator conflict*/
    explicit setBase(const Allocator& alloc) : Base(alloc) {}

    ~setBase() {};

private:
    Compare Comp;
};


template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set : private setBase< Key, Compare, Allocator >{

private:
    typedef setBase< Key, Compare, Allocator >                         Base;
    typedef set< Key, Compare, Allocator >                             Self;
/*
*====================================================================================
*|                                     Member Type                                  |
*====================================================================================
*/

public:
    typedef Key                                         key_types;
    typedef key_types                                   value_type;
    typedef std::size_t                                 size_type;
    typedef std::ptrdiff_t                              difference_type;
    typedef Compare                                     key_compare;
    typedef key_compare                                 value_compare;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef Allocator                                   allocator_type;
    typedef typename Allocator::pointer                 pointer;
    typedef typename Allocator::const_pointer           const_pointer;
    typedef value_type*                                 iterator;
    typedef const value_type*                           const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/*Parameters
alloc	-	allocator to use for all memory allocations of this container
comp	-	comparison function object to use for all comparisons of keys
first, last	-	the range to copy the elements from
other	-	another container to be used as source to initialize the elements of the container with
init	-	initializer list to initialize the elements of the container with
Type requirements
-InputIt must meet the requirements of LegacyInputIterator.
-Compare must meet the requirements of Compare.
-Allocator must meet the requirements of Allocator.
Complexity
1) Constant
2) N log(N) where N = std::distance(first, last) in general, linear in N if the range is already sorted by value_comp().
3) Linear in size of other
4) Constant. If alloc is given and alloc != other.get_allocator(), then linear.
5) N log(N) where N = init.size() in general, linear in N if init is already sorted by value_comp().
Exceptions
Calls to Allocator::allocate may throw.*/

    /*1Constructs an empty container.*/
    set() : Base() {}

};

__FT_CONTAINERS_END_NAMESPACE

#endif //FT_CONTAINERS_SET_TPP
