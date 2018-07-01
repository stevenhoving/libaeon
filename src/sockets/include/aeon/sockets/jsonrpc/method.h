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

#include <aeon/sockets/jsonrpc/result.h>
#include <string>
#include <functional>
#include <json11.hpp>

namespace aeon::sockets::jsonrpc
{

class method
{
public:
    using signature = std::function<result(const json11::Json &)>;

    method(std::string name, signature func);
    ~method() = default;

    method(method &&) = default;
    auto operator=(method &&) -> method & = default;

    method(const method &) = default;
    auto operator=(const method &) -> method & = default;

    auto name() const noexcept -> const std::string &;
    auto operator()(const json11::Json &params) const -> result;

private:
    std::string name_;
    signature func_;
};

} // namespace aeon::sockets::jsonrpc
