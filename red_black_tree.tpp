/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    red_black_tree.tpp                                 :+:      :+:    :+:    #
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
#include "iterator.tpp"
#include "type_traits.tpp"
#include "algorithm.tpp"
#include <set>
//std::set

#ifndef FT_CONTAINERS_RED_BLACK_TREE_TPP
# define FT_CONTAINERS_RED_BLACK_TREE_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

/*https://www.programiz.com/dsa/red-black-tree
Red-Black tree is a self-balancing binary search tree in which each node contains an extra bit for
 denoting the color of the node, either red or black.

A red-black tree satisfies the following properties:

Red/Black Property: Every node is colored, either red or black.
Root Property: The root is black.
Leaf Property: Every leaf (NIL) is black.
Red Property: If a red node has children then, the children are always black.
Depth Property: For each node, any simple path from this node to any of its descendant leaf
 has the same black-depth (the number of black nodes).*/

/*==================================================================================*/

/*red black tree of map*/
template< class Key, class Compare, class Allocator >
struct RedBlackTree {

private:

    typedef RedBlackTree< Key, Compare, Allocator>  _self;
    enum Color {RED, BLACK};
    static Allocator                                _alloc;
    static Compare                                  _comp;

    /* struct of set*/
    struct Node{

        Key         *_Key;
        Color       _Color;
        Node        *_LeftChild;
        Node        *_RightChild;
        Node        *_Parent;

        Node(){};
        explicit Node( Key key) : _Color(RED), _LeftChild(nullptr),_RightChild(nullptr), _Parent(nullptr)
        {
            _alloc.construct(_Key, key);
        };

        ~Node()
        {
            _alloc->destroy(_Key);
        };

    };

    Node*                                           _root;



/*
*====================================================================================
*|                                      Iterator                                    |
*====================================================================================
*/

protected:

    struct iterator : public std::iterator<std::random_access_iterator_tag,
                                            Key, Key, const Key*, Key > {
    private:
        Node*   It;
    public:
        iterator(){};
        iterator( const iterator& other ) : It(other){};

    };

/*
*====================================================================================
*|                                     Member Type                                  |
*====================================================================================
*/

protected:

    typedef Key                                             key_types;
    typedef key_types                                       value_type;
    typedef std::size_t                                     size_type;
    typedef std::ptrdiff_t                                  difference_type;
    typedef Compare                                         key_compare;
    typedef key_compare                                     value_compare;
    typedef value_type&                                     reference;
    typedef const value_type&                               const_reference;
    typedef Allocator                                       allocator_type;
    typedef typename Allocator::pointer                     pointer;
    typedef typename Allocator::const_pointer               const_pointer;
    typedef ft::reverse_iterator<iterator>                  reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:

    RedBlackTree() { __INFOMF__ _root = nullptr; };

    explicit RedBlackTree( const Compare& comp, const Allocator& alloc = Allocator() )
    { __INFOMF__
        _alloc = alloc;
        _comp = comp;
        _root = nullptr;
    };

    template< class InputIt >
    RedBlackTree( InputIt first, InputIt last, const Compare& comp, const Allocator& alloc )
    { __INFOMF__
        _alloc = alloc;
        _comp = comp;
        _root = nullptr;
        insert( first, last );
    };//assigne pointerdelte les double

    RedBlackTree( const _self& other ) : _root(other._root)
    {__INFOMF__
        _alloc = other._alloc;
        _comp = other._comp;
        insert( other.beging(), other.end() );
    };//assigne pointerdelte les double

    virtual ~RedBlackTree() {__INFOMF__ clear(); __INFOMFNL__};

    /*Copy assignment operator. Replaces the contents with a copy of the contents of other.*/
    RedBlackTree& operator=( const _self& other )
    {
        clear();
        _alloc = other._alloc;
        _comp = other._comp;
        insert( other.beging(), other.end() );
        return *this;
    };

    /*Returns the allocator associated with the container.*/
    allocator_type get_allocator() const{ return allocator_type(); }

/*
*====================================================================================
*|                                      Iterator                                    |
*====================================================================================
*/

public:

    iterator                begin()                 {__INFOIT__ return _root->_Key; };
    const_iterator          begin()         const   {__INFOIT__ return _root->_Key; };
    iterator                end()                   {__INFOIT__ return _root->_Key; };
    const_iterator          end()           const   {__INFOIT__ return _root->_Key;; };
    reverse_iterator        rbegin()                {__INFOIT__ return reverse_iterator (end()); };
    reverse_iterator        rend()                  {__INFOIT__ return reverse_iterator (begin()); };
    const_reverse_iterator  rbegin()        const   {__INFOIT__ return reverse_iterator (end()); };
    const_reverse_iterator  rend()          const   {__INFOIT__ return reverse_iterator (begin()); };


/*
*====================================================================================
*|                                     Capacity                                     |
*====================================================================================
*/

public:

    /*Checks if the container has no elements, i.e. whether begin() == end().*/
    bool        empty()     const   {__INFOCA__ return begin() == end(); };

    /*Returns the number of elements in the container,
     * i.e. std::distance(begin(), end()).*/
    size_type   size()      const   {__INFOCA__ return (end() - begin()); };

    /*Returns the maximum number of elements the container is able to
     * hold due to system or library implementation limitations, i.e.
     * std::distance(begin(), end()) for the largest container.*/
    size_type   max_size()  const
    {__INFOCA__ return std::numeric_limits<size_type>::max() / sizeof(value_type); };

/*
*====================================================================================
*|                                    Modifiers                                     |
*====================================================================================
*/


public:

    /*Erases all elements from the container. After this call, size() returns zero.
     * Invalidates any references, pointers, or iterators referring to contained elements.
     * Any past-the-end iterators are also invalidated.*/
    void            clear(){__INFOMO__ erase(begin(), end()); __INFOMONL__};

    /* inserts value.
     * Returns a pair consisting of an iterator to the inserted element (or to the element
     * that prevented the insertion) and a bool value set to true if and only if the insertion took place.*/
    ft::pair<iterator, bool>    insert( const value_type& value )
    {__INFOMO__

        __INFOMONL__
    };

    /*
     * inserts value in the position as close as possible to the position just prior to pos.
     * Returns an iterator to the inserted element, or to the element that prevented the insertion.
     */
    iterator                    insert( iterator pos, const value_type& value )
    {__INFOMO__


        return pos;
    };

    /*Inserts elements from range [first, last). If multiple elements in the range have keys
     * that compare equivalent, it is unspecified which element is inserted
     * O(N·log(size() + N)), where N is the number of elements to insert.*/
    template <class InputIt>
    iterator                    insert(InputIt first, InputIt last)
    {__INFOMO__

        Select_Input(  pos, first, last )

        __INFOMONL__
        return ;
    };

private:


    /*
    if forward, bidirectional or random-access iterators,
    the copy constructor of T is only called N  times, and
    no reallocation occurs.*/
    template <class InputIt>
    void        Select_Input(   const_iterator pos,
                                typename ft::enable_if<ft::is_random_access_iterator
                                    <typename ft::iterator_traits_if
                                    <InputIt, !is_integral
                                    <InputIt>::value>::iterator_category>::value, InputIt>::type first,
                                InputIt last )
    {__INFOMF__

        try{
            std::uninitialized_copy(first, last, Pos);
        }
        catch (...)
        {

            throw;
        }

        __INFOMFNL__};

    /* otherwise (first and last are just input iterators),
      the copy constructor of T is called O(N) times, and
      reallocation occurs O(log N) times.*/
    template< class InputIt >
    void        Select_Input(   const_iterator pos,
                                typename ft::enable_if<ft::is_input_iterator
                                    <typename ft::iterator_traits_if
                                    <InputIt, !ft::is_integral
                                    <InputIt>::value>::iterator_category>::value, InputIt>::type first,
                                InputIt last )
    {__INFOMF__

        (void)pos;
        for ( ; first != last; ++first)
            insert( *first );

        __INFOMFNL__};



public:

    /*Removes the element at pos
     * Iterator following the last removed element.*/
    iterator        erase(iterator pos)
    {__INFOMO__
        if (pos != end())
            std::copy(pos + 1, end(), pos);

        __INFOMONL__
        return pos;
    };

    /*Removes the elements in the range [first, last).
     * Iterator following the last removed element.*/
    iterator        erase(iterator first, iterator last)
    {__INFOMO__

        if ( first && last && (last - first) > 0 )
        {

        }

        __INFOMONL__
        return first;
    };

    /*Removes the element (if one exists) with the key equivalent to key.
     * Number of elements removed (0 or 1).
     * Any exceptions thrown by the Compare object.*/
    iterator        erase(const Key& key )
    {__INFOMO__

        __INFOMONL__
        return pos;
    };

/*
*====================================================================================
*|                                  Lookup                                          |
*====================================================================================
*/

    /*Returns the number of elements with key that compares equivalent to the specified argument.
     * Returns the number of elements with key key. This is either 1 or 0 since this container
     * does not allow duplicates.*/
    size_type count( const Key& key ) const{

    };

    /*Finds an element with key equivalent to key.
     * Iterator to an element with key equivalent to key. If no such element is found,
     * past-the-end (see end()) iterator is returned.*/
    iterator find( const Key& key ){

    };
    const_iterator find( const Key& key ) const{

    };


    /* Returns a range containing all elements with the given key in the container. The range is
     * defined by two iterators, one pointing to the first element that is not less than key and
     * another pointing to the first element greater than key. Alternatively, the first iterator
     * may be obtained with lower_bound(), and the second with upper_bound().
     * 1,2) Compares the keys to key.*/
    std::pair<iterator,iterator> equal_range( const Key& key ){

    };

    std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const{

    };

    /*Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
     * Iterator pointing to the first element that is not less than key.
     * If no such element is found, a past-the-end iterator (see end()) is returned.*/
    iterator lower_bound( const Key& key ){

    };

    const_iterator lower_bound( const Key& key ) const{

    };

    /*Returns an iterator pointing to the first element that is greater than key.
     * Iterator pointing to the first element that is greater than key.
     * If no such element is found, past-the-end (see end()) iterator is returned.*/
    iterator upper_bound( const Key& key ){

    };

    const_iterator upper_bound( const Key& key ) const{

    };

    /*Returns the function object that compares the keys, which is a copy of
     * this container's constructor argument comp. It is the same as value_comp.*/
    key_compare key_comp() const{

    };

    /*Returns the function object that compares the values. It is the same as key_comp.*/
    value_compare value_comp() const{

    };
/*
*====================================================================================
*|                             Private Membre fonction                              |
*====================================================================================
*/

private:

    Color getColor(Node *&node) {
        if (node == nullptr)
            return BLACK;
        return node->_Color;
    };

    void setColor(Node *&node, Color color) {
        if (node != nullptr)
            node->_Color = color;
    };

    iterator upper_bound( const Key& key ){

        if (root != nullptr) {
            if (node->_Key < root->_Key) {
                root->_LeftChild = insertBST(root->_LeftChild, node);
                root->_LeftChild->parent = root;
            } else if (node->_Key > root->_Key) {
                root->right = insertBST(root->right, node);
                root->right->parent = root;
            }
            return root;
        }
        return node;
    }

/*
*====================================================================================
*|                                 Non Membre fonction                              |
*====================================================================================
*/

/*Checks if the contents of lhs and rhs are equal,
 * that is, they have the same number of elements and each element
 * in lhs compares equal with the element in rhs at the same position.*/
    template< class Key, class Compare, class Allocator >
    inline bool operator== ( const ft::RedBlackTree< Key, Compare, Allocator >& lhs,
                             const ft::RedBlackTree< Key, Compare, Allocator >& rhs )
    {__INFONM__
        if (lhs.size() == rhs.size())
            return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        return false;
    };

    template< class Key, class Compare, class Allocator >
    inline bool operator!=( const ft::RedBlackTree< Key, Compare, Allocator >& lhs,
                            const ft::RedBlackTree< Key, Compare, Allocator >& rhs ){__INFONM__ return !(lhs == rhs); };

/*3-6) Compares the contents of lhs and rhs lexicographically.
 * The comparison is performed
 * by a function equivalent to std::lexicographical_compare.*/
    template< class Key, class Compare, class Allocator >
    inline bool operator<( const ft::RedBlackTree< Key, Compare, Allocator >& lhs,
                           const ft::RedBlackTree< Key, Compare, Allocator >& rhs )
    {__INFONM__
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                           rhs.begin(), rhs.end());
    };

    template< class Key, class Compare, class Allocator >
    inline bool operator<=( const ft::RedBlackTree< Key, Compare, Allocator >& lhs,
                            const ft::RedBlackTree< Key, Compare, Allocator >& rhs ) {__INFONM__ return !(rhs < lhs); };

    template< class Key, class Compare, class Allocator >
    inline bool operator>( const ft::RedBlackTree< Key, Compare, Allocator >& lhs,
                           const ft::RedBlackTree< Key, Compare, Allocator >& rhs )  {__INFONM__ return rhs < lhs; };

    template< class Key, class Compare, class Allocator >
    inline bool operator>=( const ft::RedBlackTree< Key, Compare, Allocator >& lhs,
                            const ft::RedBlackTree< Key, Compare, Allocator >& rhs ) {__INFONM__ return !(lhs < rhs); };

__FT_CONTAINERS_END_NAMESPACE

namespace std {
    template< class Key, class Compare, class Allocator >
    inline void swap(ft::RedBlackTree< Key, Compare, Allocator >& lhs, ft::RedBlackTree< Key, Compare, Allocator > &rhs)
    {__INFOMO__ lhs.swap(rhs); __INFOMONL__ };
}

#endif //FT_CONTAINERS_RED_BLACK_TREE_TPP
