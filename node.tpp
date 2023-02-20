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
#include "utility.tpp"

#ifndef FT_CONTAINERS_NODE_TPP
#define FT_CONTAINERS_NODE_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

    enum Color { RED, BLACK };

    template< class Key >
    struct nodeBase {

        typedef nodeBase<Key> _self;
        bool    (*Comp)(Key, Key);
        Key*    (*Alloc)( std::size_t );
        void    (*Construct)(Key*, const Key&);
        void    (*Destroy)(Key*);
        void    (*Dealloc)(Key*, std::size_t);
        Key         *_Key;
        Color       _Color;
        nodeBase    *_LeftChild;
        nodeBase    *_RightChild;
        nodeBase    *_Parent;
        std::size_t _Size;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

        nodeBase() : _Key(nullptr), _Color(BLACK), _LeftChild(nullptr),
                     _RightChild(nullptr), _Parent(nullptr), _Size(0){};

        explicit nodeBase(Key& value, Color color, nodeBase* _nul,
                          bool  (*initComp)      (Key, Key),
                          Key*  (*initAlloc)     (std::size_t),
                          Key*  (*initConstruct) (const Key&),
                          void  (*initDestroy)   (const Key*),
                          void  (*initDealloc)   (Key*, std::size_t))
                : Comp(initComp), Alloc(initAlloc), Construct(initConstruct), Destroy(initDestroy),
                Dealloc(initDealloc), _Key(nullptr), _Color(color), _LeftChild(_nul),
                _RightChild(_nul), _Parent(_nul), _Size(0) {
            _Key = Alloc(1);
            Construct(_Key, value);
        };

        nodeBase(const _self &other)
                : Comp(other.Comp), Alloc(other.Alloc), Construct(other.Construct),
                Destroy(other.Destroy), Dealloc(other.Dealloc), _Key(nullptr),_Color(other._Color),
                _LeftChild(other._LeftChild), _RightChild(other._RightChild), _Parent(other._Parent), _Size(0) {
            _Key = Alloc(1);
            Construct(_Key, *(other._Key));
        };

        ~nodeBase() {
            Destroy(_Key);
            Dealloc(_Key, 1);
        };

    /*
    *====================================================================================
    *|                                  overload operato                                |
    *====================================================================================
    */

        bool operator<(const Key& rhs) const {
            return Comp(_Key, rhs);
        };

        bool operator<=(const Key& rhs) const {
            return !(rhs < *this);
        };

        bool operator>(const Key& rhs) const {
            return rhs < *this;
        };

        bool operator>=(const Key& rhs) const {
            return !(*this < rhs);
        };

        bool operator==(const Key& rhs) const {
            return !(*this < rhs) && !(rhs < *this);
        };

        bool operator!=(const Key& rhs) const {
            return *this < rhs || rhs < *this;
        };

    /*
    *====================================================================================
    *|                                    Modifiers                                     |
    *====================================================================================
    */

        void        swap(_self& other)
        {__INFOMO__

            std::swap(Comp, other.Comp);
            std::swap(Alloc, other.Alloc);
            std::swap(Construct, other.Construct);
            std::swap(Destroy, other.Destroy);
            std::swap(Dealloc, other.Dealloc);
            std::swap(_Key, other._Key);
            std::swap(_Color, other._Color);
            std::swap(_LeftChild, other._LeftChild);
            std::swap(_RightChild, other._RightChild);
            std::swap(_Parent, other._Parent);
            std::swap(_Size, other._Size);

            __INFOMONL__
        };
    };

    template< class Key, class T = void >
    struct node : public nodeBase< ft::pair<Key, T> > {

        typedef nodeBase< ft::pair<Key, T> > base;
        typedef node<Key, T>     self;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

        node() : base() {};

        explicit node(ft::pair<Key, T> value, Color color,
                      bool  (*initComp)      (Key, Key)          = &std::less<Key>(),//a changer
                      Key*  (*initAlloc)     (std::size_t)       = &std::allocator<Key>::allocate(),
                      Key*  (*initConstruct) (const Key&)        = &std::allocator<Key>::construct(),
                      void  (*initDestroy)   (const Key*)        = &std::allocator<Key>::destroy(),
                      void  (*initDealloc)   (Key*, std::size_t) = &std::allocator<Key>::deallocate())
                : base(value, color, initComp, initAlloc, initConstruct, initDestroy, initDealloc){ };

        node(const self &other) : base(other){ };

        ~node() {};
    };

    template< class Key >
    struct node< Key > : public nodeBase< Key > {

        typedef nodeBase<Key> base;
        typedef node<Key>     self;

    /*
    *====================================================================================
    *|                                  Member Fonction                                 |
    *====================================================================================
    */

        node() : base() {};

        explicit node(Key& value, Color color,
                      bool  (*initComp)      (Key, Key)          = &std::less<Key>(),
                      Key*  (*initAlloc)     (std::size_t)       = &std::allocator<Key>::allocate(),
                      Key*  (*initConstruct) (const Key&)        = &std::allocator<Key>::construct(),
                      void  (*initDestroy)   (const Key*)        = &std::allocator<Key>::destroy(),
                      void  (*initDealloc)   (Key*, std::size_t) = &std::allocator<Key>::deallocate())
                      : base(value, color, initComp, initAlloc, initConstruct, initDestroy, initDealloc){ };

        node(const self &other) : base(other){ };

        ~node() {};

    };

__FT_CONTAINERS_END_NAMESPACE

namespace std {
    template<class Key>
    inline void swap(ft::nodeBase<Key>&lhs, ft::nodeBase<Key> &rhs)
    {__INFOMO__ lhs.swap(rhs); __INFOMONL__ };
};

#endif //FT_CONTAINERS_NODE_TPP
