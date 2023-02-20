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

    protected:

        typedef RedBlackTree<Key, Node>                     _self;
        bool    (*Comp)(Key, Key);
        Key*    (*Alloc)( std::size_t );
        void    (*Construct)(Key*, const Key&);
        void    (*Destroy)(Key*);
        void    (*Dealloc)(Key*, std::size_t);
        Node                                                *_root;
        Node                                                *_nul;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

    protected:

        explicit RedBlackTree( bool  (*initComp)      (Key, Key)          = &std::less<Key>(),
                               Key*  (*initAlloc)     (std::size_t)       = &std::allocator<Key>::allocate(),
                               Key*  (*initConstruct) (const Key&)        = &std::allocator<Key>::construct(),
                               void  (*initDestroy)   (const Key*)        = &std::allocator<Key>::destroy(),
                               void  (*initDealloc)   (Key*, std::size_t) = &std::allocator<Key>::deallocate())
                : Comp(initComp), Alloc(initAlloc), Construct(initConstruct), Destroy(initDestroy),
                Dealloc(initDealloc), _nul(create_node()), _root(_nul){ __INFOMF__ };

        RedBlackTree(const _self &other)
                : Comp(other.Comp), Alloc(other.Alloc), Construct(other.Construct), Destroy(other.Destroy),
                Dealloc(other.Dealloc), _nul(create_node(other._nul)), _root(copy_tree(other._root)){}

        ~RedBlackTree() { __INFOMF__ clear(); };

    /*
    *====================================================================================
    *|                                    Move                                         |
    *====================================================================================
    */

    private:

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

    private:

        /*call constructor void non void de Node and new Node */
        Node*   create_node(){
            return new Node();
        };

        /*call constructor non void de Node and new Node */
        Node*   create_node(Key& value, Color color){
            return new Node(value, color,  _nul, Comp, Alloc, Construct, Destroy, Dealloc);
        };

        /*call copy constructor de Node and new Node*/
        Node*   create_node(Node * node){
            return new Node(*node);
        };

        /*delete node and call the destructor of Node*/
        void    delete_node(Node* node){
            delete node;
        };

        /*find value in the tree and return Node * to the pos
         * or retur the _nul node*/
        Node*   find(Key& value, Node* rnode) {
            while (!isNul(rnode) && *(rnode->_Key) != value) {
                if (value < *(rnode->_Key))
                    rnode = rnode->_LeftChild;
                else
                    rnode = rnode->_RightChild;
            }
            return rnode;
        };

        /*update size of container*/
        void fixup_size(Node* node) {
            std::size_t left_size = (isNul(node->_LeftChild)) ? 0 : node->left->size;
            std::size_t right_size = (isNul(node->_LeftChild)) ? 0 : node->right->size;
            node->size = left_size + right_size + 1;
        };

        /*Erases all elements from the treee*/
        void clear() {__INFOMO__ clear_tree(_root); _root = _nul; __INFOMONL__ };

        /*Erases all elements from the treee start at _root*/
        void clear_tree(Node* node) {
            if (!isNul(node)) {
                clear_tree(node->_LeftChild);
                clear_tree(node->_RightChild);
                delete_node(node);
            }
        };

        Node* transplant(Node* node_to_delete, Node* node_to_transplant) {
            if (isNul(node_to_delete->_Parent))
                _root = node_to_transplant;
            else if (isLeftChild(node_to_delete))
                node_to_delete->_Parent->_LeftChild = node_to_transplant;
            else
                node_to_delete->_Parent->_RightChild = node_to_transplant;
            node_to_transplant->_Parent = node_to_delete->_Parent;
            fixup_size(node_to_delete);
            fixup_size(node_to_transplant);
            return node_to_transplant;
        };

        /*copy the tree start at _root*/
        Node* copy_tree(Node* node) {
            if (isNul(node)) {
                return _nul;
            }
            Node *new_node = create_node(node);
            new_node->_LeftChild = copy_tree(node->_LeftChild);
            new_node->_RightChild = copy_tree(node->_RightChild);
            new_node->_Parent = _nul;
            if (!isNul(new_node->_LeftChild)) {
                new_node->_LeftChild->_Parent = new_node;
            }
            if (!isNul(new_node->_RightChild)) {
                new_node->_RightChild->_Parent = new_node;
            }
            return new_node;
        };

        void swap(_self& other) {
            std::swap(Comp, other.Comp);
            std::swap(Construct, other.Construct);
            std::swap(Alloc, other.Alloc);
            std::swap(Destroy, other.Destroy);
            std::swap(Dealloc, other.Dealloc);
            std::swap(_root, other._root);
            std::swap(_nul, other._nul);
        };

        Node* greater_or_equal(Key& value){
            Node* forward_root = _root;
            Node* save = _nul;
            while (!(isNul(forward_root))) {
                if (forward_root->_Key >= value) {
                    save = forward_root;
                    forward_root = forward_root->_LeftChild;
                }
                else {
                    forward_root = forward_root->_RightChild;
                }
            }
            return save;
        }

    /*
    *====================================================================================
    *|                                    Insert                                        |
    *====================================================================================
    */

    private:

        /* find place with spec func to compare and add new node fo inserts value.
         * return Node* to pos*/
        Node* insert(const Key& value, Node* forward_root) {
            __INFOMO__
            Node* destination_node = _nul;
            while (!isNul(forward_root)) {
                destination_node = forward_root;
                if (value == *(forward_root->_Key))
                    return forward_root;
                if (value < *(forward_root->_Key))
                    forward_root = forward_root->_LeftChild;
                else
                    forward_root = forward_root->_RightChild;
            }
            Node* new_node = create_node(value, RED);
            new_node->_Parent = destination_node;
            if (isNul(destination_node))
                _root = new_node;
            else if (*(new_node->_Key) < *(destination_node->_Key))
                destination_node->_LeftChild = new_node;
            else
                destination_node->_RightChild = new_node;
            fixup_size(new_node);
            insertFixup(new_node);
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
        Node* erase(Node* pos) {
            __INFOMO__
            if (isNul(pos))
                return;
            if (isRoot(pos)){
                delete_node(pos);
                _root = _nul;
                return _root;
            }
            Node* trans;
            Color original_color = pos->_Color;
            if (isNul(pos->_LeftChild))
                trans = transplant(pos, pos->_RightChild);
            else if (isNul(pos->_RightChild))
                trans = transplant(pos, pos->_LeftChild);
            else {
                Node* next = minimum(pos->_RightChild);
                original_color = next->color;
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
            fixup_size(trans);
            delete_node(pos);
            __INFOMONL__
            return trans;
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
            fixup_size(tmp->_LeftChild);
            fixup_size(tmp->_RightChild);
            fixup_size(tmp);
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
            fixup_size(tmp->_LeftChild);
            fixup_size(tmp->_RightChild);
            fixup_size(tmp);
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
                        new_node->_Carent->_Color = BLACK;
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
            transplant->color = BLACK;
        };

    /*
    *====================================================================================
    *|                                    printTest                                     |
    *====================================================================================
    */

        void inorderTraversal(Node* node) {
            if (isNul(node))
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

    void print() const {
        if (isNul(_root)) {
            std::cout << "Empty tree" << std::endl;
            return;
        }
        const std::string kBlackNodeColor = "\033[1;30m";  // Black text
        const std::string kRedNodeColor = "\033[1;31m";    // Red text
        const std::string kResetColor = "\033[0m";         // Reset text color

        ft::stack<Node*> node_stack;
        ft::stack<int> level_stack;

        node_stack.push(_root);
        level_stack.push(0);

        int current_level = 0;
        while (!node_stack.empty()) {
            Node* node = node_stack.top();
            node_stack.pop();

            int level = level_stack.top();
            level_stack.pop();

            if (level != current_level) {
                std::cout << std::endl;
                current_level = level;
            }

            if (node->_Color == BLACK) {
                std::cout << kBlackNodeColor;
            } else {
                std::cout << kRedNodeColor;
            }

            std::cout << node->_Key << " ";
            std::cout << kResetColor;

            if (!isNul(node->right)) {
                node_stack.push(node->right);
                level_stack.push(level + 1);
            }

            if (!isNul(node->left)) {
                node_stack.push(node->left);
                level_stack.push(level + 1);
            }
        }

        std::cout << std::endl;
    }


    /*
    *====================================================================================
    *|                                    iterator                                      |
    *====================================================================================
    */

        struct iterator : public std::iterator<std::bidirectional_iterator_tag,
                Key, Key, const Key *, Key> {

        protected:

            Node*                           _node;

        /*
        *====================================================================================
        *|                                  Member Fonction                                 |
        *====================================================================================
        */

        public:

            iterator() : _node(nullptr){};

            explicit iterator(Node* tmp) : _node(tmp) {};

            iterator(const iterator &other) : _node(other._node) {};

            ~iterator(){};

            iterator& operator=(const iterator& other){
                _node = other._node;
                return *this;
            };
        /*
        *====================================================================================
        *|                                  overload operator                               |
        *====================================================================================
        */
            Key& operator*() const { return *(_node->_Key); }
            Key* operator->() const { return &(operator*()); }

            _self& operator++() {
                _node = successor(_node);
                return *this;
            };

            iterator operator++(int) {
                const iterator Tmp = *this;
                _node = successor(_node);
                return Tmp;
            };

            iterator& operator--() {
                _node = predecessor(_node);
                return *this;
            };

            iterator  operator--(int) {
                const iterator Tmp = *this;
                predecessor(_node);
                return Tmp;
            };

        };/*end of iterator*/

};/*end of Red_black_tree*/

/*
*====================================================================================
*|                                 Non Membre fonction                              |
*====================================================================================
*/


__FT_CONTAINERS_END_NAMESPACE

namespace std {
    template< class Key, class Node>
    inline void swap(ft::RedBlackTree< Key, Node>& lhs,
                     ft::RedBlackTree< Key, Node> &rhs)
    {__INFOMO__ lhs.swap(rhs); __INFOMONL__ };
}

#endif //FT_CONTAINERS_RED_BLACK_TREE_TPP
