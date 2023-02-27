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
#include "iterator.tpp"
#include <functional>
#include <unistd.h>


#ifndef FT_CONTAINERS_SET_TPP
# define FT_CONTAINERS_SET_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    template<class Key, class _node>
    struct setiterator : public std::iterator<std::bidirectional_iterator_tag,
            Key, Key, const Key *, Key> {


        _node *__node;
        RedBlackTree<Key> *RBT;

        /*
        *====================================================================================
        *|                                  Member Fonction                                 |
        *====================================================================================
        */


        setiterator() : __node(nullptr) {};

        explicit setiterator(_node *tmp) : __node(tmp) {};

        setiterator(const setiterator &other) : __node(other.__node) {};

        ~setiterator() {};

        setiterator &operator=(const setiterator &other) {
            __node = other.__node;
            RBT = other.RBT;
            return *this;
        };

        /*
        *====================================================================================
        *|                                  overload operator                               |
        *====================================================================================
        */

        Key &operator*() const { return *(__node->_Key); }

        Key *operator->() const { return &(operator*()); }

        setiterator &operator++() {
            __node = RBT->successor(__node);
            return *this;
        };

        setiterator operator++(int) {
            const setiterator Tmp = *this;
            __node = RBT->successor(__node);
            return Tmp;
        };

        setiterator &operator--() {
            __node = RBT->predecessor(__node);
            return *this;
        };

        setiterator operator--(int) {
            const setiterator Tmp = *this;
            __node = RBT->predecessor(__node);
            return Tmp;
        };

        bool operator==(const setiterator &rhs) const { return __node == rhs.__node; };

        bool operator!=(const setiterator &rhs) const { return !(*this == rhs); };
    };


    template< class Key, class Compare, class Allocator >
    class setbase {

    protected:
        typedef Allocator                                                           allocator;
        typedef Compare                                                             compare;
        typedef typename RedBlackTree<Key>::Node                                    _node;

        setbase() { RBT.init(build()); };

        explicit setbase(const Compare& comp, const Allocator& alloc) : _comp(comp), _alloc(alloc){ RBT.init(build()); };

        ~setbase() { destroy(RBT.deinit()); };

        Key* build() {
            Key* build = _alloc.allocate(1);
            _alloc.construct(build);
            return build;
        };

        void destroy(Key* key) {
            _alloc.destroy(key);
            _alloc.deallocate(key, 1);
        };

    protected:
        RedBlackTree<Key> RBT;
        Allocator _alloc;
        Compare _comp;
    };

    template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set : protected setbase <Key, Compare , Allocator>{

    private:

        typedef setbase <Key, Compare , Allocator>                  base;
        typedef set< Key, Compare, Allocator >                      _self;

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
        typedef typename base::compare                              key_compare;
        typedef key_compare                                         value_compare;
        typedef value_type &                                        reference;
        typedef const value_type &                                  const_reference;
        typedef typename base::allocator                            allocator_type;
        typedef typename Allocator::pointer                         pointer;
        typedef typename Allocator::const_pointer                   const_pointer;
        typedef setiterator<Key, typename base::_node>              iterator;
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

        explicit set(const Compare &comp, const Allocator &alloc = Allocator()) : base(comp, alloc)
        {__INFOMF__ };

        template<class InputIt>
        set(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator())
                : base(comp, alloc) {__INFOMF__ insert(first, last); };

        set(const _self &other) : base(other._comp, other._alloc) {__INFOMF__ this->_root = copy_tree(other, other._root); };

        ~set() {__INFOMF__ clear_tree();};

        /*Copy assignment operator. Replaces the contents with a copy of the contents of others.*/
        _self &operator=(const _self &other) {
            clear_tree()
            this->_alloc = other._alloc;
            this->_comp = other._comp;
            this->_root = copy_tree(other, other._root);
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

        iterator                begin()             {__INFOIT__ return iterator(this->minimum(this->_root), &this->RBT); };

        const_iterator          begin()     const   {__INFOIT__ return iterator(this->minimum(this->_root), &this->RBT); };

        iterator                end()               {__INFOIT__ return iterator(this->maximum(this->_nul), &this->RBT); };

        const_iterator          end()       const   {__INFOIT__ return iterator(this->maximum(this->_nul), &this->RBT); };

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
        bool        empty()     const { __INFOCA__ return this->RBT.getSize() == 0; };

        /*Returns the number of elements in the container,
         * i.e. std::distance(begin(), end()).*/
        size_type   size()      const {__INFOCA__ return this->RBT.getSize(); };

        /*Returns the maximum number of elements the container is able to
         * hold due to system or library implementation limitations, i.e.
         * std::distance(begin(), end()) for the largest container.*/
        size_type   max_size()  const {__INFOCA__ return std::numeric_limits<size_type>::max() / sizeof(value_type); };

    /*
    *====================================================================================
    *|                                    Modifiers                                     |
    *====================================================================================
    */


    public:

        /*Erases all elements from the container. After this call, size() returns zero.
         * Invalidates any references, pointers, or iterators referring to contained elements.
         * Any past-the-end iterators are also invalidated.*/
        void clear() {
            __INFOMO__
            clear_tree(this->RBT.getRoot());
            this->RBT.setNulRoot();
            __INFOMONL__
        };

        /* inserts value.
         * Returns a pair consisting of an iterator to the inserted element (or to the element
         * that prevented the insertion) and a bool value set to true if and only if the insertion took place.*/
        ft::pair<iterator, bool> insert(const value_type &value) {
            __INFOMO__
            iterator pos = lower_bound(value);
            if (!this->isNul(pos._node) && *pos == value)
                return  ft::make_pair(pos, false);
            else
                return  ft::make_pair(insert(iterator(this->_root, *this), value), true);
            __INFOMONL__

        };

        /*
         * inserts value in the position as close as possible to the position just prior to pos.
         * Returns an iterator to the inserted element, or to the element that prevented the insertion.
         */
        iterator insert(iterator pos, const value_type &value) {
            __INFOMO__
            Key* build = this->_alloc.allocate(1);
            this->_alloc.construct(build, value);
            return iterator(this->insertn(build, pos._node, this->_comp), *this);
        };

        /*Inserts elements from range [first, last). If multiple elements in the range have keys
         * that compare equivalent, it is unspecified which element is inserted
         * O(N·log(size() + N)), where N is the number of elements to insert.*/
        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            __INFOMO__
            iterator pos = iterator(this->_root, *this);
            for ( ; first != last; ++first)
                pos = insert(pos, *first);
            __INFOMONL__
        };

        /*Removes the element at pos
         * Iterator following the last removed element.*/
        iterator erase(iterator pos) {
            __INFOMO__
            ft::pair<_node*, Key*> result;
            result = this->erases(pos._node);
            this->_alloc.destroy(result.second);
            this->_alloc.deallocate(result.second, 1);
            return iterator(result.first, *this); };

        /*Removes the elements in the range [first, last).
         * Iterator following the last removed element.*/
        iterator erase(iterator first, iterator last) {
            __INFOMO__
            ft::pair<_node*, Key*> result;
            for ( ; *first != *last; ++first)
                erase(first);
            __INFOMONL__
            return erase(first);
        };

        /*Removes the element (if one exists) with the key equivalent to key.
         * Number of elements removed (0 or 1).
         * Any exceptions thrown by the Compare object.*/
        size_type erase(const Key &key) {
            __INFOMO__
            _node* pos = this->finds(key, this->_root, this->_comp);
            if(!(this->isNul(pos))) {
                ft::pair<_node *, Key *> result;
                result = this->erases(pos);
                this->_alloc.destroy(result.second);
                this->_alloc.deallocate(result.second, 1);
            }
            __INFOMONL__
            return (!this->isNul(this->finds(key, this->_root, this->_comp))) ? 1 : 0;
        };
        /*Exchanges the contents of the container with those of other. Does not invoke any
         * move, copy, or swap operations on individual elements.All iterators and references
         * remain valid. The past-the-end iterator is invalidated.The Compare objects must be
         * Swappable, and they are exchanged using unqualified call to non-member swap.*/
        void swap( _self& other ) {
            std::swap(this->_alloc, other._alloc);
            std::swap(this->_comp, other._comp);
            this->swap(other);
        };

    /*
    *====================================================================================
    *|                                  Lookup                                          |
    *====================================================================================
    */

        /*Returns the number of elements with key that compares equivalent to the specified argument.
         * Returns the number of elements with key key. This is either 1 or 0 since this container
         * does not allow duplicates.*/
        size_type count(const Key &key) const { return (this->isNul(this->finds(key, this->_root, this->_comp))) ? 1 : 0; };

        /*Finds an element with key equivalent to key.
         * Iterator to an element with key equivalent to key. If no such element is found,
         * past-the-end (see end()) iterator is returned.*/
        iterator find(const Key &key) {__INFOMO__ return iterator(this->finds(key, this->_root, this->_comp), *this); };

        const_iterator find(const Key &key) const {__INFOMO__ return const_iterator(this->finds(key, this->_root, this->_comp()), *this); };

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
        iterator lower_bound(const Key &key) {return iterator(this->greater_or_equal(key, this->_comp), *this); };

        const_iterator lower_bound(const Key &key) const {return const_iterator(this->greater_or_equal(key, this->_comp));};

        /*Returns an iterator pointing to the first element that is greater than key.
         * Iterator pointing to the first element that is greater than key.
         * If no such element is found, past-the-end (see end()) iterator is returned.*/
        iterator upper_bound(const Key &key) {
            iterator save =  lower_bound(key);
            return (*save == key) ? ++save : save;
        };

        const_iterator upper_bound(const Key &key) const {
            iterator save =  lower_bound(key);
            return const_cast<const_iterator>((*save == key) ? ++save : save);
        };

    /*
    *====================================================================================
    *|                                 Observers                                        |
    *====================================================================================
    */

        /*Returns the function object that compares the keys, which is a copy of
         * this container's constructor argument comp. It is the same as value_comp.*/
        key_compare key_comp() const { return key_compare(); };

        /*Returns the function object that compares the values. It is the same as key_comp.*/
        value_compare value_comp() const { return value_compare(); };

    /*
    *====================================================================================
    *|                                 private membre                                   |
    *====================================================================================
    */

    private:

        /*build Key value at the Key* */
        Key* build(const Key &value) {
            Key* build = this->_alloc.allocate(1);
            this->_alloc.construct(build, value);
            return build;
        };



        void destroy(Key* key) {
            this->_alloc.destroy(key);
            this->_alloc.deallocate(key, 1);
        };

        /*init _root and _nul Node at the start */
        void   init(){
            Key* build = this->_alloc.allocate(1);
            this->_alloc.construct(build);
            _root = _nul = new _node(build);
        };

        /*call constructor non void de Node and new Node */
        _node*   create_node(const Key value, _color color){
            _size++;
            return new _node(build(value), color, _nul);
        };

        /*delete node and call the destructor of Node*/
        void    delete_node(_node* node){
            destroy(node->_Key);
            delete node;
            _size--;

        };
        /*copy the tree start at _root*/
        _node* copy_tree(const _self &other, _node* node) {
            if(other.isNul(node))
                return this->_nul;
            Key* build = this->_alloc.allocate(1);
            this->_alloc.construct(build, *(node->_Key));
            _node *new_node = this->create_node(build, node->_Color);
            new_node->_LeftChild = copy_tree(other, node->_LeftChild);
            new_node->_RightChild = copy_tree(other, node->_RightChild);
            new_node->_Parent = this->_nul;
            if (!this->isNul(new_node->_LeftChild)) {
                new_node->_LeftChild->_Parent = new_node;
            }
            if (!this->isNul(new_node->_RightChild)) {
                new_node->_RightChild->_Parent = new_node;
            }
            this->_size++;
            return new_node;
        };

        /*Erases all elements from the treee start at _root*/
        void clear_tree(_node* node) {
            if (!this->isNul(node)) {
                clear_tree(node->_LeftChild);
                clear_tree(node->_RightChild);
                Key * save = this->delete_node(node);
                this->_alloc.destroy(save);
                this->_alloc.deallocate(save, 1);
                this->_size--;
            }
        };
    };//end of ft::set

    /*
    *====================================================================================
    *|                                 Non Membre fonction                              |
    *====================================================================================
    */


    /*Checks if the contents of lhs and rhs are equal,
    * that is, they have the same number of elements and each element
    * in lhs compares equal with the element in rhs at the same position.*/
    template< class Key, class Compare, class Allocator >
    inline bool operator== ( const ft::set< Key, Compare, Allocator >& lhs,
                             const ft::set< Key, Compare, Allocator >& rhs)
    {__INFONM__
        if (lhs.size() == rhs.size())
            return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        return false;
    };

    template< class Key, class Compare, class Allocator >
    inline bool operator!=( const ft::set< Key, Compare, Allocator >& lhs,
                            const ft::set< Key, Compare, Allocator >& rhs ){__INFONM__ return !(lhs == rhs); };

    /*3-6) Compares the contents of lhs and rhs lexicographically.
     * The comparison is performed
     * by a function equivalent to std::lexicographical_compare.*/
    template< class Key, class Compare, class Allocator >
    inline bool operator<( const ft::set< Key, Compare, Allocator >& lhs,
                           const ft::set< Key, Compare, Allocator >& rhs)
    {__INFONM__
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                           rhs.begin(), rhs.end());
    };

    template< class Key, class Compare, class Allocator >
    inline bool operator<=( const ft::set< Key, Compare, Allocator >& lhs,
                            const ft::set< Key, Compare, Allocator >& rhs ) {__INFONM__ return !(rhs < lhs); };

    template< class Key, class Compare, class Allocator >
    inline bool operator>( const ft::set< Key, Compare, Allocator >& lhs,
                           const ft::set< Key, Compare, Allocator >& rhs )  {__INFONM__ return rhs < lhs; };

    template< class Key, class Compare, class Allocator >
    inline bool operator>=( const ft::set< Key, Compare, Allocator >& lhs,
                            const ft::set< Key, Compare, Allocator >& rhs ) {__INFONM__ return !(lhs < rhs); };

__FT_CONTAINERS_END_NAMESPACE

namespace std {
    template< class Key, class Compare, class Allocator >
    inline void swap(ft::set< Key, Compare, Allocator >& lhs,
                     ft::set< Key, Compare, Allocator >& rhs)
    {__INFOMO__ lhs.swap(rhs); __INFOMONL__ };
}

#endif //FT_CONTAINERS_SET_TPP
