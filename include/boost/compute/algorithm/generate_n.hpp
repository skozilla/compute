//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP
#define BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/generate.hpp>
#include <boost/compute/detail/default_queue_for_iterator.hpp>

namespace boost {
namespace compute {

template<class OutputIterator, class Size, class Generator>
inline void generate_n(OutputIterator first,
                       Size count,
                       Generator generator,
                       command_queue &queue)
{
    ::boost::compute::generate(first, first + count, generator, queue);
}

template<class OutputIterator, class Size, class Generator>
inline void generate_n(OutputIterator first,
                       Size count,
                       Generator generator)
{
    command_queue queue = detail::default_queue_for_iterator(first);

    ::boost::compute::generate_n(first, count, generator, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP
