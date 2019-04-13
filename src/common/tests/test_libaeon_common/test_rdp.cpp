// Copyright (c) 2012-2019 Robin Degen

#include <aeon/common/rdp.h>
#include <aeon/common/rdp_matchers.h>
#include <gtest/gtest.h>

using namespace aeon::common;

TEST(test_rdp, test_advance_reverse_eof_bof_current)
{
    rdp::parser parser{"123"};
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_TRUE(rdp::bof(parser));
    EXPECT_FALSE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_TRUE(rdp::bof(parser));
    EXPECT_EQ('1', rdp::current(parser));
    EXPECT_TRUE(parser.advance());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_EQ('2', rdp::current(parser));
    EXPECT_TRUE(parser.advance());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_EQ('3', rdp::current(parser));
    EXPECT_TRUE(parser.advance());
    EXPECT_TRUE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_FALSE(parser.advance());
    EXPECT_TRUE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_EQ('3', rdp::current(parser));
    EXPECT_TRUE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_FALSE(rdp::bof(parser));
    EXPECT_EQ('2', rdp::current(parser));
    EXPECT_TRUE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_TRUE(rdp::bof(parser));
    EXPECT_EQ('1', rdp::current(parser));
    EXPECT_FALSE(parser.reverse());
    EXPECT_FALSE(rdp::eof(parser));
    EXPECT_TRUE(rdp::bof(parser));
}

TEST(test_rdp, test_offset_check_char)
{
    rdp::parser parser{"123"};
    EXPECT_EQ(0, rdp::offset(parser));
    EXPECT_TRUE(parser.check('1'));
    EXPECT_EQ(1, rdp::offset(parser));
    EXPECT_FALSE(parser.check('1'));
    EXPECT_EQ(1, rdp::offset(parser));
    EXPECT_TRUE(parser.check('2'));
    EXPECT_EQ(2, rdp::offset(parser));
    EXPECT_FALSE(parser.check('2'));
    EXPECT_EQ(2, rdp::offset(parser));
    EXPECT_TRUE(parser.check('3'));
    EXPECT_EQ(3, rdp::offset(parser));
    EXPECT_FALSE(parser.check('3'));
    EXPECT_EQ(3, rdp::offset(parser));
}

TEST(test_rdp, test_offset_check_string)
{
    rdp::parser parser{"123"};
    EXPECT_EQ(0, rdp::offset(parser));
    EXPECT_FALSE(parser.check("13"));
    EXPECT_EQ(0, rdp::offset(parser));
    EXPECT_TRUE(parser.check("12"));
    EXPECT_EQ(2, rdp::offset(parser));
    EXPECT_FALSE(parser.check("34"));
    EXPECT_EQ(2, rdp::offset(parser));
    EXPECT_TRUE(parser.check("3"));
    EXPECT_EQ(3, rdp::offset(parser));
}

TEST(test_rdp, test_offset_skip)
{
    rdp::parser parser{"111122223333"};
    EXPECT_EQ(0, rdp::offset(parser));
    parser.skip('2');
    EXPECT_EQ(0, rdp::offset(parser));
    parser.skip('1');
    EXPECT_EQ(4, rdp::offset(parser));
    parser.skip('1');
    EXPECT_EQ(4, rdp::offset(parser));
    parser.skip('2');
    EXPECT_EQ(8, rdp::offset(parser));
    parser.skip('3');
    EXPECT_EQ(12, rdp::offset(parser));
}

TEST(test_rdp, test_offset_skip_until)
{
    rdp::parser parser{"111122223333"};
    EXPECT_EQ(0, rdp::offset(parser));
    parser.skip_until('1');
    EXPECT_EQ(0, rdp::offset(parser));
    parser.skip_until('2');
    EXPECT_EQ(4, rdp::offset(parser));
    parser.skip_until('2');
    EXPECT_EQ(4, rdp::offset(parser));
    parser.skip_until('3');
    EXPECT_EQ(8, rdp::offset(parser));
}

TEST(test_rdp, test_offset_match_until)
{
    rdp::parser parser{"111122223333"};
    EXPECT_EQ(0, rdp::offset(parser));
    EXPECT_EQ("1111", parser.match_until('2'));
    EXPECT_EQ("2222", parser.match_until('3'));
    EXPECT_EQ(std::nullopt, parser.match_until('4'));
}

TEST(test_rdp, test_offset_match_pred)
{
    rdp::parser parser{"1234abcd5678"};
    EXPECT_EQ(0, rdp::offset(parser));
    EXPECT_EQ(std::nullopt, parser.match([](const auto c) { return std::isalpha(c) != 0; }));
    EXPECT_EQ("1234", parser.match([](const auto c) { return std::isdigit(c) != 0; }));
    EXPECT_EQ("abcd", parser.match([](const auto c) { return std::isalpha(c) != 0; }));
    EXPECT_EQ(std::nullopt, parser.match([](const auto c) { return std::isalpha(c) != 0; }));
    EXPECT_EQ("5678", parser.match([](const auto c) { return std::isdigit(c) != 0; }));
}

TEST(test_rdp, test_offset_match_pred_indexed)
{
    rdp::parser parser{"1a2b3c4d"};
    EXPECT_EQ(0, rdp::offset(parser));
    EXPECT_EQ(std::nullopt, parser.match_indexed([](const auto c, const auto i) {
        if (i % 2 == 0)
            return std::isalpha(c) != 0;

        return std::isdigit(c) != 0;
    }));

    EXPECT_EQ("1a2b3c4d", parser.match_indexed([](const auto c, const auto i) {
        if (i % 2 == 0)
            return std::isdigit(c) != 0;

        return std::isalpha(c) != 0;
    }));
}

TEST(test_rdp, test_offset_match_regex)
{
    rdp::parser parser{"111122223333aaaabbbbcccc1234"};
    EXPECT_EQ(0, rdp::offset(parser));
    EXPECT_EQ(std::nullopt, parser.match_regex("[a-zA-Z]+"));
    EXPECT_EQ("111122223333", parser.match_regex("[1-3]+"));
    EXPECT_EQ(std::nullopt, parser.match_regex("[1-3]+"));
    EXPECT_EQ("aaaabbbbcccc", parser.match_regex("[a-zA-Z]+"));
    EXPECT_EQ(std::nullopt, parser.match_regex("[a-zA-Z]+"));
    EXPECT_EQ("123", parser.match_regex("[1-3]+"));
    EXPECT_EQ("4", parser.match_regex("[1-4]+"));
    EXPECT_EQ(std::nullopt, parser.match_regex(".*"));
}

TEST(test_rdp, test_offset_match_regex_empty_sequence)
{
    rdp::parser parser{"111122223333aaaabbbbcccc1234"};
    EXPECT_EQ(std::nullopt, parser.match_regex("[a-zA-Z]*"));
}

TEST(test_rdp, test_offset_match_advanced)
{
    rdp::parser parser{"Validvariable123 somethingElse {}"};
    rdp::parser parser2{"123Inalidvariable123 Hello {}"};
    rdp::parser parser3{"__123Validvariable123 123 {}"};
    EXPECT_EQ("Validvariable123", parser.match_regex("[a-zA-Z_][a-zA-Z0-9\\-_]*"));
    EXPECT_EQ(std::nullopt, parser2.match_regex("[a-zA-Z][a-zA-Z0-9\\-_]*"));
    EXPECT_EQ("__123Validvariable123", parser3.match_regex("[a-zA-Z_][a-zA-Z0-9\\-_]*"));
}

template <typename T>
void check_parse_decimal(const std::string_view str, const T expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_decimal<T>(parser));
}

TEST(test_rdp, test_parse_decimal_signed)
{
    check_parse_decimal<char>("-12", -12);
    check_parse_decimal<char>("12", 12);
    check_parse_decimal<short>("-1234", -1234);
    check_parse_decimal<short>("1234", 1234);
    check_parse_decimal<int>("-123456", -123456);
    check_parse_decimal<int>("123456", 123456);
    check_parse_decimal<long long>("-123456789", -123456789);
    check_parse_decimal<long long>("123456789", 123456789);
}

TEST(test_rdp, test_parse_decimal_unsigned)
{
    check_parse_decimal<unsigned char>("12", 12);
    check_parse_decimal<unsigned short>("1234", 1234);
    check_parse_decimal<unsigned int>("123456", 123456);
    check_parse_decimal<unsigned long long>("123456789", 123456789);
}

template <typename T>
void check_parse_binary(const std::string_view str, const T expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_binary<T>(parser));
}

TEST(test_rdp, test_parse_binary)
{
    check_parse_binary<unsigned char>("1010", 10);
    check_parse_binary<unsigned short>("1001001011010101", 37589);
    check_parse_binary<unsigned int>("10101001010001101001001011010101", 2839974613);
    check_parse_binary<unsigned long long>("100010001001100010100100101010010101001010001101001001011010101",
                                           4921399016379814613);
}

template <typename T>
void check_parse_binary_prefixed(const std::string_view str, const T expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_binary<T>(parser, "0b"));
}

TEST(test_rdp, test_parse_binary_prefixed)
{
    check_parse_binary_prefixed<unsigned char>("0b1010", 10);
    check_parse_binary_prefixed<unsigned short>("0b1001001011010101", 37589);
    check_parse_binary_prefixed<unsigned int>("0b10101001010001101001001011010101", 2839974613);
    check_parse_binary_prefixed<unsigned long long>("0b100010001001100010100100101010010101001010001101001001011010101",
                                                    4921399016379814613u);
}
template <typename T>
void check_parse_hex(const std::string_view str, const T expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_hexadecimal<T>(parser));
}

TEST(test_rdp, test_parse_hexadecimal)
{
    check_parse_hex<unsigned char>("BD", 189);
    check_parse_hex<unsigned short>("BD74", 48500);
    check_parse_hex<unsigned int>("F1DA85FC", 4057630204);
    check_parse_hex<unsigned long long>("57DB41EA587DB4FC", 6330726175962150140u);
}

template <typename T>
void check_parse_hex_prefixed(const std::string_view str, const T expected)
{
    rdp::parser parser{str};
    EXPECT_EQ(expected, rdp::parse_hexadecimal<T>(parser, "0x"));
}

TEST(test_rdp, test_parse_hexadecimal_prefixed)
{
    check_parse_hex_prefixed<unsigned char>("0xBD", 189);
    check_parse_hex_prefixed<unsigned short>("0xBD74", 48500);
    check_parse_hex_prefixed<unsigned int>("0xF1DA85FC", 4057630204);
    check_parse_hex_prefixed<unsigned long long>("0x57DB41EA587DB4FC", 6330726175962150140u);
}