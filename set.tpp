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
#include "rbtiterator.tpp"
#include "iterator.tpp"

#ifndef FT_CONTAINERS_SET_TPP
# define FT_CONTAINERS_SET_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set : protected RedBlackTree< Key, Node< Key, Compare, Allocator >, Compare, Allocator > {

    private:

        typedef RedBlackTree< Key, Node< Key, Compare, Allocator >, Compare, Allocator > base;
        typedef set< Key, Compare, Allocator >                                           self;

    /*
    *====================================================================================
    *|                                     Member Type                                  |
    *====================================================================================
    */

    public:

        typedef Key                                                 key_types;
        typedef key_types                                           value_type;
        typedef std::size_t                                         size_type;
        typedef std::ptrdiff_t                                      difference_type;
        typedef Compare                                             key_compare;
        typedef key_compare                                         value_compare;
        typedef value_type &                                        reference;
        typedef const value_type &                                  const_reference;
        typedef Allocator                                           allocator_type;
        typedef typename Allocator::pointer                         pointer;
        typedef typename Allocator::const_pointer                   const_pointer;
        typedef rbtiterator< Key, Node< Key > > iterator;
        typedef const iterator                                      const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

    public:

        set() : base(){__INFOMF__};

        explicit set(const Compare &comp, const Allocator &alloc = Allocator()) : base(comp, alloc) {__INFOMF__};

        template<class InputIt>
        set(InputIt first, InputIt last, const Compare &comp, const Allocator &alloc) : base(comp, alloc)
        { __INFOMF__ insert(first, last); };

        set(const self &other) : base(other.base) {__INFOMF__ };//assigne pointerdelte les double

        ~set() {__INFOMF__  __INFOMFNL__};

        /*Copy assignment operator. Replaces the contents with a copy of the contents of others.*/
        self &operator=(const self &other) {
            this->base = other.base;
            return *this;
        };

        /*Returns the allocator associated with the container.*/
        allocator_type get_allocator() const { return allocator_type(); }

    /*
    *====================================================================================
    *|                                      Iterator                                    |
    *====================================================================================
    */

    public:

        iterator                begin()             {__INFOIT__ return iterator(base::_begin); };

        const_iterator          begin()     const   {__INFOIT__ return iterator(base::_begin); };

        iterator                end()               {__INFOIT__ return iterator(base::_end);};

        const_iterator          end()       const   {__INFOIT__ return iterator(base::_end); };

        reverse_iterator        rbegin()            {__INFOIT__ return reverse_iterator(end()); };

        reverse_iterator        rend()              {__INFOIT__ return reverse_iterator(begin()); };

        const_reverse_iterator  rbegin()    const   {__INFOIT__ return reverse_iterator(end()); };

        const_reverse_iterator  rend()      const   {__INFOIT__ return reverse_iterator(begin()); };

    /*
    *====================================================================================
    *|                                     Capacity                                     |
    *====================================================================================
    */

    public:

        /*Checks if the container has no elements, i.e. whether begin() == end().*/
        bool        empty()     const { __INFOCA__ return base::empty(); };

        /*Returns the number of elements in the container,
         * i.e. std::distance(begin(), end()).*/
        size_type   size()      const {__INFOCA__ return base::size(); };

        /*Returns the maximum number of elements the container is able to
         * hold due to system or library implementation limitations, i.e.
         * std::distance(begin(), end()) for the largest container.*/
        size_type   max_size()  const { __INFOCA__ return std::numeric_limits<size_type>::max() / sizeof(value_type); };

    /*
    *====================================================================================
    *|                                    Modifiers                                     |
    *====================================================================================
    */


    public:

        /*Erases all elements from the container. After this call, size() returns zero.
         * Invalidates any references, pointers, or iterators referring to contained elements.
         * Any past-the-end iterators are also invalidated.*/
        void clear() { __INFOMO__ base::clear();__INFOMONL__ };

        /* inserts value.
         * Returns a pair consisting of an iterator to the inserted element (or to the element
         * that prevented the insertion) and a bool value set to true if and only if the insertion took place.*/
        ft::pair<iterator, bool> insert(const value_type &value) {
            __INFOMO__

            __INFOMONL__
        };

        /*
         * inserts value in the position as close as possible to the position just prior to pos.
         * Returns an iterator to the inserted element, or to the element that prevented the insertion.
         */
        iterator insert(iterator pos, const value_type &value) {
            __INFOMO__


            return pos;
        };

        /*Inserts elements from range [first, last). If multiple elements in the range have keys
         * that compare equivalent, it is unspecified which element is inserted
         * O(N·log(size() + N)), where N is the number of elements to insert.*/
        template<class InputIt>
        iterator insert(InputIt first, InputIt last) {bool (*comp_func)(Key, Key)
            __INFOMO__

            Select_Input(pos, first, last)__INFOMONL__
            return;
        };


    public:

        /*Removes the element at pos
         * Iterator following the last removed element.*/
        iterator erase(iterator pos) {delete_func
            __INFOMO__
            if (pos != end())
                std::copy(pos + 1, end(), pos);

            __INFOMONL__
            return pos;
        };

        /*Removes the elements in the range [first, last).
         * Iterator following the last removed element.*/
        iterator erase(iterator first, iterator last) {
            __INFOMO__

            if (first && last && (last - first) > 0) {

            }

            __INFOMONL__
            return first;
        };

        /*Removes the element (if one exists) with the key equivalent to key.
         * Number of elements removed (0 or 1).
         * Any exceptions thrown by the Compare object.*/
        iterator erase(const Key &key) {
            __INFOMO__
            iterator mem = find(key);

            DelNode(mem);
            _alloc.deallocate(mem);
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
        size_type count(const Key &key) const {
            if(find(key) == end())
                return 0;
            return 1;
        };

        /*Finds an element with key equivalent to key.
         * Iterator to an element with key equivalent to key. If no such element is found,
         * past-the-end (see end()) iterator is returned.*/
        iterator find(const Key &key) {
            iterator troot = _root;/*forward*/
            iterator ritr = _root;/*return*/

            while (troot && *ritr != key) {
                if (!(*troot < key))
                    ritr = troot--;
                else
                    ritr = troot++;
            }
            return ritr;
        };

        const_iterator find(const Key &key) const {
            iterator troot = _root;/*forward*/
            iterator ritr = _root;/*return*/

            while (troot && *ritr != key) {
                if (!(*troot < key))
                    ritr = troot--;
                else
                    ritr = troot++;
            }
            return const_iterator(ritr);
        };


        /* Returns a range containing all elements with the given key in the container. The range is
         * defined by two iterators, one pointing to the first element that is not less than key and
         * another pointing to the first element greater than key. Alternatively, the first iterator
         * may be obtained with lower_bound(), and the second with upper_bound().
         * 1,2) Compares the keys to key.*/
        std::pair<iterator, iterator> equal_range(const Key &key) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        };

        std::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        };

        /*Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
         * Iterator pointing to the first element that is not less than key.
         * If no such element is found, a past-the-end iterator (see end()) is returned.*/
        iterator lower_bound(const Key &key) {
            iterator troot = _root;/*forward*/
            iterator ritr = _root;/*return*/

            while (troot ) {
                if (!(*troot < key))
                    ritr = troot--;
                else
                    ritr = troot++;
            }
            return ritr;
        };

        const_iterator lower_bound(const Key &key) const {
            iterator troot = _root;/*forward*/
            iterator ritr = _root;/*return*/

            while (troot) {
                if (!(*troot < key))
                    ritr = troot--;
                else
                    ritr = troot++;
            }
            return const_iterator(ritr);
        };

        /*Returns an iterator pointing to the first element that is greater than key.
         * Iterator pointing to the first element that is greater than key.
         * If no such element is found, past-the-end (see end()) iterator is returned.*/
        iterator upper_bound(const Key &key) {
            iterator troot = _root;/*forward*/
            iterator ritr = _root;/*return*/

            while (troot) {
                if (*troot < key)
                    ritr = troot--;
                else
                    ritr = troot++;
            }
            return ritr;
        };

        const_iterator upper_bound(const Key &key) const {
            iterator troot = _root;/*forward*/
            iterator ritr = _root;/*return*/

            while (troot){
                if (*troot < key)
                    ritr = troot--;
                else
                    ritr = troot++;
            }
            return const_iterator(ritr);
        };

        /*Returns the function object that compares the keys, which is a copy of
         * this container's constructor argument comp. It is the same as value_comp.*/
        key_compare key_comp() const { return key_comp(); };

        /*Returns the function object that compares the values. It is the same as key_comp.*/
        value_compare value_comp() const { return value_comp(); };

    /*
    *====================================================================================
    *|                             Private Membre fonction                              |
    *====================================================================================
    */

    private:



    };
    /*
    *====================================================================================
    *|                                 Non Membre fonction                              |
    *====================================================================================
    */

        template< class Key, class Compare, class Allocator >
        inline bool operator==(const typename ft::RedBlackTree< Key, Compare, Allocator >::iterator& lhs,
                               const typename ft::RedBlackTree< Key, Compare, Allocator >::iterator& rhs) {
            return lhs == rhs;
        }

        template< class Key, class Compare, class Allocator >
        inline bool operator!=(const typename ft::RedBlackTree< Key, Compare, Allocator >::iterator& lhs,
                               const typename ft::RedBlackTree< Key, Compare, Allocator >::iterator& rhs) {
            return lhs != rhs;
        }

        template< class Key, class Compare, class Allocator >
        inline bool operator<(const typename RedBlackTree< Key, Compare, Allocator >::iterator& lhs,
                              const typename RedBlackTree< Key, Compare, Allocator >::iterator& rhs) {
            return lhs < rhs;
        }

        template< class Key, class Compare, class Allocator >
        inline bool operator<=(const typename RedBlackTree< Key, Compare, Allocator >::iterator& lhs,
                               const typename RedBlackTree< Key, Compare, Allocator >::iterator& rhs) {
            return lhs <= rhs;
        }

        template< class Key, class Compare, class Allocator >
        inline bool operator>(const typename RedBlackTree< Key, Compare, Allocator >::iterator& lhs,
                              const typename RedBlackTree< Key, Compare, Allocator >::iterator& rhs) {
            return lhs > rhs;
        }

        template< class Key, class Compare, class Allocator >
        inline bool operator>=(const typename RedBlackTree< Key, Compare, Allocator >::iterator& lhs,
                               const typename RedBlackTree< Key, Compare, Allocator >::iterator& rhs) {
            return lhs >= rhs;
        }

    /*Checks if the contents of lhs and rhs are equal,
    * that is, they have the same number of elements and each element
    * in lhs compares equal with the element in rhs at the same position.*/
        template< class Key, class Compare, class Allocator >
        inline bool operator== ( const RedBlackTree< Key, Compare, Allocator >& lhs,
                                 const RedBlackTree< Key, Compare, Allocator >& rhs )
        {__INFONM__
            if (lhs.size() == rhs.size())
                return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
            return false;
        };

        template< class Key, class Compare, class Allocator >
        inline bool operator!=( const RedBlackTree< Key, Compare, Allocator >& lhs,
                                const RedBlackTree< Key, Compare, Allocator >& rhs ){__INFONM__ return !(lhs == rhs); };

    /*3-6) Compares the contents of lhs and rhs lexicographically.
     * The comparison is performed
     * by a function equivalent to std::lexicographical_compare.*/
        template< class Key, class Compare, class Allocator >
        inline bool operator<( const RedBlackTree< Key, Compare, Allocator >& lhs,
                               const RedBlackTree< Key, Compare, Allocator >& rhs )
        {__INFONM__
            return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                               rhs.begin(), rhs.end());
        };

        template< class Key, class Compare, class Allocator >
        inline bool operator<=( const RedBlackTree< Key, Compare, Allocator >& lhs,
                                const RedBlackTree< Key, Compare, Allocator >& rhs ) {__INFONM__ return !(rhs < lhs); };

        template< class Key, class Compare, class Allocator >
        inline bool operator>( const RedBlackTree< Key, Compare, Allocator >& lhs,
                               const RedBlackTree< Key, Compare, Allocator >& rhs )  {__INFONM__ return rhs < lhs; };

        template< class Key, class Compare, class Allocator >
        inline bool operator>=( const RedBlackTree< Key, Compare, Allocator >& lhs,
                                const RedBlackTree< Key, Compare, Allocator >& rhs ) {__INFONM__ return !(lhs < rhs); };

    __FT_CONTAINERS_END_NAMESPACE

    namespace std {
        template< class Key, class Compare, class Allocator >
        inline void swap(ft::RedBlackTree< Key, Compare, Allocator >& lhs, ft::RedBlackTree< Key, Compare, Allocator > &rhs)
        {__INFOMO__ lhs.swap(rhs); __INFOMONL__ };
    }
    __FT_CONTAINERS_END_NAMESPACE

    #endif //FT_CONTAINERS_SET_TPP
