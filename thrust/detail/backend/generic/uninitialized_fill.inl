/*
 *  Copyright 2008-2011 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <thrust/detail/config.h>
#include <thrust/detail/backend/generic/uninitialized_fill.h>
#include <thrust/fill.h>
#include <thrust/detail/internal_functional.h>
#include <thrust/detail/type_traits.h>
#include <thrust/iterator/iterator_traits.h>

namespace thrust
{
namespace detail
{
namespace backend
{
namespace generic
{
namespace detail
{

template<typename ForwardIterator,
         typename T>
  void uninitialized_fill(ForwardIterator first,
                          ForwardIterator last,
                          const T &x,
                          thrust::detail::true_type) // has_trivial_copy_constructor
{
  thrust::fill(first, last, x);
} // end uninitialized_fill()

template<typename ForwardIterator,
         typename T>
  void uninitialized_fill(ForwardIterator first,
                          ForwardIterator last,
                          const T &x,
                          thrust::detail::false_type) // has_trivial_copy_constructor
{
  typedef typename iterator_traits<ForwardIterator>::value_type ValueType;

  thrust::for_each(first, last, thrust::detail::uninitialized_fill_functor<ValueType>(x));
} // end uninitialized_fill()

template<typename ForwardIterator,
         typename Size,
         typename T>
  ForwardIterator uninitialized_fill_n(ForwardIterator first,
                                       Size n,
                                       const T &x,
                                       thrust::detail::true_type) // has_trivial_copy_constructor
{
  return thrust::fill_n(first, n, x);
} // end uninitialized_fill()

template<typename ForwardIterator,
         typename Size,
         typename T>
  ForwardIterator uninitialized_fill_n(ForwardIterator first,
                                       Size n,
                                       const T &x,
                                       thrust::detail::false_type) // has_trivial_copy_constructor
{
  typedef typename iterator_traits<ForwardIterator>::value_type ValueType;

  return thrust::for_each_n(first, n, thrust::detail::uninitialized_fill_functor<ValueType>(x));
} // end uninitialized_fill()

} // end detail

template<typename ForwardIterator,
         typename T>
  void uninitialized_fill(tag,
                          ForwardIterator first,
                          ForwardIterator last,
                          const T &x)
{
  typedef typename iterator_traits<ForwardIterator>::value_type ValueType;

  typedef thrust::detail::has_trivial_copy_constructor<ValueType> ValueTypeHasTrivialCopyConstructor;

  thrust::detail::backend::generic::detail::uninitialized_fill(first, last, x,
    ValueTypeHasTrivialCopyConstructor());
} // end uninitialized_fill()

template<typename ForwardIterator,
         typename Size,
         typename T>
  ForwardIterator uninitialized_fill_n(tag,
                                       ForwardIterator first,
                                       Size n,
                                       const T &x)
{
  typedef typename iterator_traits<ForwardIterator>::value_type ValueType;

  typedef thrust::detail::has_trivial_copy_constructor<ValueType> ValueTypeHasTrivialCopyConstructor;

  return thrust::detail::backend::generic::detail::uninitialized_fill_n(first, n, x,
    ValueTypeHasTrivialCopyConstructor());
} // end uninitialized_fill()

} // end namespace generic
} // end namespace backend
} // end namespace detail
} // end namespace thrust

