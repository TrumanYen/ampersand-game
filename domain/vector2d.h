#pragma once

#include <cmath>
#include <domain/vector2d_fwd.h>

template <Numeric T> class Vector2D {
public:
  Vector2D(T x, T y) : x(x), y(y) {}
  ~Vector2D() = default;

  T x;
  T y;

public:
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

  T magnitude() { return std::sqrt((x * x) + (y * y)); }

  T dot(Vector2D<T> other) const { return (x * other.x) + (y * other.y); }

  Vector2D<T> normalVector() const { return Vector2D<T>(-1.0 * y, x); }
};
