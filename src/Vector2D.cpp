#include "../include/core.h"

Vector2D::Vector2D() {
  x = 0.0f;
  y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2D &Vector2D::AddVector(const Vector2D &vec) {
  this->x += vec.x;
  this->y += vec.y;

  return *this;
}

Vector2D &Vector2D::SubtractVector(const Vector2D &vec) {
  this->x -= vec.x;
  this->y -= vec.y;

  return *this;
}

Vector2D &Vector2D::MultiplyVector(const Vector2D &vec) {
  this->x *= vec.x;
  this->y *= vec.y;

  return *this;
}

Vector2D &Vector2D::DivideVector(const Vector2D &vec) {
  this->x /= vec.x;
  this->y /= vec.y;

  return *this;
}

// Operator overloaders

Vector2D &operator+(Vector2D &vec1, const Vector2D &vec2) {
  return vec1.AddVector(vec2);
}

Vector2D &operator-(Vector2D &vec1, const Vector2D &vec2) {
  return vec1.SubtractVector(vec2);
}

Vector2D &operator*(Vector2D &vec1, const Vector2D &vec2) {
  return vec1.MultiplyVector(vec2);
}

Vector2D &operator/(Vector2D &vec1, const Vector2D &vec2) {
  return vec1.DivideVector(vec2);
}

// += -= *= /=

Vector2D &Vector2D::operator+=(const Vector2D &vec) {
  return this->AddVector(vec);
}

Vector2D &Vector2D::operator-=(const Vector2D &vec) {
  return this->SubtractVector(vec);
}

Vector2D &Vector2D::operator*=(const Vector2D &vec) {
  return this->MultiplyVector(vec);
}

Vector2D &Vector2D::operator/=(const Vector2D &vec) {
  return this->DivideVector(vec);
}

// Printing Vector easily

void PrintVector(Vector2D vec) { ZeldaTrace("(", vec.x, ", ", vec.y, ")"); }
