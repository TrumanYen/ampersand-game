#pragma once

#include <type_traits>

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T> class Vector2D;
