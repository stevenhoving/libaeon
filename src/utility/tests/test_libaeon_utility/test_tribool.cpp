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

#include <gtest/gtest.h>
#include <aeon/utility/tribool.h>

using namespace aeon;

TEST(test_tribool, test_tribool_default_false)
{
    EXPECT_FALSE(utility::tribool{});
}

TEST(test_tribool, test_tribool_boolean_constructor)
{
    EXPECT_TRUE(utility::tribool{true});
    EXPECT_FALSE(utility::tribool{false});
}

TEST(test_tribool, test_tribool_indeterminate_constructor)
{
    EXPECT_FALSE(utility::tribool{utility::indeterminate});

    utility::tribool val{utility::indeterminate};

    EXPECT_FALSE(val);
    EXPECT_TRUE(utility::indeterminate(val));
    EXPECT_TRUE(val.is_indeterminate());
}

TEST(test_tribool, test_tribool_and)
{
    utility::tribool val1{true};
    utility::tribool val2{true};
    utility::tribool val3{false};
    utility::tribool val4{utility::indeterminate};
    utility::tribool val5{utility::indeterminate};

    EXPECT_TRUE(val1 && val2);
    EXPECT_FALSE(val1 && val3);
    EXPECT_FALSE(val1 && val2 && val3);
    EXPECT_FALSE(val1 && val4);
    EXPECT_FALSE(val1 && val2 && val4);
    EXPECT_FALSE(val4 && val5);

    EXPECT_FALSE(val1 && val2 && utility::indeterminate);
    EXPECT_FALSE(utility::indeterminate && val1 && val2);
    EXPECT_FALSE(val1 && utility::indeterminate);
    EXPECT_FALSE(utility::indeterminate && val1);
}

TEST(test_tribool, test_tribool_or)
{
    utility::tribool val1{true};
    utility::tribool val2{true};
    utility::tribool val3{false};
    utility::tribool val4{false};
    utility::tribool val5{utility::indeterminate};
    utility::tribool val6{utility::indeterminate};

    EXPECT_TRUE(val1 || val2);
    EXPECT_TRUE(val1 || val3);
    EXPECT_TRUE(val2 || val3);
    EXPECT_TRUE(val1 || val6);
    EXPECT_FALSE(val3 || val4);
    EXPECT_FALSE(val4 || val5);
    EXPECT_FALSE(val5 || val6);
    EXPECT_FALSE(val3 || val6);

    EXPECT_TRUE(val1 || val3 || val5);
    EXPECT_TRUE(val2 || val5 || val6);
    EXPECT_FALSE(val3 || val5 || val6);

    EXPECT_TRUE(val1 || val2 || utility::indeterminate);
    EXPECT_TRUE(val1 || val3 || utility::indeterminate);
    EXPECT_TRUE(val2 || val3 || utility::indeterminate);
    EXPECT_TRUE(val1 || val6 || utility::indeterminate);
}

TEST(test_tribool, test_tribool_equals_tribool)
{
    utility::tribool val1{true};
    utility::tribool val2{true};
    utility::tribool val3{false};
    utility::tribool val4{false};
    utility::tribool val5{utility::indeterminate};
    utility::tribool val6{utility::indeterminate};

    EXPECT_TRUE(val1 == val2);
    EXPECT_FALSE(val1 == val3);
    EXPECT_FALSE(val1 == val5);

    EXPECT_TRUE(val3 == val4);
    EXPECT_FALSE(val3 == val1);
    EXPECT_FALSE(val3 == val5);

    // Indeterminate does never equal another indeterminate
    EXPECT_FALSE(val5 == val6);
    EXPECT_FALSE(val5 == val1);
    EXPECT_FALSE(val5 == val3);
}

TEST(test_tribool, test_tribool_equals_bool)
{
    utility::tribool val1{true};
    utility::tribool val2{false};
    utility::tribool val3{utility::indeterminate};

    EXPECT_TRUE(val1 == true);
    EXPECT_FALSE(val1 == false);
    EXPECT_TRUE(true == val1);
    EXPECT_FALSE(false == val1);

    EXPECT_TRUE(val2 == false);
    EXPECT_FALSE(val2 == true);
    EXPECT_TRUE(false == val2);
    EXPECT_FALSE(true == val2);

    // Indeterminate does never equal true or false
    EXPECT_FALSE(val3 == false);
    EXPECT_FALSE(val3 == true);
    EXPECT_FALSE(false == val3);
    EXPECT_FALSE(true == val3);
}

TEST(test_tribool, test_tribool_equals_indeterminate)
{
    utility::tribool val1{true};
    utility::tribool val2{false};
    utility::tribool val3{utility::indeterminate};

    EXPECT_FALSE(val1 == utility::indeterminate);
    EXPECT_FALSE(utility::indeterminate == val1);

    EXPECT_FALSE(val2 == utility::indeterminate);
    EXPECT_FALSE(utility::indeterminate == val2);

    // Indeterminate does never equal another indeterminate
    EXPECT_FALSE(val3 == utility::indeterminate);
    EXPECT_FALSE(utility::indeterminate == val3);
}

TEST(test_tribool, test_tribool_not_equals_tribool)
{
    utility::tribool val1{true};
    utility::tribool val2{true};
    utility::tribool val3{false};
    utility::tribool val4{false};
    utility::tribool val5{utility::indeterminate};
    utility::tribool val6{utility::indeterminate};

    EXPECT_FALSE(val1 != val2);
    EXPECT_TRUE(val1 != val3);
    EXPECT_TRUE(val1 != val5);

    EXPECT_FALSE(val3 != val4);
    EXPECT_TRUE(val3 != val1);
    EXPECT_TRUE(val3 != val5);

    // Indeterminate does never equal another indeterminate
    EXPECT_TRUE(val5 != val6);
    EXPECT_TRUE(val5 != val1);
    EXPECT_TRUE(val5 != val3);
}

TEST(test_tribool, test_tribool_not_equals_bool)
{
    utility::tribool val1{true};
    utility::tribool val2{false};
    utility::tribool val3{utility::indeterminate};

    EXPECT_FALSE(val1 != true);
    EXPECT_FALSE(true != val1);
    EXPECT_TRUE(val1 != false);
    EXPECT_TRUE(false != val1);

    EXPECT_FALSE(val2 != false);
    EXPECT_FALSE(false != val2);
    EXPECT_TRUE(val2 != true);
    EXPECT_TRUE(true != val2);

    EXPECT_TRUE(val3 != false);
    EXPECT_TRUE(false != val3);
    EXPECT_TRUE(val3 != true);
    EXPECT_TRUE(true != val3);
}

TEST(test_tribool, test_tribool_not_equals_indeterminate)
{
    utility::tribool val1{true};
    utility::tribool val2{false};
    utility::tribool val3{utility::indeterminate};

    EXPECT_TRUE(val1 != utility::indeterminate);
    EXPECT_TRUE(utility::indeterminate != val1);

    EXPECT_TRUE(val2 != utility::indeterminate);
    EXPECT_TRUE(utility::indeterminate != val2);

    // Indeterminate does never equal another indeterminate
    EXPECT_TRUE(val3 != utility::indeterminate);
    EXPECT_TRUE(utility::indeterminate != val3);
}