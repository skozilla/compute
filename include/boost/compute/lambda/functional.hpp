//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_FUNCTIONAL_HPP
#define BOOST_COMPUTE_LAMBDA_FUNCTIONAL_HPP

#include <boost/proto/core.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/compute/lambda/result_of.hpp>

namespace boost {
namespace compute {
namespace lambda {

namespace mpl = boost::mpl;
namespace proto = boost::proto;

// wraps a unary boolean function
#define BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef int type; \
            }; \
            \
            static const char* function_name() \
            { \
                return BOOST_PP_STRINGIZE(name); \
            } \
        }; \
    } \
    template<class Arg> \
    typename proto::result_of::make_expr< \
               proto::tag::function, \
               BOOST_PP_CAT(detail::name, _func), \
               const Arg& \
         >::type const \
    name(const Arg &arg) \
    { \
        return proto::make_expr<proto::tag::function>( \
                   BOOST_PP_CAT(detail::name, _func)(), \
                   ::boost::ref(arg) \
           ); \
    }

// wraps a unary function who's return type is the same as the argument type
#define BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type type; \
            }; \
            \
            static const char* function_name() \
            { \
                return BOOST_PP_STRINGIZE(name); \
            } \
        }; \
    } \
    template<class Arg> \
    typename proto::result_of::make_expr< \
               proto::tag::function, \
               BOOST_PP_CAT(detail::name, _func), \
               const Arg& \
         >::type const \
    name(const Arg &arg) \
    { \
        return proto::make_expr<proto::tag::function>( \
                   BOOST_PP_CAT(detail::name, _func)(), \
                   ::boost::ref(arg) \
           ); \
    }

#define BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type type; \
            }; \
            \
            static const char* function_name() \
            { \
                return BOOST_PP_STRINGIZE(name); \
            } \
        }; \
    } \
    template<class Arg1, class Arg2> \
    typename proto::result_of::make_expr< \
                 proto::tag::function, \
                 BOOST_PP_CAT(detail::name, _func), \
                 const Arg1&, \
                 const Arg2& \
             >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2) \
    { \
        return proto::make_expr<proto::tag::function>( \
                   BOOST_PP_CAT(detail::name, _func)(), \
                   ::boost::ref(arg1), \
                   ::boost::ref(arg2)); \
    }

// wraps a ternary function
#define BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(name) \
    namespace detail { \
        struct BOOST_PP_CAT(name, _func) \
        { \
            template<class Expr, class Args> \
            struct lambda_result \
            { \
                typedef typename proto::result_of::child_c<Expr, 1>::type Arg1; \
                typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type type; \
            }; \
            \
            static const char* function_name() \
            { \
                return BOOST_PP_STRINGIZE(name); \
            } \
        }; \
    } \
    template<class Arg1, class Arg2, class Arg3> \
    typename proto::result_of::make_expr< \
                 proto::tag::function, \
                 BOOST_PP_CAT(detail::name, _func), \
                 const Arg1&, \
                 const Arg2&, \
                 const Arg3& \
             >::type const \
    name(const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) \
    { \
        return proto::make_expr<proto::tag::function>( \
                   BOOST_PP_CAT(detail::name, _func)(), \
                   ::boost::ref(arg1), \
                   ::boost::ref(arg2), \
                   ::boost::ref(arg3)); \
    }


BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(all)
BOOST_COMPUTE_LAMBDA_WRAP_BOOLEAN_UNARY_FUNCTION(any)

BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(abs)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(cos)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(acos)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(sin)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(asin)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(tan)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(atan)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(sqrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(rsqrt)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(exp)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(exp2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(exp10)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(log)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(log2)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(log10)
BOOST_COMPUTE_LAMBDA_WRAP_UNARY_FUNCTION_T(round)

//BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(cross)
//BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(dot)
//BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(distance)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(pow)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(pown)
BOOST_COMPUTE_LAMBDA_WRAP_BINARY_FUNCTION(powr)

BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(clamp)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(fma)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(mad)
BOOST_COMPUTE_LAMBDA_WRAP_TERNARY_FUNCTION(smoothstep)

namespace detail {

struct dot_func
{
    template<class Expr, class Args>
    struct lambda_result
    {
        typedef typename proto::result_of::child_c<Expr, 1>::type Arg1;
        typedef typename proto::result_of::child_c<Expr, 2>::type Arg2;

        typedef typename ::boost::compute::lambda::result_of<Arg1, Args>::type T1;
        typedef typename ::boost::compute::lambda::result_of<Arg2, Args>::type T2;

        typedef typename ::boost::compute::scalar_type<T1>::type type;
    };

    static const char* function_name()
    {
        return "dot";
    }
};

} // end detail namespace

template<class Arg1, class Arg2>
typename proto::result_of::make_expr<
             proto::tag::function,
             detail::dot_func,
             const Arg1&,
             const Arg2&
         >::type const
dot(const Arg1 &arg1, const Arg2 &arg2)
{
    return proto::make_expr<proto::tag::function>(
               detail::dot_func(),
               ::boost::ref(arg1),
               ::boost::ref(arg2)
           );
}

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_FUNCTIONAL_HPP
