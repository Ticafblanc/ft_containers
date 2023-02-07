/* *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    map.tpp                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 12:26:02 by mdoquocb          #+#    #+#              #
#    Updated: 2022/12/29 12:26:04 by mdoquocb         ###   ########.fr        #
#                                                                              #
# *************************************************************************** */

#pragma once

#include "ft_containers.hpp"
#include "red_black_tree.tpp"
#include "vector.tpp"
#include "utility.tpp"

#ifndef FT_CONTAINERS_MAP_TPP
# define FT_CONTAINERS_MAP_TPP

__FT_CONTAINERS_BEGIN_NAMESPACE

template< class Key, class T, class Compare, class Allocator >
class mapBase : ft::vector<Node<Key, T> >{

private:
    typedef mapBase< Key, T, Compare, Allocator >                         self;
    typedef ft::vector<Node<Key, T> >                                     Base;

public:
    mapBase() : Base(){}
    /*Solved allocator conflict*/
    explicit mapBase(const Allocator& alloc) : Base(alloc) {}

    ~mapBase() {};

private:
    Compare Comp;
};

    //ft::map
/*std::map is a sorted associative container that contains key-value pairs with unique keys.
 * Keys are sorted by using the comparison function Compare. Search, removal, and insertion
 * operations have logarithmic complexity. Maps are usually implemented as red-black trees.

Everywhere the standard library uses the Compare requirements, uniqueness is determined by
 using the equivalence relation. In imprecise terms, two objects a and b are considered equivalent
 (not unique) if neither compares less than the other: !comp(a, b) && !comp(b, a). */


template< class Key, class T, class Compare = std::less<Key>,
        class Allocator = std::allocator<pair<const Key, T> > >
class map : private mapBase< Key, T, Compare, Allocator >{

private:
    typedef mapBase< Key, T, Compare, Allocator >                         Base;
    typedef map< Key, T, Compare, Allocator >                             Self;

/*
*====================================================================================
*|                                     Member Type                                  |
*====================================================================================
*/

public:

    typedef Key                                                     key_types;
    typedef T                                                       mapped_type;
    typedef ft::pair<const key_types, mapped_type>                  value_type;
    typedef std::size_t                                             size_type;
    typedef std::ptrdiff_t                                          difference_type;
    typedef Compare                                                 key_compare;
    typedef value_type&                                             reference;
    typedef const value_type&                                       const_reference;
    typedef Allocator                                               allocator_type;
    typedef typename Allocator::pointer                             pointer;
    typedef typename Allocator::const_pointer                       const_pointer;
    typedef value_type*                                             iterator;
    typedef const value_type*                                       const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

/*
*====================================================================================
*|                                  Member classes                                  |
*====================================================================================
*/

public:

    /*class value_compare https://en.cppreference.com/w/cpp/container/map/value_compare
     * std::map::value_compare is a function object that compares objects of type std::map::value_type
     * (key-value pairs) by comparing of the first components of the pairs.*/
    class value_compare : public std::binary_function<value_type, value_type, bool>{
    protected:
        Compare comp;
        explicit value_compare(Compare c) : comp(c) {};

    public:
        bool operator()(const value_type& lhs, const value_type& rhs) const
        {return comp(lhs.first, rhs.first);}
    };

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

    /*Parameters
       alloc 	- 	allocator to use for all memory allocations of this container
       comp 	- 	comparison function object to use for all comparisons of keys
       first, last 	- 	the range to copy the elements from
       other 	- 	another container to be used as source to initialize the elements of the container with
       init 	- 	initializer list to initialize the elements of the container with
       Type requirements
       -
       InputIt must meet the requirements of LegacyInputIterator.
       -
       Compare must meet the requirements of Compare.
       -
       Allocator must meet the requirements of Allocator.
       Complexity
       1-3) Constant
       4-5) N log(N) where N = std::distance(first, last) in general, linear in N if the range is already sorted by
        value_comp().
       6-7) Linear in size of other
       8-9) Constant. If alloc is given and alloc != other.get_allocator(), then linear.
       10-11) N log(N) where N = init.size() in general, linear in N if init is already sorted by value_comp().
       Exceptions
       Calls to Allocator::allocate may throw.*/

    /*1-3 Constructs an empty container.*/
    map() : Base() {}
};

//    explicit map( const Compare& comp, const Allocator& alloc = Allocator() )
//                    : red_black_tree<pair<const Key, T> > (){}
//
//    //4-5 Constructs the container with the contents of the range [first, last). If multiple elements in the range
//    // have keys
//    // that compare equivalent, it is unspecified which element is inserted (pending LWG2844).
//    template< class InputIt >
//    map( InputIt first, InputIt last, const Compare& comp = Compare(),
//         const Allocator& alloc = Allocator() ) : self_type(first, last, comp, alloc)
//    { this->insert(first, last); }//a valider quand build insert
//
//    //Copy constructor. Constructs the container with the copy of the contents of other
//    map( const map& other ) : self_type(other.key_comp(), other.get_allocator())
//    { this->swap(other); }
//
//    //Destructs the map. The destructors of the elements are called and the used storage is deallocated. Note, that
//    // if the elements are pointers, the pointed-to objects are not destroyed.
//    ~map() {}
//
//    /*Parameters
//    other 	- 	another container to use as data source
//    ilist 	- 	initializer list to use as data source
//    Return value
//
//    *this
//    Complexity
//    1) Linear in the size of *this and other.
//    2) Linear in the size of *this unless the allocators do not compare equal and do not propagate, in which case linear in the size of *this and other.
//    3) O(NlogN) in general, where N is size() + ilist.size(). Linear if ilist is sorted with respect to value_comp().
//    Exceptions
//
//May throw implementation-defined exceptions. */
//
//    // Copy assignment operator. Replaces the contents with a copy of the contents of other.
//    map&     operator=(const map& other)
//    {
//        this->clear();
//        this->swap(other);
//        return *this;
//    }
//
//    //Returns the allocator associated with the container
//    allocator_type get_allocator() const {return allocator_type(); }
//
//    //Returns a reference to the mapped value of the element with key equivalent to key. If no such element exists,
//    // an exception of type std::out_of_range is thrown.
//    mapped_type& at( const Key& key )
//    {
//        //voir si use with find
//    }
//
//    const mapped_type & at( const Key& key ) const
//    {
//        //voir si use with find
//    }
//
//    //Returns a reference to the value that is mapped to a key equivalent to key, performing an insertion if such key
//    // does not already exist.
//    //Inserts value_type(key, T()) if the key does not exist. This function is equivalent to return insert
//    // (std::make_pair(key, T())).first->second;
//    //-
//    //key_type must meet the requirements of CopyConstructible.
//    //-
//    //mapped_type must meet the requirements of CopyConstructible and DefaultConstructible.
//    //If an insertion is performed, the mapped value is value-initialized (default-constructed for class types,
//    // zero-initialized otherwise) and a reference to it is returned.
//    Parameters
//            key 	- 	the key of the element to find
//            Return value
//
//            Reference to the mapped value of the new element if no element with key key existed. Otherwise a
//            reference to the mapped value of the existing element whose key is equivalent to key.
//    Exceptions
//
//            If an exception is thrown by any operation, the insertion has no effect
//
//    mapped_type & operator[]( const Key& key )
//    {
//        if (check if posiible)
//            throw SegFault();
//        return (*((this->insert(ft::make_pair(key, mapped_type()))).first)).second;//a revoir
//    }
//
//    //Returns an iterator to the first element of the map.
//    //If the map is empty, the returned iterator will be equal to end().
//    iterator begin() { return self.begin(); }
//    const_iterator begin() const { return self.begin(); }
//
//    //Returns an iterator to the element following the last element of the map.
//    //This element acts as a placeholder; attempting to access it results in undefined behavior.
//    //range-begin-end.svg
//    iterator end() { return self.end(); }
//    const_iterator end() const { return self.end(); }
//
//    //Returns a reverse iterator to the first element of the reversed map. It corresponds to the last element of the
//    // non-reversed map. If the map is empty, the returned iterator is equal to rend().
//    //range-rbegin-rend.svg
//    reverse_iterator rbegin() { return self.rbegin(); }
//    const_reverse_iterator rbegin() const { return self.rbegin(); }
//
//    //Returns a reverse iterator to the element following the last element of the reversed map. It corresponds to the
//    // element preceding the first element of the non-reversed map. This element acts as a placeholder, attempting to
//    // access it results in undefined behavior.
//    reverse_iterator rend() { return self.rend(); }
//    const_reverse_iterator rend() const { return self.rend(); }
//
//    //Checks if the container has no elements, i.e. whether begin() == end().
//    bool empty() const
//    {
//
//    }
//
//    //Returns the number of elements in the container, i.e. std::distance(begin(), end()).
//    size_type size() const
//    {
//
//    }
//
//    //Returns the maximum number of elements the container is able to hold due to system or library implementation
//    // limitations, i.e. std::distance(begin(), end()) for the largest container.
//    size_type max_size() const
//    {
//
//    }
//
//private:
//    typedef map<Key, T, Compare, Allocator>                     self_type;
//    typedef red_black_tree<ft::pair<const Key, T>, Compare>     rbt_type;
//
//
//};

__FT_CONTAINERS_END_NAMESPACE

#endif //FT_CONTAINERS_MAP_TPP
