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

#include <aeon/testing/temporary_file_fixture.h>
#include <aeon/filesystem/filesystem.h>

namespace aeon
{
namespace testutils
{

temporary_file::temporary_file()
    : path_(filesystem::generate_temporary_file_path())
{
}

temporary_file::temporary_file(const std::string &extension)
    : path_(filesystem::generate_temporary_file_path() + "." + extension)
{
}

temporary_file::~temporary_file()
{
    if (filesystem::exists(path_))
        delete_temporary_file();
}

auto temporary_file::get_temporary_file_path() const -> std::string
{
    return path_;
}

auto temporary_file::assert_temporary_file_present() const -> bool
{
    return filesystem::exists(path_);
}

void temporary_file::delete_temporary_file() const
{
    filesystem::delete_file(path_);
}

} // namespace testutils
} // namespace aeon
