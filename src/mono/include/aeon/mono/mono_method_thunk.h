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

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_thunk_base.h>
#include <aeon/mono/mono_type_conversion.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_object.h>
#include <mono/jit/jit.h>
#include <utility>

namespace aeon::mono
{

template <typename return_type_t>
class mono_method_thunk;

template <typename... args_t>
class mono_method_thunk<void(args_t...)> : public mono_thunk_base<void(MonoObject *, args_t...)>, public mono_object
{
public:
    mono_method_thunk()
        : mono_thunk_base<void(MonoObject *, args_t...)>()
        , mono_object()
    {
    }

    explicit mono_method_thunk(const mono_assembly &assembly, MonoObject *object, MonoMethod *method)
        : mono_thunk_base<void(MonoObject *, args_t...)>(assembly, method)
        , mono_object(object)
    {
    }

    ~mono_method_thunk() = default;

    mono_method_thunk(const mono_method_thunk &) = delete;
    auto operator=(const mono_method_thunk &) -> mono_method_thunk & = delete;

    mono_method_thunk(mono_method_thunk &&) noexcept = default;
    auto operator=(mono_method_thunk &&) noexcept -> mono_method_thunk & = default;

    void operator()(args_t... args)
    {
        MonoException *ex = nullptr;
        this->method_(this->object_,
                      convert_mono_type<args_t>::to_mono(*this->assembly_, std::forward<args_t>(args))..., &ex);

        if (ex)
            throw mono_thunk_exception{ex};
    }
};

template <typename return_type_t, typename... args_t>
class mono_method_thunk<return_type_t(args_t...)> : public mono_thunk_base<return_type_t(MonoObject *, args_t...)>,
                                                    public mono_object
{
public:
    mono_method_thunk()
        : mono_thunk_base<return_type_t(MonoObject *, args_t...)>()
        , mono_object()
    {
    }

    explicit mono_method_thunk(const mono_assembly &assembly, MonoObject *object, MonoMethod *method)
        : mono_thunk_base<return_type_t(MonoObject *, args_t...)>(assembly, method)
        , mono_object(object)
    {
    }

    ~mono_method_thunk() = default;

    mono_method_thunk(const mono_method_thunk &) = delete;
    auto operator=(const mono_method_thunk &) -> mono_method_thunk & = delete;

    mono_method_thunk(mono_method_thunk &&) noexcept = default;
    auto operator=(mono_method_thunk &&) noexcept -> mono_method_thunk & = default;

    auto operator()(args_t... args)
    {
        MonoException *ex = nullptr;
        auto result = this->method_(
            this->object_, convert_mono_type<args_t>::to_mono(*this->assembly_, std::forward<args_t>(args))..., &ex);

        if (ex)
            throw mono_thunk_exception{ex};

        return convert_mono_type<return_type_t>::from_mono(std::move(result));
    }
};

} // namespace aeon::mono
