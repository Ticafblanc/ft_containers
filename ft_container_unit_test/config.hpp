#pragma once

#include "../ft_stl/map.tpp"
#include "../ft_stl/set.tpp"
#include "../ft_stl/vector.tpp"
#include "../ft_stl/stack.tpp"
#include "../ft_stl/type_traits.tpp"
#include "../ft_stl/iterator.tpp"
#include "../ft_stl/algorithm.tpp"
#include "../ft_stl/utility.tpp"

/**************************************************/
/*			Change paths to your files			  */
/*				or comment #include				  */
/*		if you haven't yet some container		  */
/**************************************************/
#define VECTOR			"../../../ft_stl/vector.tpp"
#define STACK			"../../../ft_stl/stack.tpp"
#define MAP			  	"../../../ft_stl/map.tpp"
#define SET			  	"../../../ft_stl/set.tpp"
#define UTILITIES		"../../../ft_stl/utility.tpp"
#define TYPE_TRAITS     "../../../ft_stl/type_traits.tpp"


/* comment this to turn OFF flags (-WWW, -std=98) */
//#define FLAGS

/**************************************************/
/*		Change template names of your classes	  */
/**************************************************/
#define	_vector 			ft::vector
#define	_stack	 			ft::stack
#define	_map 				ft::map
#define	_set	 			ft::set
#define	_is_integral 		ft::is_integral
#define	_enable_if 			ft::enable_if
#define	_pair 				ft::pair
#define	_make_pair 			ft::make_pair
#define	_lexicographical	ft::lexicographical_compare
#define	_equal				ft::equal
