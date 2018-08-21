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

#include <aeon/imaging/image.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/imaging/dynamic_image_descriptor.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/common/assert.h>
#include <memory>

namespace aeon::imaging
{

class dynamic_image
{
public:
    explicit dynamic_image(const dynamic_image_descriptor &dynamic_descriptor);

    template <typename T>
    explicit dynamic_image(image<T> &&image);

    template <typename T>
    explicit dynamic_image(std::unique_ptr<image<T>> image);

    ~dynamic_image();

    dynamic_image(const dynamic_image &) = delete;
    auto operator=(const dynamic_image &) -> dynamic_image & = delete;

    dynamic_image(dynamic_image &&o) noexcept = default;
    auto operator=(dynamic_image &&other) noexcept -> dynamic_image & = default;

    auto descriptor() const noexcept -> dynamic_image_descriptor;

    template <typename T>
    auto get_image() noexcept -> image<T> &;

    template <typename T>
    auto get_image() const noexcept -> const image<T> &;

private:
    dynamic_image_descriptor dynamic_descriptor_;
    std::unique_ptr<image_base> image_;
};

inline auto descriptor(const dynamic_image &image) noexcept -> dynamic_image_descriptor;

inline auto null(const dynamic_image &image) noexcept -> bool;

inline auto valid(const dynamic_image &image) noexcept -> bool;

inline auto encoding(const dynamic_image &image) noexcept -> pixel_encoding;

inline auto width(const dynamic_image &image) noexcept -> dimension;

inline auto height(const dynamic_image &image) noexcept -> dimension;

inline auto dimensions(const dynamic_image &image) noexcept -> math::size2d<dimension>;

inline auto rectangle(const dynamic_image &image) noexcept -> math::rectangle<dimension>;

inline auto stride_x(const dynamic_image &image) noexcept -> std::ptrdiff_t;

inline auto stride_y(const dynamic_image &image) noexcept -> std::ptrdiff_t;

inline auto continuous(const dynamic_image &image) noexcept -> bool;

inline auto contains(const dynamic_image &image, const math::vector2<dimension> coord) noexcept -> bool;

inline auto size(const dynamic_image &image) noexcept -> std::ptrdiff_t;

template <typename T>
inline auto view(dynamic_image &image) noexcept -> image_view<T> &;

template <typename T>
inline auto view(const dynamic_image &image) noexcept -> const image_view<T> &;

#define process_image(img, func, ...)                                                                                  \
    [&]() {                                                                                                            \
        switch (encoding(img))                                                                                         \
        {                                                                                                              \
            case pixel_encoding::unsigned8:                                                                            \
                func(view<std::uint8_t>(img), ##__VA_ARGS__);                                                          \
                return;                                                                                                \
            case pixel_encoding::unsigned16:                                                                           \
                func(view<std::uint16_t>(img), ##__VA_ARGS__);                                                         \
                return;                                                                                                \
            case pixel_encoding::unsigned32:                                                                           \
                func(view<std::uint32_t>(img), ##__VA_ARGS__);                                                         \
                return;                                                                                                \
            case pixel_encoding::float32:                                                                              \
                func(view<float>(img), ##__VA_ARGS__);                                                                 \
                return;                                                                                                \
            case pixel_encoding::rgb24:                                                                                \
                func(view<rgb24>(img), ##__VA_ARGS__);                                                                 \
                return;                                                                                                \
            case pixel_encoding::rgba32:                                                                               \
                func(view<rgba32>(img), ##__VA_ARGS__);                                                                \
                return;                                                                                                \
            case pixel_encoding::bgr24:                                                                                \
                func(view<bgr24>(img), ##__VA_ARGS__);                                                                 \
                return;                                                                                                \
            case pixel_encoding::bgra32:                                                                               \
                func(view<bgra32>(img), ##__VA_ARGS__);                                                                \
            default:                                                                                                   \
                throw imaging_exception();                                                                             \
        }                                                                                                              \
    }();

#define process_image_to_copy(img, func, ...)                                                                          \
    [&]() -> dynamic_image {                                                                                           \
        switch (encoding(img))                                                                                         \
        {                                                                                                              \
            case pixel_encoding::unsigned8:                                                                            \
                return dynamic_image{func(view<std::uint8_t>(img), ##__VA_ARGS__)};                                    \
            case pixel_encoding::unsigned16:                                                                           \
                return dynamic_image{func(view<std::uint16_t>(img), ##__VA_ARGS__)};                                   \
            case pixel_encoding::unsigned32:                                                                           \
                return dynamic_image{func(view<std::uint32_t>(img), ##__VA_ARGS__)};                                   \
            case pixel_encoding::float32:                                                                              \
                return dynamic_image{func(view<float>(img), ##__VA_ARGS__)};                                           \
            case pixel_encoding::rgb24:                                                                                \
                return dynamic_image{func(view<rgb24>(img), ##__VA_ARGS__)};                                           \
            case pixel_encoding::rgba32:                                                                               \
                return dynamic_image{func(view<rgba32>(img), ##__VA_ARGS__)};                                          \
            case pixel_encoding::bgr24:                                                                                \
                return dynamic_image{func(view<bgr24>(img), ##__VA_ARGS__)};                                           \
            case pixel_encoding::bgra32:                                                                               \
                return dynamic_image{func(view<bgra32>(img), ##__VA_ARGS__)};                                          \
            default:                                                                                                   \
                throw imaging_exception();                                                                             \
        }                                                                                                              \
    }();

#define process_image_with_dst(src, dst, func, ...)                                                                    \
    [&]() {                                                                                                            \
        aeon_assert(encoding(src) == encoding(dst), "Encoding mismatch between source and destination.");              \
        switch (encoding(src))                                                                                         \
        {                                                                                                              \
            case pixel_encoding::unsigned8:                                                                            \
                func(view<std::uint8_t>(src), view<std::uint8_t>(dst), ##__VA_ARGS__);                                 \
                return;                                                                                                \
            case pixel_encoding::unsigned16:                                                                           \
                func(view<std::uint16_t>(src), view<std::uint16_t>(dst), ##__VA_ARGS__);                               \
                return;                                                                                                \
            case pixel_encoding::unsigned32:                                                                           \
                func(view<std::uint32_t>(src), view<std::uint32_t>(dst), ##__VA_ARGS__);                               \
                return;                                                                                                \
            case pixel_encoding::float32:                                                                              \
                func(view<float>(src), view<float>(dst), ##__VA_ARGS__);                                               \
                return;                                                                                                \
            case pixel_encoding::rgb24:                                                                                \
                func(view<rgb24>(src), view<rgb24>(dst), ##__VA_ARGS__);                                               \
                return;                                                                                                \
            case pixel_encoding::rgba32:                                                                               \
                func(view<rgba32>(src), view<rgba32>(dst), ##__VA_ARGS__);                                             \
                return;                                                                                                \
            case pixel_encoding::bgr24:                                                                                \
                func(view<bgr24>(src), view<bgr24>(dst), ##__VA_ARGS__);                                               \
                return;                                                                                                \
            case pixel_encoding::bgra32:                                                                               \
                func(view<bgra32>(src), view<bgra32>(dst), ##__VA_ARGS__);                                             \
            default:                                                                                                   \
                throw imaging_exception();                                                                             \
        }                                                                                                              \
    }();

} // namespace aeon::imaging

#include <aeon/imaging/impl/dynamic_image_impl.h>
