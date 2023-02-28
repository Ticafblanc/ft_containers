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
#include "utility.tpp"
#include "stack.tpp"
#include <functional>
#include <sstream>
#include <deque>
#include <queue>
#include <iomanip>
#include <unistd.h>

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


        explicit RedBlackTree() : _root(nullptr), _nul(nullptr), _size(0) { __INFOMF__ };

        ~RedBlackTree() { __INFOMF__ delete_node(_nul);  };

    /*
    *====================================================================================
    *|                                    Move                                         |
    *====================================================================================
    */

        void init(Key* value){
            _root = _nul = create_node(BLACK);
            _nul->_Key = value;
        };

        bool isNul(Node* node) const {
            return (node == nullptr || node == _nul);
        };

        bool isRoot(Node* node) const {
            return (node == _root);
        };

        bool isRightChild(Node* node){
            return node == node->_Parent->_RightChild;
        };

        bool isLeftChild(Node* node){
            return node == node->_Parent->_LeftChild;
        };

        Node* maximum(Node* node) {
            while (!isNul(node->_RightChild)) {
                node = node->_RightChild;
            }
            return node;
        };

        Node* minimum(Node* node) {
            while (!isNul(node->_LeftChild)) {
                node = node->_LeftChild;
            }
            return node;
        };

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
            if (isNul(node))
               return maximum(_root);
            if (!isNul(node->_LeftChild))
                return maximum(node->_LeftChild);
            Node* rnode = node->_Parent;
            while (!isNul(rnode) && node == rnode->_LeftChild) {
                node = rnode;
                rnode = rnode->_Parent;
            }
            return rnode;
        };

    /*
    *====================================================================================
    *|                                    utility                                       |
    *====================================================================================
    */


        /*call constructor non void de Node and new Node */
        Node*   create_node(Color color){
            return new Node(color,  _nul);
        };

        /*delete node and call the destructor of Node*/
        Key*    delete_node(Node* node){
            Key* save = node->_Key;
            delete node;
            return save;
        };

        /*find value in the tree and return Node * to the pos
         * or retur the _nul node*/
        template<class compare>
        Node*   finds(const Key& value, Node* rnode, compare comp ) const {
            while (!isNul(rnode) && (*(rnode->_Key) != value)) {
                if (comp(value, *(rnode->_Key)))
                    rnode = rnode->_LeftChild;
                else
                    rnode = rnode->_RightChild;
            }
            return rnode;
        };


        Node* transplant(Node* node_to_delete, Node* node_to_transplant) {
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
        template<typename Compare>
        Node* greater_or_equal(const Key& value, Compare comp) const {
            Node* forward_root = _root;
            Node* save = _nul;
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
         * return Node* to pos*/
        template<typename Compare>
        ft::pair<Node*, bool> insertn(const Key& value, Node* forward_root, Compare& comp ) {
            __INFOMO__
            if (isNul(forward_root)
                || comp(*forward_root->_Key, *successor(forward_root)->_Key)
                || comp(*predecessor(forward_root)->_Key, *forward_root->_Key))
                forward_root = _root;
            Node* destination_node = _nul;
            while (!isNul(forward_root)) {
                destination_node = forward_root;
                if (*(forward_root->_Key) == value)
                    return ft::make_pair(destination_node, false);
                if (comp(value, *(forward_root->_Key)))
                    forward_root = forward_root->_LeftChild;
                else
                    forward_root = forward_root->_RightChild;
            }
            Node* new_node = create_node(RED);
            new_node->_Parent = destination_node;
            if (isNul(destination_node))
                _root = new_node;
            else if (comp(value, *(destination_node->_Key)))
                destination_node->_LeftChild = new_node;
            else
                destination_node->_RightChild = new_node;
            insertFixup(new_node);
            _size++;
            __INFOMONL__
            return ft::make_pair(new_node, true);
        };


    /*
    *====================================================================================
    *|                                    Erase                                         |
    *====================================================================================
    */
        /*Removes the element at pos delete data Key with specific allocator in set
         * return node* to replace it*/
        ft::pair<Node*, Key*> erases(Node* pos) {
            __INFOMO__
            if (isNul(pos))
                return  ft::make_pair(pos, nullptr);
            Node* trans;
            Color original_color = pos->_Color;
            if (isNul(pos->_LeftChild))
                trans = transplant(pos, pos->_RightChild);
            else if (isNul(pos->_RightChild))
                trans = transplant(pos, pos->_LeftChild);
            else {
                Node* next = minimum(pos->_RightChild);
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
            if (original_color == BLACK)
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
        void rotateLeft(Node* node) {
            Node* tmp = node->_RightChild;
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
        void rotateRight(Node* node) {
            Node* tmp = node->_LeftChild;
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
        void insertFixup(Node* new_node) {
            Node* check;
            while (new_node->_Parent->_Color == RED) {
                if (isLeftChild(new_node->_Parent)) {
                    check = new_node->_Parent->_Parent->_RightChild;
                    if (check->_Color == RED) {
                        new_node->_Parent->_Color = BLACK;
                        check->_Color = BLACK;
                        new_node->_Parent->_Parent->_Color = RED;
                        new_node = new_node->_Parent->_Parent;
                    } else {
                        if (isRightChild(new_node)) {
                            new_node = new_node->_Parent;
                            rotateLeft(new_node);
                        }
                        new_node->_Parent->_Color = BLACK;
                        new_node->_Parent->_Parent->_Color = RED;
                        rotateRight(new_node->_Parent->_Parent);
                    }
                } else {
                    check = new_node->_Parent->_Parent->_LeftChild;
                    if (check->_Color == RED) {
                        new_node->_Parent->_Color = BLACK;
                        check->_Color = BLACK;
                        new_node->_Parent->_Parent->_Color = RED;
                        new_node = new_node->_Parent->_Parent;
                    } else {
                        if (isLeftChild(new_node)) {
                            new_node = new_node->_Parent;
                            rotateRight(new_node);
                        }
                        new_node->_Parent->_Color = BLACK;
                        new_node->_Parent->_Parent->_Color = RED;
                        rotateLeft(new_node->_Parent->_Parent);
                    }
                }
            }
            _root->_Color = BLACK;
        };

        /*balance tree after delete*/
        void deleteFixup(Node* transplant) {
            Node* check;
            while (transplant != _root && transplant->_Color == BLACK) {
                if (transplant == transplant->_Parent->_LeftChild) {
                    check= transplant->_Parent->_RightChild;
                    if (check->_Color == RED) {
                        check->_Color = BLACK;
                        transplant->_Parent->_Color = RED;
                        rotateLeft(transplant->_Parent);
                        check = transplant->_Parent->_RightChild;
                    }
                    if (check->_LeftChild->_Color == BLACK && check->_RightChild->_Color == BLACK) {
                        check->_Color = RED;
                        transplant = transplant->_Parent;
                    } else {
                        if (check->_RightChild->_Color == BLACK) {
                            check->_LeftChild->_Color = BLACK;
                            check->_Color = RED;
                            rotateRight(check);
                            check = transplant->_Parent->_RightChild;
                        }
                        check->_Color = transplant->_Parent->_Color;
                        transplant->_Parent->_Color = BLACK;
                        check->_RightChild->_Color = BLACK;
                        rotateLeft(transplant->_Parent);
                        transplant = _root;
                    }
                } else {
                    check = transplant->_Parent->_LeftChild;
                    if (check->_Color == RED) {
                        check->_Color = BLACK;
                        transplant->_Parent->_Color = RED;
                        rotateRight(transplant->_Parent);
                        check = transplant->_Parent->_LeftChild;
                    }
                    if (check->_RightChild->_Color == BLACK && check->_LeftChild->_Color == BLACK) {
                        check->_Color = RED;
                        transplant = transplant->_Parent;
                    } else {
                        if (check->_LeftChild->_Color == BLACK) {
                            check->_RightChild->_Color = BLACK;
                            check->_Color = RED;
                            rotateLeft(check);
                            check = transplant->_Parent->_LeftChild;
                        }
                        check->_Color = transplant->_Parent->_Color;
                        transplant->_Parent->_Color = BLACK;
                        check->_LeftChild->_Color = BLACK;
                        rotateRight(transplant->_Parent);
                        transplant = _root;
                    }
                }
            }
            transplant->_Color = BLACK;
        };

    /*
    *====================================================================================
    *|                                    printTest                                     |
    *====================================================================================
    */

        void printSubtree(Node* node, int level, const std::deque<bool>& branches) {
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
            else if (node->_Color == BLACK )
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
    };/*end of Red_black_tree*/
    /*
    *====================================================================================
    *|                                    iterator                                      |
    *====================================================================================
    */

    template<class Key>
    struct rbtiterator : public std::iterator<std::bidirectional_iterator_tag,
            Key, Key, const Key *, Key> {

        typedef nodeSet<Key>                     Node;
        Node*                                   _node;
        RedBlackTree<Key, Node>*                _tree;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

        rbtiterator() : _node(nullptr), _tree(nullptr){};

        explicit rbtiterator(Node* tmp, ft::RedBlackTree<Key, Node>* _tree) : _node(tmp), _tree(_tree){};

        rbtiterator(const rbtiterator &other) : _node(other._node) , _tree(other._tree){};

        ~rbtiterator(){};

        rbtiterator& operator=(const rbtiterator& other){
            _node = other._node;
            _tree = other._tree;
            return *this;
        };
    /*
    *====================================================================================
    *|                                  overload operator                               |
    *====================================================================================
    */

        Key& operator*() const { return *(_node->_Key); }
        Key* operator->() const { return &(operator*()); }

        rbtiterator& operator++() {
//            std::cout << "coucou " << std::endl;

            _node = _tree->successor(_node);
            return *this;
        };

        rbtiterator operator++(int) {
//            std::cout << "coucou " << std::endl;

            const rbtiterator Tmp = *this;
            _node = _tree->successor(_node);
            return Tmp;
        };

        rbtiterator& operator--() {
//            std::cout << "coucou " << std::endl;

            _node = _tree->predecessor(_node);
            return *this;
        };

        rbtiterator  operator--(int) {
//            std::cout << "coucou " << std::endl;

            const rbtiterator Tmp = *this;
            _node = _tree->predecessor(_node);
            return Tmp;
        };

        bool operator==(const rbtiterator& rhs) const { return _node == rhs._node; };

        bool operator!=(const rbtiterator& rhs) const { return !(*this == rhs); };


    };/*end of iterator*/


/*
*====================================================================================
*|                                 Non Membre fonction                              |
*====================================================================================
*/


__FT_CONTAINERS_END_NAMESPACE


#endif //FT_CONTAINERS_RED_BLACK_TREE_TPP
