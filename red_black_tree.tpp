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

#include <iostream>
#include <cstdlib>
#include "ft_containers.hpp"
#include "type_traits.tpp"
#include "algorithm.tpp"
#include "node.tpp"

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


    template< class Key, class Node >
    struct RedBlackTree {

        typedef RedBlackTree<Key, Node>                     _self;
        Node                                                *_root;
        Node                                                *_nul;
        std::size_t                                         _size;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

        RedBlackTree() : _root(_nul), _nul(new Node()), _size(0) { __INFOMF__ };

        ~RedBlackTree() { __INFOMF__ };

    /*
    *====================================================================================
    *|                                    Move                                         |
    *====================================================================================
    */

        bool isNul(Node* node) const {
            return (node == nullptr || node == _nul);
        }

        Node* maximum(Node* node) {
            while (!isNul(node->_RightChild)) {
                node = node->_RightChild;
            }
            return node;
        }

        Node* minimum(Node* node) {
            while (!isNul(node->_LeftChild)) {
                node = node->_LeftChild;
            }
            return node;
        }

        Node* successor(Node* node) {
            if (!isNul(node->_RightChild))
                return minimum(node->_RightChild);
            Node* rnode = node->_Parent;
            while (!isNul(rnode) && node == rnode->_RightChild) {
                node = rnode;
                rnode = rnode->_Parent;
            }
            return rnode;
        };

        Node* predecessor(Node* node) {
            if (!isNul(node->_LeftChild))
                return maximum(node->_LeftChild);
            Node* rnode = node->_Parent;
            while (!isNul(rnode) && node == rnode->_LeftChild) {
                node = rnode;
                rnode = rnode->_Parent;
            }
            return rnode;
        }

    /*
    *====================================================================================
    *|                                    utility                                       |
    *====================================================================================
    */

        bool    keyComp(Key lhs, Key rhs, bool (*initFunc)(Key, Key) = nullptr){
            static bool (*Func)(Key, Key);
            if (initFunc != nullptr) {
                Func = initFunc;
                return true;
            }
            return Func(lhs, rhs);
        }

        Key*    keyConstruct(const Key& value, Key* (initFuncAlloc)(std::size_t) = nullptr,
                             void (*initFuncConstruct)(Key*, const Key&) = nullptr){
            static Key* (*FuncAlloc)(std::size_t);
            static Key* (*FuncConstruct)(Key*, const Key&);
            if (initFuncAlloc != nullptr && initFuncConstruct != nullptr) {
                FuncAlloc = initFuncAlloc;
                FuncConstruct = initFuncConstruct;
                return true;
            }
            Key* rkey = FuncAlloc(1);
            FuncConstruct(rkey, value);
            return rkey;
        }

        Key*    keyDestroy(const Key& value, Key* (initFuncAlloc)(std::size_t) = nullptr,
                             void (*initFuncConstruct)(Key*, const Key&) = nullptr){
            static Key* (*FuncAlloc)(std::size_t);
            static Key* (*FuncConstruct)(Key*, const Key&);
            if (initFuncAlloc != nullptr && initFuncConstruct != nullptr) {
                FuncAlloc = initFuncAlloc;
                FuncConstruct = initFuncConstruct;
                return true;
            }
            Key* rkey = FuncAlloc(1);
            FuncConstruct(rkey, value);
            return rkey;
        }

        Node* find(Key value, bool (*comp_func)(Key, Key)) {
            Node* rnode = _root;
            while (!isNul(rnode) && rnode->_Key != value) {
                if (value < rnode->_Key)
                    rnode = rnode->_LeftChild;
                else
                    rnode = rnode->_RightChild;
            }
            return rnode;
        }

        /*update size of container*/
        void fixup_size(Node* x) {
            std::size_t left_size = (x->_LeftChild == _nul) ? 0 : x->left->size;
            std::size_t right_size = (x->_RightChild == _nul) ? 0 : x->right->size;
            x->size = left_size + right_size + 1;
        }

        /*Erases all elements from the treee*/
        void clear(void (*delete_func)(Key*)) {__INFOMO__ clear_tree(_root, delete_func); _root = _nul; __INFOMONL__ };

        void clear_tree(Node* x, void (*delete_func)(Key*)) {
            if (x != _nul) {
                clear_tree(x->_LeftChild, delete_func);
                clear_tree(x->_RightChild, delete_func);
                if (delete_func != nullptr)
                    delete_func(x->data);
                delete x;
            }
        }

    /*
    *====================================================================================
    *|                                    Insert                                        |
    *====================================================================================
    */
        /* find place with spec func to copmpare and add new node fo inserts value.*/
        Node* insert(const Key value, bool (*comp_func)(Key, Key)) {
            __INFOMO__
            Node* z = new Node(value, RED);
            Node* y = _nul;
            Node* x = _root;
            while (x != _nul) {
                y = x;
                if (comp_func(*z->_Key, *x->_Key))
                    x = x->_LeftChild;
                else
                    x = x->_RightChild;
            }
            z->_Parent = y;
            if (y == _nul)
                _root = z;
            else if (comp_func(*z->_Key, *y->_Key))
                y->_LeftChild = z;
            else
                y->_RightChild = z;
            z->_LeftChild = _nul;
            z->_RightChild = _nul;
            z->_Color = RED;
            insertFixup(z);
            __INFOMONL__
        };

        void transplant(Node* u, Node* v) {
            if (u->_Parent == _nul)
                _root = v;
            else if (u == u->_Parent->_LeftChild)
                u->_Parent->_LeftChild = v;
            else
                u->_Parent->_RightChild = v;
            v->_Parent = u->_Parent;
        };

    /*
    *====================================================================================
    *|                                    Erase                                         |
    *====================================================================================
    */
        /*Removes the element at pos delete data Key with specific allocator in set*/
        Node* erase(Node* pos, void (*delete_func)(Key*)) {
            __INFOMO__
            if (pos == _nul)
                return;
            Node* x;
            Node* y = pos;
            Color y_original_color = y->_Color;
            if (pos->_LeftChild == _nul) {
                x = pos->right;
                transplant(pos, pos->right);
                x = pos->right;
            } else if (pos->right == _nul) {
                x = pos->_LeftChild;
                transplant(pos, pos->_LeftChild);
                x = pos->_LeftChild;
            } else {
                y = minimum(pos->right);
                y_original_color = y->color;
                x = y->right;
                if (y->_Parent == pos)
                    x->_Parent = y;
                else {
                    transplant(y, y->right);
                    y->right = pos->right;
                    y->right->parent = y;
                }
                transplant(pos, y);
                y->left = pos->left;
                y->left->parent = y;
                y->color = pos->color;
            }
            if (y_original_color == BLACK)
                deleteFixup(x);
            delete_func(x->_Key);
            x = successor(pos);
            delete pos;
            __INFOMONL__
            return x;
        };

    /*
    *====================================================================================
    *|                                    Balance                                       |
    *====================================================================================
    */

        /*rotate Node X */
        void rotateLeft(Node* x) {
            Node* y = x->_RightChild;
            x->_RightChild = y->_LeftChild;
            if (y->_LeftChild != _nul)
                y->_LeftChild->_Parent = x;
            y->_Parent = x->_Parent;
            if (x->_Parent == _nul)
                _root = y;
            else if (x == x->_Parent->_LeftChild)
                x->_Parent->_LeftChild = y;
            else
                x->_Parent->_RightChild = y;
            y->_LeftChild = x;
            x->_Parent = y;
        };

        /*rotate Node X */
        void rotateRight(Node* x) {
            Node* y = x->_LeftChild;
            x->_LeftChild = y->_RightChild;
            if (y->_RightChild != _nul)
                y->_RightChild->_Parent = x;
            y->_Parent = x->_Parent;
            if (x->_Parent == _nul)
                _root = y;
            else if (x == x->_Parent->_RightChild)
                x->_Parent->_RightChild = y;
            else
                x->_Parent->_LeftChild = y;
            y->_RightChild = x;
            x->_Parent = y;
        };

        /*balance tree after insert*/
        void insertFixup(Node* z) {
            while (z->_Parent->_Color == RED) {
                if (z->_Parent == z->_Parent->_Parent->_LeftChild) {
                    Node* y = z->_Parent->_Parent->_RightChild;
                    if (y->_Color == RED) {
                        z->_Parent->_Color = BLACK;
                        y->_Color = BLACK;
                        z->_Parent->_Parent->_Color = RED;
                        z = z->_Parent->_Parent;
                    } else {
                        if (z == z->_Parent->_RightChild) {
                            z = z->_Parent;
                            rotateLeft(z);
                        }
                        z->_Parent->_Color = BLACK;
                        z->_Parent->_Parent->_Color = RED;
                        rotateRight(z->_Parent->_Parent);
                    }
                } else {
                    Node* y = z->_Parent->_Parent->_LeftChild;
                    if (y->_Color == RED) {
                        z->_Carent->_Color = BLACK;
                        y->_Color = BLACK;
                        z->_Parent->_Parent->_Color = RED;
                        z = z->_Parent->_Parent;
                    } else {
                        if (z == z->_Parent->_LeftChild) {
                            z = z->_Parent;
                            rotateRight(z);
                        }
                        z->_Parent->_Color = BLACK;
                        z->_Parent->_Parent->_Color = RED;
                        rotateLeft(z->_Parent->_Parent);
                    }
                }
            }
            _root->color = BLACK;
        };

        /*balance tree after delete*/
        void deleteFixup(Node* x) {
            while (x != _root && x->_Color == BLACK) {
                if (x == x->_Parent->_LeftChild) {
                    Node* w = x->_Parent->_RightChild;
                    if (w->_Color == RED) {
                        w->_Color = BLACK;
                        x->_Parent->_Color = RED;
                        rotateLeft(x->_Parent);
                        w = x->_Parent->_RightChild;
                    }
                    if (w->_LeftChild->_Color == BLACK && w->_RightChild->_Color == BLACK) {
                        w->_Color = RED;
                        x = x->_Parent;
                    } else {
                        if (w->_RightChild->_Color == BLACK) {
                            w->_LeftChild->_Color = BLACK;
                            w->_Color = RED;
                            rotateRight(w);
                            w = x->_Parent->_RightChild;
                        }
                        w->_Color = x->_Parent->_Color;
                        x->_Parent->_Color = BLACK;
                        w->_RightChild->_Color = BLACK;
                        rotateLeft(x->_Parent);
                        x = _root;
                    }
                } else {
                    Node* w = x->_Parent->_LeftChild;
                    if (w->_Color == RED) {
                        w->_Color = BLACK;
                        x->_Parent->_Color = RED;
                        rotateRight(x->_Parent);
                        w = x->_Parent->_LeftChild;
                    }
                    if (w->_RightChild->_Color == BLACK && w->_LeftChild->_Color == BLACK) {
                        w->_Color = RED;
                        x = x->_Parent;
                    } else {
                        if (w->_LeftChild->_Color == BLACK) {
                            w->_RightChild->_Color = BLACK;
                            w->_Color = RED;
                            rotateLeft(w);
                            w = x->_Parent->_LeftChild;
                        }
                        w->_Color = x->_Parent->_Color;
                        x->_Parent->_Color = BLACK;
                        w->_LeftChild->_Color = BLACK;
                        rotateRight(x->_Parent);
                        x = _root;
                    }
                }
            }
            x->color = BLACK;
        };

    /*
    *====================================================================================
    *|                                    printTest                                     |
    *====================================================================================
    */

        void inorderTraversal(Node* node) {
            if (node == _nul)
                return;

            inorderTraversal(node->left);
            system("Color 70");
            if (node->_Color == RED)
                system("Color 74");
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }

        void printTree() {
            inorderTraversal(_root);
            std::cout << std::endl;
        }
};

/*
*====================================================================================
*|                                 Non Membre fonction                              |
*====================================================================================
*/


__FT_CONTAINERS_END_NAMESPACE

namespace std {
    template< class Key, class Node, class Compare, class Allocator >
    inline void swap(ft::RedBlackTree< Key, Node>& lhs,
                     ft::RedBlackTree< Key, Node> &rhs)
    {__INFOMO__ lhs.swap(rhs); __INFOMONL__ };
}

#endif //FT_CONTAINERS_RED_BLACK_TREE_TPP
