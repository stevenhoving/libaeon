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

#include <aeon/hdf5/hdf5_scoped_create_group.h>
#include <stdexcept>

namespace aeon
{
namespace hdf5
{

hdf5_scoped_create_group::hdf5_scoped_create_group(const hid_t file, const std::string &name)
    : handle_(-1)
{
    handle_ = H5Gcreate2(file, name.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    if (handle_ < 0)
        throw std::runtime_error("Could not create group '" + name + "'.");
}

hdf5_scoped_create_group::~hdf5_scoped_create_group()
{
    if (handle_ >= 0)
        H5Gclose(handle_);
}

hdf5_scoped_create_group::hdf5_scoped_create_group(hdf5_scoped_create_group &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

hdf5_scoped_create_group &hdf5_scoped_create_group::operator=(hdf5_scoped_create_group &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

} // namespace hdf5
} // namespace aeon
