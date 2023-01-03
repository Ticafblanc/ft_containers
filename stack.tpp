/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    stack.tpp                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 21:56:15 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/27 21:56:18 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include <ft_containers.hpp>

#ifndef FT_CONTAINER_STACK_TPP
#define FT_CONTAINER_STACK_TPP

__FT_CONTAINER_BEGIN_NAMESPACE

    //ft::stack https://en.cppreference.com/w/cpp/container/stack

/*The std::stack class is a container adaptor that gives the programmer the functionality of a stack - specifically,
 * a LIFO (last-in, first-out) data structure.

The class template acts as a wrapper to the underlying container - only a specific set of functions is provided. The
 stack pushes and pops the element from the back of the underlying container, known as the top of the stack.
Template parameters
    T 	- 	The type of the stored elements. The behavior is undefined if T is not the same type as Container::value_type.
 (since C++17)
    Container 	- 	The type of the underlying container to use to store the elements. The container must satisfy the

 requirements of SequenceContainer. Additionally, it must provide the following functions with the usual semantics:

    back()
    push_back()
    pop_back()

The standard containers std::vector, std::deque and std::list satisfy these requirements. By default, if no container
 class is specified for a particular stack class instantiation, the standard container std::deque is*/

template<class T, class Container = std::deque<T> >
class stack
{
public:
    typedef Container                            container_type ;
    typedef typename Container::value_type       value_type ;
    typedef typename Container::size_type        size_type;
    typedef typename Container::reference        reference;
    typedef typename Container::const_reference  const_reference;

    //Copy-constructs the underlying container c with the contents of cont.
    // This is also the default constructor. (until C++11)
    explicit stack( const Container& cont = Container()) : c(cont) {}

    //Destructs the stack. The destructors of the elements are called and the used storage is deallocated. Note,
    // that if the elements are pointers, the pointed-to objects are not destroyed.
    ~stack() {}

    /*Copy assignment operator. Replaces the contents with a copy of the contents of other.
    // Effectively calls c = other.c;*/
    stack& operator=( const stack& other )
    {
        c = other.c;
        return *this;
    }

    //Returns reference to the top element in the stack. This is the most recently pushed element.
    // This element will be removed on a call to pop(). Effectively calls c.back().
    reference top() { return c.back(); }
    const_reference top() const { return c.back(); }

    //Checks if the underlying container has no elements, i.e. whether c.empty().
    //return true if the underlying container is empty, false otherwise
    bool empty() const { return c.empty(); }

    //Returns the number of elements in the underlying container, that is, c.size().
    size_type size() const { return c.size(); }

    //Pushes the given element value to the top of the stack.
    //Effectively calls c.push_back(value)
    //Parameters
    //value 	- 	the value of the element to push
    //Return value
    //(void)
    void push(const value_type& value) { c.push_back(value); }

    //Removes the top element from the stack. Effectively calls c.pop_back()
    void pop() { c.pop_back(); }

protected:
    //the underlying container
    Container c;
};

//Compares the contents of the underlying containers of two container adaptors. The comparison is done by applying
// the corresponding operator to the underlying containers.
//Parameters
//lhs, rhs 	- 	container adaptors whose contents to compare
//-
//T must meet the requirements of EqualityComparable.
//Return value
//true if the corresponding comparison yields true, false otherwise.

template< class T, class Container >
bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{ return lhs.c == rhs.c; }

template< class T, class Container >
bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{ return lhs.c != rhs.c; }

template< class T, class Container >
bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{ return lhs.c < rhs.c; }

template< class T, class Container >
bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{ return lhs.c <= rhs.c; }

template< class T, class Container >
bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{ return lhs.c > rhs.c; }

template< class T, class Container >
bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{ return lhs.c >= rhs.c; }

__FT_CONTAINER_END_NAMESPACE

#endif //STACK_TPP
