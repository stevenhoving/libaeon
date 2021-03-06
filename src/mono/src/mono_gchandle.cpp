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

#include <aeon/mono/mono_gchandle.h>
#include <aeon/mono/mono_object.h>
#include <utility>

namespace aeon
{
namespace mono
{

mono_gchandle::mono_gchandle(mono_object &obj)
    : mono_gchandle(obj.get_mono_object())
{
}

mono_gchandle::mono_gchandle(MonoObject *obj)
    : handle_(mono_gchandle_new(obj, 1))
{
}

mono_gchandle::~mono_gchandle()
{
    if (handle_ != 0)
        mono_gchandle_free(handle_);
}

mono_gchandle::mono_gchandle(mono_gchandle &&o)
    : handle_(std::move(o.handle_))
{
    o.handle_ = 0;
}

auto mono_gchandle::operator=(mono_gchandle &&o) -> mono_gchandle &
{
    handle_ = std::move(o.handle_);
    o.handle_ = 0;
    return *this;
}

} // namespace mono
} // namespace aeon
