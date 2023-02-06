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

#include <ft_containers.hpp>
#include <utility.tpp>

#ifndef FT_CONTAINER_RED_BLACK_TREE_TPP
# define FT_CONTAINER_RED_BLACK_TREE_TPP

    /*https://www.programiz.com/dsa/red-black-tree
    Red-Black tree is a self-balancing binary search tree in which each node contains an extra bit for denoting the color of the node, either red or black.

    A red-black tree satisfies the following properties:

    Red/Black Property: Every node is colored, either red or black.
    Root Property: The root is black.
    Leaf Property: Every leaf (NIL) is black.
    Red Property: If a red node has children then, the children are always black.
    Depth Property: For each node, any simple path from this node to any of its descendant leaf has the same black-depth (the number of black nodes).
*/
    // the Node ...
    //color of node

# define __RBT_RED 0x1
# define __RBT_BLACK 0x2

    //struct of base
struct S_Node{
    typedef S_Node*     Node_ptr;
    //Each node has the following attributes:
    char Color;
    S_Node *leftChild = nullptr;
    S_Node *rightChild = nullptr;
    S_Node *Parent = nullptr;//(except root node)

    static Node_ptr N_minimum(Node_ptr N_ptr)
    {
        while (N_ptr->leftChild != nullptr)
            N_ptr = N_ptr->leftChild;
        return N_ptr;
    }

    static Node_ptr N_maximum(Node_ptr N_ptr)
    {
        while (N_ptr->rightChild != nullptr)
            N_ptr = N_ptr->rightChild;
        return N_ptr;
    }
};
    //struct template
template<class Value_type >
struct S_Node_Vt : public S_Node{
    Value_type Vt;
};

    //iterator the tree
    //struct of base
struct S_RB_Tree_iterator{
    typedef S_Node::Node_ptr                    Node_ptr;
    typedef std::bidirectional_iterator_tag     iterator_category;//not use
    typedef std::ptrdiff_t                      difference_type;//not use
    Node_ptr N_ptr;
    Node_ptr T_ptr;

    void Iter_Plus_Plus()//a proteger des segv?
    {
        if (N_ptr->rightChild != nullptr)
        {
            N_ptr = S_Node::N_minimum(N_ptr->rightChild);
        }
        else
        {
            T_ptr = N_ptr->Parent;
            while (N_ptr == T_ptr->rightChild)
            {
                N_ptr = T_ptr;
                T_ptr = T_ptr->Parent;
            }
            //if (N_ptr->rightChild != T_ptr)
            N_ptr = T_ptr;
        }
        T_ptr = nullptr;
    }

    void Iter_Less_less()
    {
//        if (N_ptr->Color == __RBT_RED &&
//            N_ptr->Parent->Parent == N_ptr)
//            N_ptr = N_ptr->rightChild;
/*else*/if (N_ptr->leftChild != nullptr)
        {
            N_ptr = S_Node::N_maximum(N_ptr->leftChild);
//            T_ptr = N_ptr->leftChild;
//            while (T_ptr->rightChild != NULL)
//                T_ptr = T_ptr->rightChild;
//            N_ptr = T_ptr;
        }
        else
        {
            T_ptr = N_ptr->Parent;
            while (N_ptr == T_ptr->leftChild) {
                N_ptr = T_ptr;
                T_ptr = T_ptr->Parent;
            }
            N_ptr = T_ptr;
        }
        T_ptr = nullptr;
    }
};
    //struct template
template <class Vt, class Ref, class Ptr>
struct S_RB_Tree_iterator_Vt : public S_RB_Tree_iterator
{
    typedef Vt                                                                          value_type;
    typedef Ref                                                                         reference;
    typedef Ptr                                                                         pointer;
    typedef S_RB_Tree_iterator_Vt<value_type, value_type&, value_type*>                 iterator;
    typedef S_RB_Tree_iterator_Vt<value_type, const value_type&, const value_type*>     const_iterator;
    typedef S_RB_Tree_iterator_Vt<value_type, reference, pointer>                       Self;
    typedef S_Node_Vt<value_type>*                                                      Node_ptr;

    S_RB_Tree_iterator_Vt() {}
    S_RB_Tree_iterator_Vt(Node_ptr N_ptr) { this->N_ptr = N_ptr; }
    S_RB_Tree_iterator_Vt(const iterator& it) { this->N_ptr = it.N_ptr; }

    reference operator*() const { return Node_ptr(N_ptr)->Vt; }


    Self& operator++()
    {
        Iter_Plus_Plus();
        return *this;
    }
    Self operator++(int)
    {
        Self __tmp = *this;
        Iter_Plus_Plus();
        return __tmp;
    }
    Self& operator--()
    {
        Iter_Less_less();
        return *this;
    }
    Self operator--(int)
    {
        Self __tmp = *this;
        Iter_Less_less();
        return __tmp;
    }
};
    //compare only de node base
bool operator==(const S_RB_Tree_iterator& it1, const S_RB_Tree_iterator& it2)
{ return it1.N_ptr == it2.N_ptr; }

bool operator!=(const S_RB_Tree_iterator& it1, const S_RB_Tree_iterator& it2)
{ return it1.N_ptr != it2.N_ptr; }

    //the red black tree operand
    //rotate left the node N
void    RB_Tree_rotate_left(S_Node* N, S_Node*& Root)
{
    S_Node* tmp;

    tmp = N->rightChild;
    N->rightChild = tmp->leftChild;
    if (tmp->leftChild != nullptr)
        tmp->leftChild->Parent = N;
    tmp->Parent = N->Parent;
    if (N == Root)
        Root = tmp;
    else if (N == N->Parent->leftChild)
        N->Parent->leftChild = tmp;
    else
        N->Parent->rightChild = tmp;
    tmp->leftChild = N;
    N->Parent = tmp;
}

    //rotate right the node N
void    RB_Tree_rotate_right(S_Node* N, S_Node*& Root)
{
    S_Node* tmp;

    tmp = N->leftChild;
    N->leftChild = tmp->rightChild;
    if (tmp->rightChild != nullptr)
        tmp->rightChild->Parent = N;
    tmp->Parent = N->Parent;
    if (N == Root)
        Root = tmp;
    else if (N == N->Parent->rightChild)
        N->Parent->rightChild = tmp;
    else
        N->Parent->leftChild = tmp;
    tmp->rightChild = N;
    N->Parent = tmp;
}

void    RB_Tree_balance(S_Node* N, S_Node*& Root)
{
    N->Color |= __RBT_RED;
    while (N != Root && N->Parent->Color & __RBT_RED)
    {
        // check the end of NBT
        if (N->Parent == N->Parent->Parent->leftChild)
        {
            //if the rotation is necessary
            if (N->Parent->Parent->rightChild && N->Parent->Parent->rightChild->Color & __RBT_RED)
            {
                N->Parent->Color |= __RBT_BLACK;
                N->Parent->Parent->rightChild->Color |= __RBT_BLACK;
                N->Parent->Parent->Color |= __RBT_RED;
                N = N->Parent->Parent;
            }
            else//do the right rotation
            {
                if (N == N->Parent->rightChild)
                {
                    N = N->Parent;
                    RB_Tree_rotate_left(N, Root);
                }
                N->Parent->Color |= __RBT_BLACK;
                N->Parent->Parent->Color |= __RBT_RED;
                RB_Tree_rotate_right(N->Parent->Parent, Root);
            }
        }
        else// check the start of NBT
        {
            //if the rotation is necessary
            if (N->Parent->Parent->leftChild && N->Parent->Parent->leftChild->Color & __RBT_RED)
            {
                N->Parent->Color |= __RBT_BLACK;
                N->Parent->Parent->leftChild->Color |= __RBT_BLACK;
                N->Parent->Parent->Color |= __RBT_RED;
                N = N->Parent->Parent;
            }
            else//do the left rotation
            {
                if (N == N->Parent->leftChild)
                {
                    N = N->Parent;
                    RB_Tree_rotate_right(N, Root);
                }
                N->Parent->Color |= __RBT_BLACK;
                N->Parent->Parent->Color |= __RBT_RED;
                RB_Tree_rotate_left(N->Parent->Parent, Root);
            }
        }
    }
    Root->Color = __RBT_BLACK;
}

S_Node::Node_ptr RB_Tree_del_balance(S_Node::Node_ptr __z, S_Node::Node_ptr& __root,
                                     S_Node::Node_ptr& __leftmost,S_Node::Node_ptr& __rightmost)
{
    S_Node::Node_ptr __y = __z;
    S_Node::Node_ptr __x = 0;
    S_Node::Node_ptr __x_parent = 0;
    if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
        __x = __y->_M_right;     // __x might be null.
    else
    if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
        __x = __y->_M_left;    // __x is not null.
    else {                   // __z has two non-null children.  Set __y to
        __y = __y->_M_right;   //   __z's successor.  __x might be null.
        while (__y->_M_left != 0)
            __y = __y->_M_left;
        __x = __y->_M_right;
    }
    if (__y != __z) {          // relink y in place of z.  y is z's successor
        __z->_M_left->_M_parent = __y;
        __y->_M_left = __z->_M_left;
        if (__y != __z->_M_right) {
            __x_parent = __y->_M_parent;
            if (__x) __x->_M_parent = __y->_M_parent;
            __y->_M_parent->_M_left = __x;      // __y must be a child of _M_left
            __y->_M_right = __z->_M_right;
            __z->_M_right->_M_parent = __y;
        }
        else
            __x_parent = __y;
        if (__root == __z)
            __root = __y;
        else if (__z->_M_parent->_M_left == __z)
            __z->_M_parent->_M_left = __y;
        else
            __z->_M_parent->_M_right = __y;
        __y->_M_parent = __z->_M_parent;
        __STD::swap(__y->_M_color, __z->_M_color);
        __y = __z;
        // __y now points to node to be actually deleted
    }
    else {                        // __y == __z
        __x_parent = __y->_M_parent;
        if (__x) __x->_M_parent = __y->_M_parent;
        if (__root == __z)
            __root = __x;
        else
        if (__z->_M_parent->_M_left == __z)
            __z->_M_parent->_M_left = __x;
        else
            __z->_M_parent->_M_right = __x;
        if (__leftmost == __z)
            if (__z->_M_right == 0)        // __z->_M_left must be null also
                __leftmost = __z->_M_parent;
                // makes __leftmost == _M_header if __z == __root
            else
                __leftmost = _Rb_tree_node_base::_S_minimum(__x);
        if (__rightmost == __z)
            if (__z->_M_left == 0)         // __z->_M_right must be null also
                __rightmost = __z->_M_parent;
                // makes __rightmost == _M_header if __z == __root
            else                      // __x == __z->_M_left
                __rightmost = _Rb_tree_node_base::_S_maximum(__x);
    }
    if (__y->_M_color != _S_rb_tree_red) {
        while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))
            if (__x == __x_parent->_M_left) {
                _Rb_tree_node_base* __w = __x_parent->_M_right;
                if (__w->_M_color == _S_rb_tree_red) {
                    __w->_M_color = _S_rb_tree_black;
                    __x_parent->_M_color = _S_rb_tree_red;
                    _Rb_tree_rotate_left(__x_parent, __root);
                    __w = __x_parent->_M_right;
                }
                if ((__w->_M_left == 0 ||
                     __w->_M_left->_M_color == _S_rb_tree_black) &&
                    (__w->_M_right == 0 ||
                     __w->_M_right->_M_color == _S_rb_tree_black)) {
                    __w->_M_color = _S_rb_tree_red;
                    __x = __x_parent;
                    __x_parent = __x_parent->_M_parent;
                } else {
                    if (__w->_M_right == 0 ||
                        __w->_M_right->_M_color == _S_rb_tree_black) {
                        if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
                        __w->_M_color = _S_rb_tree_red;
                        _Rb_tree_rotate_right(__w, __root);
                        __w = __x_parent->_M_right;
                    }
                    __w->_M_color = __x_parent->_M_color;
                    __x_parent->_M_color = _S_rb_tree_black;
                    if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
                    _Rb_tree_rotate_left(__x_parent, __root);
                    break;
                }
            } else {                  // same as above, with _M_right <-> _M_left.
                _Rb_tree_node_base* __w = __x_parent->_M_left;
                if (__w->_M_color == _S_rb_tree_red) {
                    __w->_M_color = _S_rb_tree_black;
                    __x_parent->_M_color = _S_rb_tree_red;
                    _Rb_tree_rotate_right(__x_parent, __root);
                    __w = __x_parent->_M_left;
                }
                if ((__w->_M_right == 0 ||
                     __w->_M_right->_M_color == _S_rb_tree_black) &&
                    (__w->_M_left == 0 ||
                     __w->_M_left->_M_color == _S_rb_tree_black)) {
                    __w->_M_color = _S_rb_tree_red;
                    __x = __x_parent;
                    __x_parent = __x_parent->_M_parent;
                } else {
                    if (__w->_M_left == 0 ||
                        __w->_M_left->_M_color == _S_rb_tree_black) {
                        if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
                        __w->_M_color = _S_rb_tree_red;
                        _Rb_tree_rotate_left(__w, __root);
                        __w = __x_parent->_M_left;
                    }
                    __w->_M_color = __x_parent->_M_color;
                    __x_parent->_M_color = _S_rb_tree_black;
                    if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
                    _Rb_tree_rotate_right(__x_parent, __root);
                    break;
                }
            }
        if (__x) __x->_M_color = _S_rb_tree_black;
    }
    return __y;
}

template <class T, class Alloc>
struct _Rb_tree
{
    typedef Alloc           allocator_type;

    allocator_type get_allocator() const { return allocator_type(); }

    _Rb_tree(const allocator_type&): _M_header(0) { _M_header = _M_get_node(); }

    ~_Rb_tree_base() { _M_put_node(_M_header); }

protected:
    _Rb_tree_node<_Tp>* _M_header; // 实现的一个技巧

    typedef simple_alloc<_Rb_tree_node<_Tp>, _Alloc> _Alloc_type;

    _Rb_tree_node<_Tp>* _M_get_node()
    { return _Alloc_type::allocate(1); }
    void _M_put_node(_Rb_tree_node<_Tp>* __p)
    { _Alloc_type::deallocate(__p, 1); }


template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<s_node<Key> > >
class red_black_tree{
public:
    typedef Key                                                                 key_type;
    typedef Key                                                                 value_type;
    typedef std::size_t                                                         size_type;
    typedef std::ptrdiff_t                                                      difference_type;
    typedef Compare                                                             key_compare;
    typedef Compare                                                             value_compare;
    typedef Allocator                                                           allocator_type;
    typedef value_type&                                                         reference;
    typedef const value_type&                                                   const_reference;
    typedef typename Allocator::pointer                                         pointer;
    typedef typename Allocator::const_pointer                                   const_pointer;
    typedef typename ft::tree_iterator<value_type>    iterator;
    typedef typename ft::map_iterator<std::bidirectional_iterator_tag, value_type>    const_iterator;
    typedef typename ft::reverse_iterator<iterator>                             reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>                       const_reverse_iterator;


protected:
    //constructor
    red_black_tree() : _first(NULL){}
    explicit red_black_tree(const Compare& comp, const Allocator& alloc = Allocator() )
                                : _first(NULL){}// init the first pointer
    template< class InputIt >
    red_black_tree( InputIt first, InputIt last, const Compare& comp = Compare(),
    const Allocator& alloc = Allocator() ) : _first(NULL)
    { this->insert(first, last); }
    red_black_tree( const red_black_tree& other ) : _first(other._first)
    { this->swap(other); }

    //destructor
    ~red_black_tree(){}//voir pour desaloc

    red_black_tree&     operator=(const red_black_tree& other)
    {
        this->clear();
        this->swap(other);
        return *this;
    }

    allocator_type get_allocator() const {return allocator_type(); }

    iterator begin() { return self.begin(); }
    const_iterator begin() const { return self.begin(); }

    iterator end() { return self.end(); }
    const_iterator end() const { return self.end(); }

    reverse_iterator rbegin() { return self.rbegin(); }
    const_reverse_iterator rbegin() const { return self.rbegin(); }

    std::pair<iterator, bool> insert( const key_type& value )
    {

    }

   iterator insert( iterator pos, const key_type& value )
   {

   }



private:
    typedef red_black_tree<Key>     self_type;
    s_node<key_type>                *_first;

};





__FT_CONTAINER_END_NAMESPACE

#endif //FT_CONTAINER_RED_BLACK_TREE_TPP
