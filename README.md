<div id="top"></div>

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Ticafblanc/ft_container">
    <code><img height="80" src="Images/cpp_logo.png"></code>
  </a>

<h3 align="center">ft_container</h3>

  <p align="center">
    C++ containers, easy mode !!
    <br />
    <a href="https://github.com/Ticafblanc/ft_container"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Ticafblanc/ft_container">View Demo</a>
    ·
    <a href="https://github.com/Ticafblanc/ft_container/issues">Report Bug</a>
    ·
    <a href="https://github.com/Ticafblanc/ft_container/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project


In this project, you will implement a few container types of the C++ standard template library.
You have to take the structure of each standard container as reference. If a part of the Orthodox Canonical form is missing in it, do not implement it.
As a reminder, you have to comply with the C++98 standard, so any later feature of the containers MUST NOT be implemented, but every C++98 feature (even deprecated ones) is expected.
see subject for the rest

<p align="right">(<a href="#top">back to top</a>)</p>



### Built With

* [CLion](https://www.jetbrains.com/clion/promo/?source=google&medium=cpc&campaign=11960744855&term=clion&content=489240779234&gclid=EAIaIQobChMIjYSpkeeX_AIVh6XICh0CqwhAEAAYASAAEgLIVPD_BwE)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

Implement the following containers and turn in the necessary <container>.hpp files with a Makefile:
• vector
You don’t have to do the vector<bool> specialization.
• map
• stack
It will use your vector class as default underlying container. But it must still be compatible with other containers, the STL ones included.
You also have to implement:
• iterators_traits
• reverse_iterator
• enable_if
Yes, it is C++11 but you will be able to implement it in a C++98 manner. This is asked so you can discover SFINAE.
• is_integral
• equal and/or lexicographical_compare
• std::pair
• std::make_pair

The namespace must be ft instead of std

### Prerequisites

c++98

### Installation
• git clone the repo and use with
<p align="right">(<a href="#top">back to top</a>)</p>
<!-- USAGE EXAMPLES -->
## Usage

• #include <map.hpp>
• #include <stack.hpp>
• #include <vector.hpp>

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- [X] create headers files and define namespace
- [X] create template utility.tpp contain >>  ft::pair / ft::make_pair
- [X] create template algorithm.tpp contain >>  ft::equal / ft::lexicographical_compare
- [X] create template type_trait.tpp contain >>   ft::enable_if / std::is_integral
- [X] create template iterator.tpp contain >>   ft::iterator_trait / std::reverse_iterator
- [X] create template vector.tpp contain >>   ft::vector
- [X] create template set.tpp contain >>   ft::set / std::red_black_tree
- [X] create template map.tpp contain >>   ft::mpa

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Matthis DoQuocBao - [![LinkedIn][linkedin-shield]][linkedin-url] - matthisdqb@icloud.com

Project Link: [https://github.com/Ticafblanc/ft_container](https://github.com/Ticafblanc/ft_container)


<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* https://en.cppreference.com(https://en.cppreference.com)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/Ticafblanc/42-cursus_get_next_line.svg?style=for-the-badge
[contributors-url]: https://github.com/Ticafblanc/42-cursus_get_next_line/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Ticafblanc/42-cursus_get_next_line.svg?style=for-the-badge
[forks-url]: https://github.com/Ticafblanc/42-cursus_get_next_line/network/members
[stars-shield]: https://img.shields.io/github/stars/Ticafblanc/42-cursus_get_next_line.svg?style=for-the-badge
[stars-url]: https://github.com/Ticafblanc/42-cursus_get_next_line/stargazers
[issues-shield]: https://img.shields.io/github/issues/Ticafblanc/42-cursus_get_next_line.svg?style=for-the-badge
[issues-url]: https://github.com/Ticafblanc/42-cursus_get_next_line/issues
[license-shield]: https://img.shields.io/github/license/Ticafblanc/42-cursus_get_next_line.svg?style=for-the-badge
[license-url]: https://github.com/Ticafblanc/42-cursus_get_next_line/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/matthis-doquocbao-a4a381192?lipi=urn%3Ali%3Apage%3Ad_flagship3_profile_viewBase_contact_details%3Bqur1a8wNS0OuvMWTRXIihA%3D%3D
<!--[product-screenshot]: Images/cpp_logo.png-->
