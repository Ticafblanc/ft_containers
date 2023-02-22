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
#include "iterator.tpp"
#include "type_traits.tpp"
#include "algorithm.tpp"
#include "utility.tpp"
#include "stack.tpp"

#ifndef FT_CONTAINERS_SET_TPP
# define FT_CONTAINERS_SET_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    template< class Key, class Compare, class Allocator >
    class setbase {

    protected:
        typedef Allocator                                                           allocator;
        typedef Compare                                                             compare;

        setbase() {};

        explicit setbase(const Compare& comp, const Allocator& alloc) : _comp(comp), _alloc(alloc){};

        ~setbase() {};


    protected:

        Allocator   _alloc;
        Compare     _comp;

        enum Color { RED, BLACK };

        struct node {

            Key         *_Key;
            Color       _Color;
            node        *_LeftChild;
            node        *_RightChild;
            node        *_Parent;

            /*
            *====================================================================================
            *|                                  Member Fonction                                 |
            *====================================================================================
            */

            node() : _Key(nullptr), _Color(BLACK), _LeftChild(nullptr),
                        _RightChild(nullptr), _Parent(nullptr){};

            explicit node(Key* value) : _Key(value), _Color(BLACK), _LeftChild(nullptr),
                                           _RightChild(nullptr), _Parent(nullptr){};

            explicit node(Key* value, Color color, node* _nul)
                    : _Key(value), _Color(color), _LeftChild(_nul),
                      _RightChild(_nul), _Parent(_nul){};

            node (const node &other){
                Key* build = this->_alloc.allocate(1);
                this->_alloc.construct(build);
                this->init(build);
                this->_root = copy_tree(other, other._root);
            };

            ~node() {};

            //is not a depp copy
            node &operator=(const node &other) {
                _Key = other._Key;
                _Color = other._Color;
                _LeftChild = other._LeftChild;
                _RightChild = other._RightChild;
                _Parent = other._Parent;
                return *this;
            };

        };
    };

    template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set : protected setbase <Key, Compare , Allocator> {

    private:

        typedef setbase <Key, Compare , Allocator>                  _base;
        typedef set< Key, Compare, Allocator >                      _self;
        typedef typename _base::node                                _node;
        typedef typename _base::Color                               _color;
        _node                                                       *_root;
        _node                                                       *_nul;
        std::size_t                                                 _size;

    /*
    *====================================================================================
    *|                                    iterator                                      |
    *====================================================================================
    */

    private:

        struct iterator : public std::iterator<std::bidirectional_iterator_tag,
                Key, Key, const Key *, Key> {


            _node*                                   __node;
            set<Key, Compare, Allocator>&            __set;

            /*
            *====================================================================================
            *|                                  Member Fonction                                 |
            *====================================================================================
            */


            iterator() : __node(nullptr), __set(nullptr){};

            explicit iterator(_node* tmp, set<Key, Compare, Allocator>& set ) : __node(tmp), __set(set){};

            iterator(const iterator &other) : __node(other._node) , __set(other._set){};

            ~iterator(){};

            iterator& operator=(const iterator& other){
                __node = other.__node;
                __set = other.__set;
                return *this;
            };
            /*
            *====================================================================================
            *|                                  overload operator                               |
            *====================================================================================
            */

            Key& operator*() const { return *(__node->_Key); }
            Key* operator->() const { return &(operator*()); }

            iterator& operator++() {
                __node = __set.successor(__node);
                return *this;
            };

            iterator operator++(int) {
                const iterator Tmp = *this;
                __node = __set.successor(__node);
                return Tmp;
            };

            iterator& operator--() {
                __node = __set.predecessor(__node);
                return *this;
            };

            iterator  operator--(int) {
                const iterator Tmp = *this;
                __node = __set.predecessor(__node);
                return Tmp;
            };

            bool operator==(const iterator& rhs) const { return __node == rhs.__node; };

            bool operator!=(const iterator& rhs) const { return !(*this == rhs); };


        };/*end of iterator*/

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
        typedef typename _base::compare                              key_compare;
        typedef key_compare                                         value_compare;
        typedef value_type &                                        reference;
        typedef const value_type &                                  const_reference;
        typedef typename _base::allocator                           allocator_type;
        typedef typename Allocator::pointer                         pointer;
        typedef typename Allocator::const_pointer                   const_pointer;
        typedef iterator                                            iterator;
        typedef const iterator                                      const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

    public:

        set() : _base(), _size(0){ init(); };

        explicit set(const Compare &comp, const Allocator &alloc = Allocator())
                                    : _base(comp, alloc), _size(0){ init(); };

        template<class InputIt>
        set(InputIt first, InputIt last,
            const Compare &comp = Compare(), const Allocator &alloc = Allocator())
            : _base(comp, alloc), _size(0) { init(); insert(first, last); };

        set(const _self &other) : _base(other._comp, other._alloc), _size(other._size) {
            init();
            _root = copy_tree(other, other._root);
        };

        ~set() { clear(); destroy(_nul); };

        /*Copy assignment operator. Replaces the contents with a copy of the contents of others.*/
        _self &operator=(const _self &other) {
            clear();
            this->_alloc = other._alloc;
            this->_comp = other._comp;
            _root = copy_tree(other, other._root);
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

        iterator                begin()             {__INFOIT__ return iterator(this->minimum(this->_root), *this); };

        const_iterator          begin()     const   {__INFOIT__ return iterator(this->minimum(this->_root), *this); };

        iterator                end()               {__INFOIT__ return iterator(this->maximum(this->_nul), *this); };

        const_iterator          end()       const   {__INFOIT__ return iterator(this->maximum(this->_nul), *this); };

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
        bool        empty()     const { __INFOCA__ return this->_size == 0; };

        /*Returns the number of elements in the container,
         * i.e. std::distance(begin(), end()).*/
        size_type   size()      const {__INFOCA__ return this->_size; };

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
            clear_tree(this->_root);
            this->_root = this->_nul;
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
            std::swap(_root, other._root);
            std::swap(_nul, other._nul);
            std::swap(_size, other._size);
        };

    /*
    *====================================================================================
    *|                                  Lookup                                          |
    *====================================================================================
    */

        /*Returns the number of elements with key that compares equivalent to the specified argument.
         * Returns the number of elements with key key. This is either 1 or 0 since this container
         * does not allow duplicates.*/
        size_type count(const Key &key) const { return (this->isNul(finds(key)._node)) ? 1 : 0; };

        /*Finds an element with key equivalent to key.
         * Iterator to an element with key equivalent to key. If no such element is found,
         * past-the-end (see end()) iterator is returned.*/
        iterator find(const Key &key) {
            _node* rnode = _root;
            while (!isNul(rnode) && (this->_comp(*(rnode->_Key), key) || this->_comp(key, *(rnode->_Key)))) {
                if (this->_comp(key, *(rnode->_Key)))
                    rnode = rnode->_LeftChild;
                else
                    rnode = rnode->_RightChild;
            }
            return iterator(rnode, *this); };

        const_iterator find(const Key &key) const {__INFOMO__ return const_iterator(find(key), *this); };

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
            _root = _nul = create_node(build, this->BLACK);
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
                return _nul;
            Key* build = this->_alloc.allocate(1);
            this->_alloc.construct(build, *(node->_Key));
            _node *new_node = create_node(build, node->_Color);
            new_node->_LeftChild = copy_tree(other, node->_LeftChild);
            new_node->_RightChild = copy_tree(other, node->_RightChild);
            new_node->_Parent = _nul;
            if (!isNul(new_node->_LeftChild)) {
                new_node->_LeftChild->_Parent = new_node;
            }
            if (!isNul(new_node->_RightChild)) {
                new_node->_RightChild->_Parent = new_node;
            }
            this->_size++;
            return new_node;
        };

        /*Erases all elements from the treee start at _root*/
        void clear_tree(_node* node) {
            if (!isNul(node)) {
                clear_tree(node->_LeftChild);
                clear_tree(node->_RightChild);
                delete_node(node);
            }
        };

        bool isNul(_node* node) const {
            return (node == nullptr || node == _nul);
        };

        bool isRoot(_node* node) const {
            return (node == _root);
        };

        bool isRightChild(_node* node){
            return node == node->_Parent->_RightChild;
        };

        bool isLeftChild(_node* node){
            return node == node->_Parent->_LeftChild;
        };

        _node* maximum(_node* node) {
            while (!isNul(node->_RightChild)) {
                node = node->_RightChild;
            }
            return node;
        };

        _node* minimum(_node* node) {
            while (!isNul(node->_LeftChild)) {
                node = node->_LeftChild;
            }
            return node;
        };

        _node* successor(_node* node) {
            if (!isNul(node->_RightChild))
                return minimum(node->_RightChild);
            _node* rnode = node->_Parent;
            while (!isNul(rnode) && node == rnode->_RightChild) {
                node = rnode;
                rnode = rnode->_Parent;
            }
            return rnode;
        };

        _node* predecessor(_node* node) {
            if (isNul(node))
                return maximum(_root);
            if (!isNul(node->_LeftChild))
                return maximum(node->_LeftChild);
            _node* rnode = node->_Parent;
            while (!isNul(rnode) && node == rnode->_LeftChild) {
                node = rnode;
                rnode = rnode->_Parent;
            }
            return rnode;
        };

        _node* transplant(_node* node_to_delete, _node* node_to_transplant) {
            if (isNul(node_to_delete->_Parent))
                _root = node_to_transplant;
            else if (isLeftChild(node_to_delete))
                node_to_delete->_Parent->_LeftChild = node_to_transplant;
            else
                node_to_delete->_Parent->_RightChild = node_to_transplant;
            node_to_transplant->_Parent = node_to_delete->_Parent;
            return node_to_transplant;
        };

        /* find return greater or eqaul pos value*/
        _node* greater_or_equal(const Key& value) const {
            _node* forward_root = _root;
            _node* save = _nul;
            while (!(isNul(forward_root))) {
                if (!comp(*(forward_root->_Key), value)) {
                    save = forward_root;
                    forward_root = forward_root->_LeftChild;
                }
                else {
                    forward_root = forward_root->_RightChild;
                }
            }
            return save;
        };

    /*
    *====================================================================================
    *|                                    Insert                                        |
    *====================================================================================
    */

        /* find place with spec func to compare and add new node fo inserts value.
         * return _node* to pos*/

        _node* insertn(Key* value, _node* forward_root) {
            __INFOMO__
            _node* destination_node = _nul;
            while (!isNul(forward_root)) {
                destination_node = forward_root;
                if (comp(*value, *(forward_root->_Key)))
                    forward_root = forward_root->_LeftChild;
                else
                    forward_root = forward_root->_RightChild;
            }
            _node* new_node = create_node(value, this->RED);
            new_node->_Parent = destination_node;
            if (isNul(destination_node))
                _root = new_node;
            else if (comp(*(new_node->_Key), *(destination_node->_Key)))
                destination_node->_LeftChild = new_node;
            else
                destination_node->_RightChild = new_node;
            insertFixup(new_node);
            _size++;
            __INFOMONL__
            return new_node;
        };


    /*
    *====================================================================================
    *|                                    Erase                                         |
    *====================================================================================
    */

        /*Removes the element at pos delete data Key with specific allocator in set
         * return node* to replace it*/
        ft::pair<_node*, Key*> erases(_node* pos) {
            __INFOMO__
            if (isNul(pos))
                return  ft::make_pair(pos, nullptr);
            if (isRoot(pos)){
                ft::pair<_node*, Key*> ret = ft::make_pair(_root, delete_node(pos));
                _root = _nul;
                return ret;
            }
            _node* trans;
            _color original_color = pos->_Color;
            if (isNul(pos->_LeftChild))
                trans = transplant(pos, pos->_RightChild);
            else if (isNul(pos->_RightChild))
                trans = transplant(pos, pos->_LeftChild);
            else {
                _node* next = minimum(pos->_RightChild);
                original_color = next->_Color;
                trans = next->_RightChild;
                if (next->_Parent == pos)
                    trans->_Parent = next;
                else {
                    transplant(next, next->_RightChild);
                    next->_RightChild = pos->_RightChild;
                    next->_RightChild->_Parent = next;
                }
                transplant(pos, next);
                next->_LeftChild = pos->_LeftChild;
                next->_LeftChild->_Parent = next;
                next->_Color = pos->_Color;
            }
            if (original_color == this->BLACK)
                deleteFixup(trans);
            _size--;
            __INFOMONL__
            return ft::make_pair(trans, delete_node(pos));
        };

    /*
    *====================================================================================
    *|                                    Balance                                       |
    *====================================================================================
    */

        /*rotate Node X */
        void rotateLeft(_node* node) {
            _node* tmp = node->_RightChild;
            node->_RightChild = tmp->_LeftChild;
            if (!isNul(tmp->_LeftChild))
                tmp->_LeftChild->_Parent = node;
            tmp->_Parent = node->_Parent;
            if (isNul(node->_Parent))
                _root = tmp;
            else if (isLeftChild(node))
                node->_Parent->_LeftChild = tmp;
            else
                node->_Parent->_RightChild = tmp;
            tmp->_LeftChild = node;
            node->_Parent = tmp;
        };

        /*rotate Node X */
        void rotateRight(_node* node) {
            _node* tmp = node->_LeftChild;
            node->_LeftChild = tmp->_RightChild;
            if (!isNul(tmp->_RightChild))
                tmp->_RightChild->_Parent = node;
            tmp->_Parent = node->_Parent;
            if (isNul(node->_Parent))
                _root = tmp;
            else if (isRightChild(node))
                node->_Parent->_RightChild = tmp;
            else
                node->_Parent->_LeftChild = tmp;
            tmp->_RightChild = node;
            node->_Parent = tmp;
        };

        /*balance tree after insert*/
        void insertFixup(_node* new_node) {
            _node* check;
            while (new_node->_Parent->_Color == this->RED) {
                if (isLeftChild(new_node->_Parent)) {
                    check = new_node->_Parent->_Parent->_RightChild;
                    if (check->_Color == this->RED) {
                        new_node->_Parent->_Color = this->BLACK;
                        check->_Color = this->BACK;
                        new_node->_Parent->_Parent->_Color = this->RED;
                        new_node = new_node->_Parent->_Parent;
                    } else {
                        if (isRightChild(new_node)) {
                            new_node = new_node->_Parent;
                            rotateLeft(new_node);
                        }
                        new_node->_Parent->_Color = this->BACK;
                        new_node->_Parent->_Parent->_Color = this->RED;
                        rotateRight(new_node->_Parent->_Parent);
                    }
                } else {
                    check = new_node->_Parent->_Parent->_LeftChild;
                    if (check->_Color == this->RED) {
                        new_node->_Parent->_Color = this->BACK;
                        check->_Color = this->BACK;
                        new_node->_Parent->_Parent->_Color = this->RED;
                        new_node = new_node->_Parent->_Parent;
                    } else {
                        if (isLeftChild(new_node)) {
                            new_node = new_node->_Parent;
                            rotateRight(new_node);
                        }
                        new_node->_Parent->_Color = this->BACK;
                        new_node->_Parent->_Parent->_Color = this->RED;
                        rotateLeft(new_node->_Parent->_Parent);
                    }
                }
            }
            _root->_Color = this->BACK;
        };

        /*balance tree after delete*/
        void deleteFixup(_node* transplant) {
            _node* check;
            while (transplant != _root && transplant->_Color == this->BACK) {
                if (transplant == transplant->_Parent->_LeftChild) {
                    check= transplant->_Parent->_RightChild;
                    if (check->_Color == this->RED) {
                        check->_Color = this->BACK;
                        transplant->_Parent->_Color = this->RED;
                        rotateLeft(transplant->_Parent);
                        check = transplant->_Parent->_RightChild;
                    }
                    if (check->_LeftChild->_Color == this->BACK && check->_RightChild->_Color == this->BACK) {
                        check->_Color = this->RED;
                        transplant = transplant->_Parent;
                    } else {
                        if (check->_RightChild->_Color == this->BACK) {
                            check->_LeftChild->_Color = this->BACK;
                            check->_Color = this->RED;
                            rotateRight(check);
                            check = transplant->_Parent->_RightChild;
                        }
                        check->_Color = transplant->_Parent->_Color;
                        transplant->_Parent->_Color = this->BACK;
                        check->_RightChild->_Color = this->BACK;
                        rotateLeft(transplant->_Parent);
                        transplant = _root;
                    }
                } else {
                    check = transplant->_Parent->_LeftChild;
                    if (check->_Color == this->RED) {
                        check->_Color = this->BACK;
                        transplant->_Parent->_Color = this->RED;
                        rotateRight(transplant->_Parent);
                        check = transplant->_Parent->_LeftChild;
                    }
                    if (check->_RightChild->_Color == this->BACK && check->_LeftChild->_Color == this->BACK) {
                        check->_Color = this->RED;
                        transplant = transplant->_Parent;
                    } else {
                        if (check->_LeftChild->_Color == this->BACK) {
                            check->_RightChild->_Color = this->BACK;
                            check->_Color = this->RED;
                            rotateLeft(check);
                            check = transplant->_Parent->_LeftChild;
                        }
                        check->_Color = transplant->_Parent->_Color;
                        transplant->_Parent->_Color = this->BACK;
                        check->_LeftChild->_Color = this->BACK;
                        rotateRight(transplant->_Parent);
                        transplant = _root;
                    }
                }
            }
            transplant->_Color = this->BACK;
        };

    /*
    *====================================================================================
    *|                                    printTest                                     |
    *====================================================================================
    */

        void printSubtree(_node* node, int level, const std::deque<bool>& branches) {
            if (isNul(node)) return;
            std::deque<bool> new_branches(branches);
            new_branches.push_back(false);
            printSubtree(node->_RightChild, level + 1, new_branches);
            new_branches.pop_back();

            std::cout << std::string(level * 4, ' ');
            for (std::deque<bool>::const_iterator it = branches.begin(); it != branches.end(); ++it) {
                std::cout << "    " ;
            }
            if (node == _root)
                std::cout << "─── " << "\033[1;32m" << *(node->_Key) << "\033[0m" << std::endl;
            else if (node->_Color == this->BACK )
                std::cout << "── " << "\033[1;30m"<<  *(node->_Key) << "\033[0m" << std::endl;

            else
                std::cout << "── " << "\033[1;31m" << *(node->_Key) << "\033[0m" << std::endl;

            new_branches.push_back(true);
            printSubtree(node->_LeftChild, level + 1, new_branches);
        }

        void print() {
            std::cout << "\033[2J\033[1;1H" << std::endl;
            printSubtree(_root, 0, std::deque<bool>());
            std::cout<<std::endl;
            sleep(1);
        }



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
