//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_BUFFER_VALUE_HPP
#define BOOST_COMPUTE_DETAIL_BUFFER_VALUE_HPP

#include <boost/compute/context.hpp>
#include <boost/compute/device_ptr.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
class buffer_value
{
public:
    typedef T value_type;

    buffer_value()
        : m_buffer(0)
    {
    }

    buffer_value(const value_type &value)
        : m_buffer(0),
          m_value(value)
    {
    }

    // creates a reference for the value in buffer at index (in bytes).
    buffer_value(const buffer &buffer, size_t index)
        : m_buffer(&buffer),
          m_index(index)
    {
    }

    buffer_value(const buffer_value<T> &other)
        : m_buffer(other.m_buffer),
          m_index(other.m_index)
    {
    }

    operator value_type() const
    {
        if(m_buffer){
            const context &context = m_buffer->get_context();
            const device &device = context.get_device();
            command_queue queue(context, device);

            return detail::read_single_value<T>(*m_buffer, m_index / sizeof(T), queue);
        }
        else {
            return m_value;
        }
    }

    buffer_value<T> operator-() const
    {
        return -T(*this);
    }

    bool operator<(const T &value) const
    {
        return T(*this) < value;
    }

    bool operator>(const T &value) const
    {
        return T(*this) > value;
    }

    bool operator<=(const T &value) const
    {
        return T(*this) <= value;
    }

    bool operator>=(const T &value) const
    {
        return T(*this) <= value;
    }

    bool operator==(const T &value) const
    {
        return T(*this) == value;
    }

    bool operator==(const buffer_value<T> &other) const
    {
        if(m_buffer != other.m_buffer){
            return false;
        }

        if(m_buffer){
            return m_index == other.m_index;
        }
        else {
            return m_value == other.m_value;
        }
    }

    bool operator!=(const T &value) const
    {
        return T(*this) != value;
    }

    buffer_value<T>& operator=(const T &value)
    {
        if(m_buffer){
            const context &context = m_buffer->get_context();
            command_queue queue(context, context.get_device());

            detail::write_single_value<T>(value, *m_buffer, m_index / sizeof(T), queue);

            return *this;
        }
        else {
            m_value = value;
            return *this;
        }
    }

    buffer_value<T>& operator=(const buffer_value<T> &value)
    {
        return operator=(T(value));
    }

    device_ptr<T> operator&() const
    {
        return device_ptr<T>(*m_buffer, m_index);
    }

    buffer_value<T>& operator++()
    {
        if(m_buffer){
            T value = T(*this);
            value++;
            *this = value;
        }
        else {
            m_value++;
        }

        return *this;
    }

    buffer_value<T> operator++(int)
    {
        buffer_value<T> result(*this);
        ++(*this);
        return result;
    }

private:
    const buffer *m_buffer;
    size_t m_index;
    value_type m_value;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_BUFFER_VALUE_HPP
