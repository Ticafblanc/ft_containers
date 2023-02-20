#pragma once

#include "../vector.tpp"
#include "../stack.tpp"
#include "../type_traits.tpp"
#include "../iterator.tpp"
#include "../algorithm.tpp"
#include "../utility.tpp"

/**************************************************/
/*			Change paths to your files			  */
/*				or comment #include				  */
/*		if you haven't yet some container		  */
/**************************************************/
#define VECTOR			"../../../vector.tpp"
#define STACK			"../../../stack.tpp"
//#define MAP			  	"../../../Map.tpp"
#define SET			  	"../../../set.tpp"
#define UTILITIES		"../../../utility.tpp"
#define TYPE_TRAITS     "../../../type_traits.tpp"


/* comment this to turn OFF flags (-WWW, -std=98) */
// #define FLAGS

/**************************************************/
/*		Change template names of your classes	  */
/**************************************************/
#define	_vector 			ft::vector
#define	_stack	 			ft::stack
//#define	_map 				ft::Map
#define	_set	 			ft::set
#define	_is_integral 		ft::is_integral
#define	_enable_if 			ft::enable_if
#define	_pair 				ft::pair
#define	_make_pair 			ft::make_pair
#define	_lexicographical	ft::lexicographical_compare
#define	_equal				ft::equal
