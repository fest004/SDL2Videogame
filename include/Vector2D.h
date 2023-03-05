#ifndef VECTOR_2D_H
#define VECTOR_2D_H

class Vector2D {
public:
  // Making a Vector2D class consising of two floats in a vector,
  // Vector2D(x, y)
  // Added operator overloading for simple and quick vector math.
  // +-*/
  float x;
  float y;
  Vector2D();
  Vector2D(float x, float y);

  Vector2D &AddVector(const Vector2D &vec);
  Vector2D &SubtractVector(const Vector2D &vec);
  Vector2D &MultiplyVector(const Vector2D &vec);
  Vector2D &DivideVector(const Vector2D &vec);

  friend Vector2D &operator+(Vector2D &vec1, const Vector2D &vec2);
  friend Vector2D &operator-(Vector2D &vec1, const Vector2D &vec2);
  friend Vector2D &operator*(Vector2D &vec1, const Vector2D &vec2);
  friend Vector2D &operator/(Vector2D &vec1, const Vector2D &vec2);

  Vector2D &operator+=(const Vector2D &vec);
  Vector2D &operator-=(const Vector2D &vec);
  Vector2D &operator*=(const Vector2D &vec);
  Vector2D &operator/=(const Vector2D &vec);
};

#endif
