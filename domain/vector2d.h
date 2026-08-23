#pragma once

#include <type_traits>

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T> class Vector2D {
public:
  Vector2D(T x, T y) : x(x), y(y) {}
  ~Vector2D() = default;

  Vector2D<T> operator+(Vector2D<T> rhs) const {
    return Vector2D<T>(x + rhs.x, y + rhs.y);
  }

  Vector2D<T> operator-(Vector2D<T> rhs) const {
    return Vector2D<T>(x - rhs.x, y - rhs.y);
  }

  Vector2D<T> operator/(T scalar) const {
    return Vector2D<T>(x / scalar, y / scalar);
  }

  Vector2D<T> operator*(T scalar) const {
    return Vector2D<T>(x * scalar, y * scalar);
  }

  T squaredDistanceFrom(Vector2D<T> other) const {
    Vector2D<T> displacement = (*this) - other;
    return (displacement.x * displacement.x) +
           (displacement.y * displacement.y);
  }

  T x;
  T y;
};
