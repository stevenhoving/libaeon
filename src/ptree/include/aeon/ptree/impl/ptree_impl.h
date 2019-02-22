// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/assert.h>

namespace aeon::ptree
{

inline property_tree::property_tree()
    : value_{}
{
}

inline property_tree::property_tree(std::nullptr_t)
    : value_{}
{
}

inline property_tree::property_tree(const int value)
    : value_{static_cast<std::int64_t>(value)}
{
}

inline property_tree::property_tree(const std::int64_t value)
    : value_{value}
{
}

inline property_tree::property_tree(const double value)
    : value_{value}
{
}

inline property_tree::property_tree(const array &value)
    : value_{value}
{
}

inline property_tree::property_tree(array &&value)
    : value_{std::move(value)}
{
}

inline property_tree::property_tree(const object &value)
    : value_{value}
{
}

inline property_tree::property_tree(object &&value)
    : value_{std::move(value)}
{
}

inline property_tree::property_tree(const bool value)
    : value_{value}
{
}

inline property_tree::property_tree(const char *const value)
    : value_{std::string{value}}
{
}

inline property_tree::property_tree(const std::string &value)
    : value_{value}
{
}

inline property_tree::property_tree(std::string &&value)
    : value_{std::move(value)}
{
}

inline property_tree::property_tree(const utility::uuid &uuid)
    : value_{uuid}
{
}

inline property_tree::property_tree(utility::uuid &&uuid)
    : value_{std::move(uuid)}
{
}

template <typename T>
inline auto property_tree::is_type() const noexcept
{
    return std::holds_alternative<T>(value_);
}

inline auto property_tree::is_null() const noexcept
{
    return is_type<std::monostate>();
}

inline auto property_tree::is_array() const noexcept
{
    return is_type<array>();
}

inline auto property_tree::is_object() const noexcept
{
    return is_type<object>();
}

inline auto property_tree::is_string() const noexcept
{
    return is_type<std::string>();
}

inline auto property_tree::is_uuid() const noexcept
{
    return is_type<utility::uuid>();
}

inline auto property_tree::is_integer() const noexcept
{
    return is_type<std::int64_t>();
}

inline auto property_tree::is_double() const noexcept
{
    return is_type<double>();
}

inline auto property_tree::is_bool() const noexcept
{
    return is_type<bool>();
}

inline auto property_tree::value() noexcept -> property_tree::variant_type &
{
    return value_;
}

inline auto property_tree::value() const noexcept -> const property_tree::variant_type &
{
    return value_;
}

inline auto property_tree::array_value() -> array &
{
    aeon_assert(is_array(), "Value is not an array.");
    return std::get<array>(value());
}

inline auto property_tree::array_value() const -> const array &
{
    aeon_assert(is_array(), "Value is not an array.");
    return std::get<array>(value());
}

inline auto property_tree::object_value() -> object &
{
    aeon_assert(is_object(), "Value is not an object.");
    return std::get<object>(value());
}

inline auto property_tree::object_value() const -> const object &
{
    aeon_assert(is_object(), "Value is not an object.");
    return std::get<object>(value());
}

inline auto property_tree::uuid_value() const -> const utility::uuid &
{
    aeon_assert(is_uuid(), "Value is not a uuid.");
    return std::get<utility::uuid>(value());
}

inline auto property_tree::string_value() const -> const std::string &
{
    aeon_assert(is_string(), "Value is not a string.");
    return std::get<std::string>(value());
}

inline auto property_tree::integer_value() const -> std::int64_t
{
    aeon_assert(is_integer(), "Value is not an integer.");
    return std::get<std::int64_t>(value());
}

inline auto property_tree::double_value() const -> double
{
    aeon_assert(is_double(), "Value is not a double.");
    return std::get<double>(value());
}

inline auto property_tree::bool_value() const -> bool
{
    aeon_assert(is_bool(), "Value is not a bool.");
    return std::get<bool>(value());
}

inline auto property_tree::at(const object::key_type &key) -> object::value_type &
{
    return object_value().at(key);
}

inline auto property_tree::at(const object::key_type &key) const -> const object::value_type &
{
    return object_value().at(key);
}

inline auto property_tree::operator[](const object::key_type &key) -> object::value_type &
{
    if (is_null())
        value_ = object{};

    return object_value()[key];
}

inline auto property_tree::operator[](object::key_type &&key) -> object::value_type &
{
    if (is_null())
        value_ = object{};

    return object_value()[std::move(key)];
}

inline auto property_tree::operator=(const std::nullptr_t) -> property_tree &
{
    value_ = {};
    return *this;
}

inline auto property_tree::operator=(const int value) -> property_tree &
{
    value_ = static_cast<std::int64_t>(value);
    return *this;
}

inline auto property_tree::operator=(const std::int64_t value) -> property_tree &
{
    value_ = value;
    return *this;
}

inline auto property_tree::operator=(const double value) -> property_tree &
{
    value_ = value;
    return *this;
}

inline auto property_tree::operator=(const array &value) -> property_tree &
{
    value_ = value;
    return *this;
}

inline auto property_tree::operator=(array &&value) -> property_tree &
{
    value_ = std::move(value);
    return *this;
}

inline auto property_tree::operator=(const object &value) -> property_tree &
{
    value_ = value;
    return *this;
}

inline auto property_tree::operator=(object &&value) -> property_tree &
{
    value_ = value;
    return *this;
}

inline auto property_tree::operator=(const char *const value) -> property_tree &
{
    value_ = std::string{value};
    return *this;
}

inline auto property_tree::operator=(const std::string &value) -> property_tree &
{
    value_ = value;
    return *this;
}

inline auto property_tree::operator=(std::string &&value) -> property_tree &
{
    value_ = std::move(value);
    return *this;
}

inline auto property_tree::operator=(const utility::uuid &value) -> property_tree &
{
    value_ = value;
    return *this;
}

inline auto property_tree::operator=(utility::uuid &&value) -> property_tree &
{
    value_ = std::move(value);
    return *this;
}

inline auto property_tree::operator==(const property_tree &other) const noexcept -> bool
{
    return value_ == other.value_;
}

inline auto property_tree::operator!=(const property_tree &other) const noexcept -> bool
{
    return !(*this == other);
}

inline auto operator==(const property_tree &lhs, const std::nullptr_t) noexcept -> bool
{
    return lhs.is_null();
}

inline auto operator!=(const property_tree &lhs, const std::nullptr_t) noexcept -> bool
{
    return !lhs.is_null();
}

inline auto operator==(const std::nullptr_t, const property_tree &rhs) noexcept -> bool
{
    return rhs.is_null();
}

inline auto operator!=(const std::nullptr_t, const property_tree &rhs) noexcept -> bool
{
    return !rhs.is_null();
}

inline auto operator==(const property_tree &lhs, const int rhs) -> bool
{
    if (!lhs.is_integer())
        return false;

    return lhs.integer_value() == static_cast<std::int64_t>(rhs);
}

inline auto operator!=(const property_tree &lhs, const int rhs) -> bool
{
    return !(lhs == rhs);
}

inline auto operator==(const int lhs, const property_tree &rhs) -> bool
{
    return rhs == lhs;
}

inline auto operator!=(const int lhs, const property_tree &rhs) -> bool
{
    return rhs != lhs;
}

inline auto operator==(const property_tree &lhs, const std::int64_t rhs) -> bool
{
    if (!lhs.is_integer())
        return false;

    return lhs.integer_value() == rhs;
}

inline auto operator!=(const property_tree &lhs, const std::int64_t rhs) -> bool
{
    return !(lhs == rhs);
}

inline auto operator==(const std::int64_t lhs, const property_tree &rhs) -> bool
{
    return rhs == lhs;
}

inline auto operator!=(const std::int64_t lhs, const property_tree &rhs) -> bool
{
    return rhs != lhs;
}

inline auto operator==(const property_tree &lhs, const double rhs) -> bool
{
    if (!lhs.is_double())
        return false;

    return lhs.double_value() == rhs;
}

inline auto operator!=(const property_tree &lhs, const double rhs) -> bool
{
    return !(lhs == rhs);
}

inline auto operator==(const double lhs, const property_tree &rhs) -> bool
{
    return rhs == lhs;
}

inline auto operator!=(const double lhs, const property_tree &rhs) -> bool
{
    return rhs != lhs;
}

inline auto operator==(const property_tree &lhs, const array &rhs) -> bool
{
    if (!lhs.is_array())
        return false;

    return lhs.array_value() == rhs;
}

inline auto operator!=(const property_tree &lhs, const array &rhs) -> bool
{
    return !(lhs == rhs);
}

inline auto operator==(const array &lhs, const property_tree &rhs) -> bool
{
    return rhs == lhs;
}

inline auto operator!=(const array &lhs, const property_tree &rhs) -> bool
{
    return rhs != lhs;
}

inline auto operator==(const property_tree &lhs, const object &rhs) -> bool
{
    if (!lhs.is_object())
        return false;

    return lhs.object_value() == rhs;
}

inline auto operator!=(const property_tree &lhs, const object &rhs) -> bool
{
    return !(lhs == rhs);
}

inline auto operator==(const object &lhs, const property_tree &rhs) -> bool
{
    return rhs == lhs;
}

inline auto operator!=(const object &lhs, const property_tree &rhs) -> bool
{
    return rhs != lhs;
}

inline auto operator==(const property_tree &lhs, const char *const rhs) -> bool
{
    if (!lhs.is_string())
        return false;

    return lhs.string_value() == rhs;
}

inline auto operator!=(const property_tree &lhs, const char *const rhs) -> bool
{
    return !(lhs == rhs);
}

inline auto operator==(const char *const lhs, const property_tree &rhs) -> bool
{
    return rhs == lhs;
}

inline auto operator!=(const char *const lhs, const property_tree &rhs) -> bool
{
    return rhs != lhs;
}

inline auto operator==(const property_tree &lhs, const std::string &rhs) -> bool
{
    if (!lhs.is_string())
        return false;

    return lhs.string_value() == rhs;
}

inline auto operator!=(const property_tree &lhs, const std::string &rhs) -> bool
{
    return !(lhs == rhs);
}

inline auto operator==(const std::string &lhs, const property_tree &rhs) -> bool
{
    return rhs == lhs;
}

inline auto operator!=(const std::string &lhs, const property_tree &rhs) -> bool
{
    return rhs != lhs;
}

inline auto operator==(const property_tree &lhs, const utility::uuid &rhs) -> bool
{
    if (!lhs.is_uuid())
        return false;

    return lhs.uuid_value() == rhs;
}

inline auto operator!=(const property_tree &lhs, const utility::uuid &rhs) -> bool
{
    return !(lhs == rhs);
}

inline auto operator==(const utility::uuid &lhs, const property_tree &rhs) -> bool
{
    return rhs == lhs;
}

inline auto operator!=(const utility::uuid &lhs, const property_tree &rhs) -> bool
{
    return rhs != lhs;
}

} // namespace aeon::ptree