//
//  foundation.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "foundation.h"

const double EPS = 1e-8;

Vector::Vector() {
  x = y = z = 0;
}

Vector::Vector(double _x, double _y, double _z) {
  x = _x; y = _y; z = _z;
}

Vector operator + (const Vector &a, const Vector &b) {
  return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator - (const Vector &a, const Vector &b) {
  return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector operator * (const double a, const Vector &b) {
  return Vector(a * b.x, a * b.y, a * b.z);
}

Vector operator * (const Vector &a, const double b) {
  return Vector(a.x * b, a.y * b, a.z * b);
}

Vector operator * (const Vector &a, const Vector &b) {
  return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector operator / (const Vector &a, const double b) {
  return Vector(a.x / b, a.y / b, a.z / b);
}

double innerProduct(const Vector &a, const Vector &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector crossProduct(const Vector &a, const Vector &b) {
  return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}