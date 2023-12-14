// from https://www.codeproject.com/Articles/857354/Compile-Time-Loops-with-Cplusplus-Creating-a-Gener

#ifndef STATIC_FOR_HPP_
#define STATIC_FOR_HPP_

#include <cstdint>

#include "static_for.hxx"

template<size_t count, typename functor, size_t sequence_width = 70,
    typename... functor_types>
inline void static_for(functor_types&&... functor_args)
{
    static_for_impl<0, count-1, functor, sequence_width, functor_types...>::
        loop(std::forward<functor_types>(functor_args)...);
}

template<size_t start, size_t end, typename functor, size_t sequence_width = 70,
    typename... functor_types>
inline void static_for(functor_types&&... functor_args)
{
    static_for_impl<start, end, functor, sequence_width, functor_types...>::
        loop(std::forward<functor_types>(functor_args)...);
}

#endif // STATIC_FOR_HPP_