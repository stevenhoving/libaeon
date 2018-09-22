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

#include <aeon/common/assert.h>
#include <type_traits>
#include <cstddef>
#include <iterator>
#include <array>

namespace aeon::common
{

template <typename T>
class span
{
public:
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using index_type = std::ptrdiff_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator = pointer;
    using const_iterator = const pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    explicit constexpr span() noexcept;

    explicit constexpr span(pointer ptr, const index_type count) noexcept;

    explicit constexpr span(pointer first, pointer last) noexcept;

    template <std::size_t N>
    explicit constexpr span(std::array<value_type, N> &array) noexcept;

    template <std::size_t N>
    explicit constexpr span(const std::array<value_type, N> &array) noexcept;

    ~span() = default;

    span(const span &) noexcept = default;
    auto operator=(const span &) noexcept -> span & = default;

    span(span &&) noexcept = default;
    auto operator=(span &&) noexcept -> span & = default;

    constexpr auto data() const noexcept -> pointer;

    constexpr auto size() const noexcept -> index_type;

    constexpr auto empty() const noexcept -> bool;

    constexpr auto operator[](const index_type i) const noexcept -> reference;

    constexpr auto operator()(const index_type i) const noexcept -> reference;

    constexpr auto at(const index_type i) const -> reference;

    constexpr auto begin() const noexcept -> iterator;

    constexpr auto end() const noexcept -> iterator;

    constexpr auto front() const noexcept -> reference;

    constexpr auto back() const noexcept -> reference;

private:
    pointer data_;
    index_type size_;
};

template <typename T>
inline constexpr span<T>::span() noexcept
    : data_{nullptr}
    , size_{0}
{
}

template <typename T>
inline constexpr span<T>::span(pointer ptr, const index_type count) noexcept
    : data_{ptr}
    , size_{count}
{
}

template <typename T>
inline constexpr span<T>::span(pointer first, pointer last) noexcept
    : data_{first}
    , size_{std::distance(first, last)}
{
}

template <typename T>
template <std::size_t N>
inline constexpr span<T>::span(std::array<value_type, N> &array) noexcept
    : data_{array.data()}
    , size_{static_cast<index_type>(array.size())}
{
}

template <typename T>
template <std::size_t N>
inline constexpr span<T>::span(const std::array<value_type, N> &array) noexcept
    : data_{array.data()}
    , size_{static_cast<index_type>(array.size())}
{
}

template <typename T>
constexpr auto span<T>::data() const noexcept -> pointer
{
    return data_;
}

template <typename T>
inline constexpr auto span<T>::size() const noexcept -> index_type
{
    return size_;
}

template <typename T>
inline constexpr auto span<T>::empty() const noexcept -> bool
{
    return size() == 0;
}

template <typename T>
inline constexpr auto span<T>::operator[](const index_type i) const noexcept -> reference
{
    aeon_assert(i >= 0, "Out of range.");
    aeon_assert(i < size(), "Out of range.");
    return *(data() + i);
}

template <typename T>
inline constexpr auto span<T>::operator()(const index_type i) const noexcept -> reference
{
    aeon_assert(i >= 0, "Out of range.");
    aeon_assert(i < size(), "Out of range.");
    return *(data() + i);
}

template <typename T>
inline constexpr auto span<T>::at(const index_type i) const -> reference
{
    if (i < 0 || i > size())
        throw std::out_of_range{"Out of range."};

    return *(data() + i);
}

template <typename T>
inline constexpr auto span<T>::begin() const noexcept -> iterator
{
    return data();
}

template <typename T>
inline constexpr auto span<T>::end() const noexcept -> iterator
{
    return data() + size();
}

template <typename T>
inline constexpr auto span<T>::front() const noexcept -> reference
{
    aeon_assert(!empty(), "Span empty.");
    return *data();
}

template <typename T>
inline constexpr auto span<T>::back() const noexcept -> reference
{
    aeon_assert(!empty(), "Span empty.");
    return *(data() + size() - 1);
}

template <class T, size_t N>
span(std::array<T, N> &)->span<T>;

template <class T, size_t N>
span(const std::array<T, N> &)->span<const T>;

} // namespace aeon::common
