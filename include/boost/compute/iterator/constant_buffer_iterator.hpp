//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_CONSTANT_BUFFER_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_CONSTANT_BUFFER_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for constant_buffer_iterator<T>
template<class T> class constant_buffer_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for constant_buffer_iterator<T>
template<class T>
class constant_buffer_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::constant_buffer_iterator<T>,
        T,
        ::std::random_access_iterator_tag,
        ::boost::compute::detail::buffer_value<T>
    > type;
};

} // end detail namespace

template<class T>
class constant_buffer_iterator :
    public detail::constant_buffer_iterator_base<T>::type
{
public:
    typedef typename detail::constant_buffer_iterator_base<T>::type super_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;

    constant_buffer_iterator()
        : m_buffer(0),
          m_index(0)
    {
    }

    constant_buffer_iterator(const buffer &buffer, size_t index)
        : m_buffer(&buffer),
          m_index(index)
    {
    }

    constant_buffer_iterator(const constant_buffer_iterator<T> &other)
        : m_buffer(other.m_buffer),
          m_index(other.m_index)
    {
    }

    constant_buffer_iterator<T>& operator=(const constant_buffer_iterator<T> &other)
    {
        if(this != &other){
            m_buffer = other.m_buffer;
            m_index = other.m_index;
        }

        return *this;
    }

    ~constant_buffer_iterator()
    {
    }

    const buffer& get_buffer() const
    {
        return *m_buffer;
    }

    size_t get_index() const
    {
        return m_index;
    }

    template<class Expr>
    detail::buffer_iterator_index_expr<T, Expr>
    operator[](const Expr &expr) const
    {
        BOOST_ASSERT(m_buffer);
        BOOST_ASSERT(m_buffer->get_mem());

        return detail::buffer_iterator_index_expr<T, Expr>(*m_buffer,
                                                           m_index,
                                                           "__constant",
                                                           expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return detail::buffer_value<T>(*m_buffer, m_index);
    }

    bool equal(const constant_buffer_iterator<T> &other) const
    {
        return m_buffer == other.m_buffer && m_index == other.m_index;
    }

    void increment()
    {
        m_index++;
    }

    void decrement()
    {
        m_index--;
    }

    void advance(difference_type n)
    {
        m_index = static_cast<size_t>(static_cast<difference_type>(m_index) + n);
    }

    difference_type distance_to(const constant_buffer_iterator<T> &other) const
    {
        return static_cast<difference_type>(other.m_index - m_index);
    }

private:
    const buffer *m_buffer;
    size_t m_index;
};

template<class T>
inline constant_buffer_iterator<T>
make_constant_buffer_iterator(const buffer &buffer, size_t index = 0)
{
    return constant_buffer_iterator<T>(buffer, index);
}

namespace detail {

// is_buffer_iterator specialization for constant_buffer_iterator
template<class Iterator>
struct is_buffer_iterator<
    Iterator,
    typename boost::enable_if<
        boost::is_same<
            constant_buffer_iterator<typename Iterator::value_type>,
            typename boost::remove_const<Iterator>::type
        >
    >::type
> : public boost::true_type {};

// is_device_iterator specialization for constant_buffer_iterator
template<class Iterator>
struct is_device_iterator<
    Iterator,
    typename boost::enable_if<
        boost::is_same<
            constant_buffer_iterator<typename Iterator::value_type>,
            typename boost::remove_const<Iterator>::type
        >
    >::type
> : public boost::true_type {};

} // end detail namespace

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_CONSTANT_BUFFER_ITERATOR_HPP
