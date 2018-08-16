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
#include <aeon/math/vector2.h>

namespace aeon::fonts
{

enum class glyph_pixel_type
{
    gray,
    color
};

class glyph
{
    friend class face;

public:
    ~glyph() = default;

    glyph(const glyph &) = delete;
    auto operator=(const glyph &) -> glyph & = delete;

    glyph(glyph &&other) noexcept = default;
    auto operator=(glyph &&other) noexcept -> glyph & = default;

    auto &view() const noexcept
    {
        return view_;
    }

    auto &color_view() const noexcept
    {
        return color_view_;
    }

    auto offset() const noexcept
    {
        return offset_;
    }

    auto advance() const noexcept
    {
        return advance_;
    }

    auto pixel_type() const noexcept
    {
        return pixel_type_;
    }

private:
    explicit glyph(imaging::image_view<std::uint8_t> view, const math::vector2<int> &offset,
                   const math::vector2<int> &advance) noexcept
        : view_{std::move(view)}
        , color_view_{}
        , offset_{offset}
        , advance_{advance}
        , pixel_type_{glyph_pixel_type::gray}
    {
    }

    explicit glyph(imaging::image_view<imaging::bgra32> view, const math::vector2<int> &offset,
                   const math::vector2<int> &advance) noexcept
        : view_{}
        , color_view_{std::move(view)}
        , offset_{offset}
        , advance_{advance}
        , pixel_type_{glyph_pixel_type::color}
    {
    }

    imaging::image_view<std::uint8_t> view_;
    imaging::image_view<imaging::bgra32> color_view_;
    math::vector2<int> offset_;
    math::vector2<int> advance_;
    glyph_pixel_type pixel_type_;
};

} // namespace aeon::fonts