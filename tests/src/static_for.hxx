#include <type_traits>
#include <utility>

#include "static_for.hpp"

template<size_t for_start, size_t for_end, typename functor, size_t sequence_width,
    typename... functor_types>
struct static_for_impl
{
    static inline void loop(functor_types&&... functor_args)
    {
        // The main sequence point is created, and then we call "next" on each point inside
        using sequence = point<for_start, for_end>;
        next<sequence>
            (std::integral_constant<bool, sequence::is_end_point_>(), 
             std::forward<functor_types>(functor_args)...);
    }

private:
    
    // A point is a node of an n-ary tree
    template<size_t pt_start, size_t pt_end> struct point
    {
        static constexpr size_t start_        { pt_start };
        static constexpr size_t end_          { pt_end };
        static constexpr size_t count_        { end_ - start_ + 1 };
        static constexpr bool is_end_point_   { count_ <= sequence_width };

        static constexpr size_t sequence_count()
        {
            return
                    points_in_sequence(sequence_width) > sequence_width
                ?
                    sequence_width
                :
                    points_in_sequence(sequence_width);
        }

    private:
        // Calculates the start and end indexes for a child node
        static constexpr size_t child_start(size_t index)
        {
            return
                    index == 0
                ?
                    pt_start
                :
                    child_end(index - 1) + 1;
        }
        static constexpr size_t child_end(size_t index)
        {
            return
                    index == sequence_count() - 1
                ?
                    pt_end
                :
                    pt_start + points_in_sequence(sequence_count()) * (index + 1) -
                        (index < count_
                    ?
                         1
                    :
                         0);
        }
        static constexpr size_t points_in_sequence(size_t max)
        {
            return count_ / max + (
                    (count_ % max) > 0
                ?
                    1
                :
                    0);
        }
           
    public:
        // Generates child nodes when needed
        template<size_t index> using child_point = point<child_start(index), child_end(index)>;
    };

    // flat_for is used to instantiate a section of our our main static_for::loop
    // A point is used to specify which numbers this instance of flat_for will use
    template<size_t flat_start, size_t flat_end, class flat_functor> struct flat_for
    {
        // This is the entry point for flat_for
        static inline void flat_loop(functor_types&&... functor_args)
        {
            flat_next(std::integral_constant<size_t, flat_start>(), 
                std::forward<functor_types>(functor_args)...);
        }

    private:
        // Loop termination
        static inline void flat_next
            (std::integral_constant<size_t, flat_end + 1>, functor_types&&...)
        {
        }
       
        // Loop function that calls the function passed to it, as well as recurses
        template<size_t index>
        static inline void flat_next
            (std::integral_constant<size_t, index>, functor_types&&... functor_args)
        {
            flat_functor::template func<index>(std::forward<functor_types>(functor_args)...);
            flat_next(std::integral_constant<size_t, index + 1>(),
                std::forward<functor_types>(functor_args)...);
        }
    };

    // This is what gets called when we run flat_for on a point
    // It will recurse to more finer grained point until the points are no bigger than sequence_width
    template<typename sequence> struct flat_sequence
    {
        template<size_t index> static inline void func(functor_types&&... functor_args)
        {
            using pt = typename sequence::template child_point<index>;
            next<pt>
                (std::integral_constant<bool, pt::is_end_point_>(),
                 std::forward<functor_types>(functor_args)...);
        }
    };

    // The true_type function is called when our sequence is small enough to run out
    // and call the main functor that was provided to us
    template<typename sequence> static inline void next
        (std::true_type, functor_types&&... functor_args)
    {
        flat_for<sequence::start_, sequence::end_, functor>::
            flat_loop(std::forward<functor_types>(functor_args)...);
    }

    // The false_type function is called when our sequence is still too big, and we need to
    // run an internal flat_for loop on the child sequence_points 
    template<typename sequence> static inline void next
        (std::false_type, functor_types&&... functor_args)
    {
        flat_for<0, sequence::sequence_count() - 1, flat_sequence<sequence>>::
            flat_loop(std::forward<functor_types>(functor_args)...);
    }
};