// Copyright (c) 2012-2019 Robin Degen

#include <aeon/streams/stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/size_filter.h>
#include <aeon/streams/stream_writer.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace aeon;

TEST(test_streams, test_size_filter_on_memory_device)
{
    auto pipeline = streams::size_filter<10>{} | streams::memory_device{};
    EXPECT_EQ(pipeline.size(), 0);
    pipeline.device().resize(100);
    EXPECT_EQ(pipeline.size(), 10);
    pipeline.device().resize(5);
    EXPECT_EQ(pipeline.size(), 5);
}
