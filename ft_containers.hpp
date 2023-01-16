/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_container.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 21:18:19 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/12/26 21:18:22 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

    //#include stdlib specific
//std::ptrdiff_t
# include <cstddef>
//std::random_access_iterator_tag
//std::iterator
# include <iterator>
//std::deque
# include <deque>
//std::allocator, std::uninitialised_copy
# include <memory>
//std::mememove
# include <cstring>
//std::swap std::copy
# include <algorithm>
//std::numeric_limits<>
# include <limits>

/* Print debug */

size_t    count = 0;

#define __COUT__    std::cout
#define __CENDL__   << std::endl;
#define __CE__      ;
#define __NFILE__   << "\nFile name = " << __FILE_NAME__
#define __NLINE__   << "\nLine = " << __LINE__
#define __INFUN__   << "\n" << count << " -> Get in fonction = "<<__PRETTY_FUNCTION__
#define __OUTFUN__  << "\n" << count++ << " -> Get out in fonction = "<<__PRETTY_FUNCTION__
#define __SIZE__    << "\nSize = " << size()
#define __CAPA__    << "\nCapacity = " << capacity()

/* Non members */
#if 0
    #define __INFONM__ __COUT__ __NFILE__ __INFUN__ __NLINE__ __CE__
#else
    #define __INFONM__ ;
#endif

/* Modifier */
#if 0
    #define __INFOMO__ __COUT__ __NFILE__ __INFUN__ __NLINE__ __SIZE__ __CAPA__ __CE__
    #define __INFOMONL__ __COUT__ __OUTFUN__ __NLINE__ __SIZE__ __CAPA__ __CENDL__
#else
    #define __INFOMO__ ;
    #define __INFOMONL__ ;
#endif

/* capacity */
#if 0
    #define __INFOCA__ __COUT__ __NFILE__ __INFUN__ __NLINE__ __SIZE__ __CAPA__ __CE__
    #define __INFOCANL__ __COUT__ __OUTFUN__ __NLINE__ __SIZE__ __CAPA__ __CENDL__
#else
    #define __INFOCA__ ;
    #define __INFOCANL__ ;
#endif

/* Iterator */
#if 0
    #define __INFOIT__ __COUT__ __NFILE__ __INFUN__ __NLINE__ __CE__
#else
    #define __INFOIT__ ;
#endif

/* Eemant acces */
#if 0
    #define __INFOEA__ __COUT__ __NFILE__ __INFUN__ __NLINE__ __CE__
#else
    #define __INFOEA__ ;
#endif

/* menber Fonction */
#if 0
    #define __INFOMF__ __COUT__ __NFILE__ __INFUN__ __NLINE__ __SIZE__ __CAPA__ __CE__
    #define __INFOMFNL__ __COUT__ __OUTFUN__ __NLINE__ __SIZE__ __CAPA__ __CENDL__
#else
    #define __INFOMF__ ;
    #define __INFOMFNL__ ;
#endif


#ifndef FT_CONTAINERS_FT_CONTAINERS_HPP
# define FT_CONTAINERS_FT_CONTAINERS_HPP

#define __FT_CONTAINERS_BEGIN_NAMESPACE namespace ft {
#define __FT_CONTAINERS_END_NAMESPACE }

//#include <map.tpp> //container > ft::map

//#include <vector.tpp> //container >> ft:vector

//#include <stack.tpp> //container >> ft::stack

//#include <iterator.tpp> //contain >> ft::iterator_trait / ft::reverse_iterator

//#include <type_traits.tpp> //contain >>   ft::enable_if / std::is_integral

//#include <algorithm.tpp> //contain >>  ft::equal / ft::lexicographical_compare

//#include <utility.tpp> //contain >>  ft::pair / ft::make_pair

#endif //FT_CONTAINERS_FT_CONTAINERS_HPP
