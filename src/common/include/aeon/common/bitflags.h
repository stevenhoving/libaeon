/*
 * Copyright (c) 2012-2017 Robin Degen
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

namespace aeon
{
namespace common
{

template <typename T>
inline static auto get_bit(T val, unsigned int bit)
{
    return ((val & (1 << bit)) >> bit);
}

template <typename T>
inline static auto get_bit_range(T val, unsigned int offset, unsigned int length)
{
    return ((val & (((1 << length) - 1) << offset)) >> offset);
}

template <typename T>
inline static void set_bit(T &val, unsigned int bit)
{
    val |= (1 << bit);
}

template <typename T>
inline static void clear_bit(T &val, unsigned int bit)
{
    val &= (val & ~(1 << bit));
}

template <typename T>
inline static void set_bit_flag(T &val, T flag)
{
    val |= flag;
}

template <typename T>
inline static void clear_bit_flag(T &val, T flag)
{
    val &= (val & (~flag));
}

template <typename T>
inline static auto check_bit_flag(T value, T flag)
{
    return (value & flag) == flag;
}

inline static auto get_low_nibble(unsigned char value)
{
    return static_cast<unsigned char>(value & 0x0F);
}

inline static auto get_high_nibble(unsigned char value)
{
    return static_cast<unsigned char>((value & 0xF0) >> 4);
}

} // namespace common
} // namespace aeon
