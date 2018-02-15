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

#include <aeon/sockets/http/method.h>

namespace aeon::sockets::http
{

struct method_string_lookup_t
{
    std::string str;
    method method = method::invalid;
};

static const method_string_lookup_t method_string_lookup[] = {{"GET", method::get},
                                                              {"HEAD", method::head},
                                                              {"POST", method::post},
                                                              {"PUT", method::put},
                                                              {"DELETE", method::delete_method},
                                                              {"OPTIONS", method::options},
                                                              {"PATCH", method::patch}};

auto string_to_method(const std::string_view &str) noexcept -> method
{
    for (const auto &method_string : method_string_lookup)
    {
        if (method_string.str == str)
            return method_string.method;
    }

    return method::invalid;
}

} // namespace aeon::sockets::http
