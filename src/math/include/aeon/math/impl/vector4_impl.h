/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <cmath>
#include <limits>

namespace aeon::math
{

template <typename T>
inline vector4<T>::vector4() noexcept
    : x{}
    , y{}
    , z{}
    , w{}
{
}

template <typename T>
inline vector4<T>::vector4(const T xyzw) noexcept
    : x{xyzw}
    , y{xyzw}
    , z{xyzw}
    , w{xyzw}
{
}

template <typename T>
inline vector4<T>::vector4(const T x, const T y) noexcept
    : x{x}
    , y{y}
    , z{0}
    , w{0}
{
}

template <typename T>
inline vector4<T>::vector4(const T x, const T y, const T z) noexcept
    : x{x}
    , y{y}
    , z{z}
    , w{0}
{
}

template <typename T>
inline vector4<T>::vector4(const T x, const T y, const T z, const T w) noexcept
    : x{x}
    , y{y}
    , z{z}
    , w{w}
{
}

template <typename T>
inline vector4<T>::vector4(const vector2<T> vec) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{0}
    , w{0}
{
}

template <typename T>
inline vector4<T>::vector4(const vector2<T> vec, const T z) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{z}
    , w{0}
{
}

template <typename T>
inline vector4<T>::vector4(const vector2<T> vec, const T z, const T w) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{z}
    , w{w}
{
}

template <typename T>
inline vector4<T>::vector4(const vector3<T> vec) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{vec.z}
    , w{0}
{
}

template <typename T>
inline vector4<T>::vector4(const vector3<T> vec, const T w) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{vec.z}
    , w{w}
{
}

template <typename T>
vector4<T>::vector4(const T xyzw[4]) noexcept
    : x{xyzw[0]}
    , y{xyzw[1]}
    , z{xyzw[2]}
    , w{xyzw[3]}
{
}

template <typename T>
inline auto vector4<T>::zero() noexcept -> vector4<T>
{
    return vector4<T>{};
}

template <typename T>
inline void vector4<T>::set(const T new_x, const T new_y, const T new_z, const T new_w) noexcept
{
    x = new_x;
    y = new_y;
    z = new_z;
    w = new_w;
}

template <typename T>
inline auto dot(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
}

template <typename T>
inline auto length(const vector4<T> &vec) noexcept -> T
{
    return std::sqrt(dot(vec, vec));
}

template <typename T>
inline auto squared_length(const vector4<T> &vec) noexcept -> T
{
    return dot(vec, vec);
}

template <typename T>
inline auto normalized(const vector4<T> &vec) noexcept -> vector4<T>
{
    auto l = length(vec);

    if (l > std::numeric_limits<T>::epsilon())
        return vec / l;

    return vector4<T>::zero();
}

template <typename T>
inline auto sin(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::sin(vec.x), std::sin(vec.y), std::sin(vec.z), std::sin(vec.w)};
}

template <typename T>
inline auto cos(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::cos(vec.x), std::cos(vec.y), std::cos(vec.z), std::cos(vec.w)};
}

template <typename T>
inline auto tan(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::tan(vec.x), std::tan(vec.y), std::tan(vec.z), std::tan(vec.w)};
}

template <typename T>
inline auto distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T
{
    return length(lhs - rhs);
}

template <typename T>
inline auto squared_distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T
{
    return squared_length(lhs - rhs);
}

template <typename T>
inline auto midpoint(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return (lhs + rhs) * 0.5f;
}

template <typename T>
inline auto floor(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    auto x = lhs.x;
    auto y = lhs.y;
    auto z = lhs.z;
    auto w = lhs.w;

    if (rhs.x < x)
        x = rhs.x;
    if (rhs.y < y)
        y = rhs.y;
    if (rhs.z < z)
        z = rhs.z;
    if (rhs.w < w)
        w = rhs.w;

    return {x, y, z, w};
}

template <typename T>
inline auto ceil(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    auto x = lhs.x;
    auto y = lhs.y;
    auto z = lhs.z;
    auto w = lhs.w;

    if (rhs.x > x)
        x = rhs.x;
    if (rhs.y > y)
        y = rhs.y;
    if (rhs.z > z)
        z = rhs.z;
    if (rhs.w > w)
        w = rhs.w;

    return {x, y, z, w};
}

template <typename T>
inline auto ptr(vector4<T> &vec) noexcept -> T *
{
    return &vec.x;
}

template <typename T>
inline auto ptr(const vector4<T> &vec) noexcept -> const T *
{
    return &vec.x;
}

} // namespace aeon::math