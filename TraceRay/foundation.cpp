//
//  foundation.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "foundation.h"

const double EPS = 1e-8;
const double INFD = 1e8;
const int BUFFER_SIZE = 1024;

Vector::Vector() {
  x = y = z = 0;
}

Vector::Vector(double _x, double _y, double _z) {
  x = _x; y = _y; z = _z;
}

double& Vector::operator [] (const int id) {
  if (id == 0) return x;
  if (id == 1) return y;
  if (id == 2) return z;
  assert(0);
}

double Vector::operator [] (const int id) const {
  if (id == 0) return x;
  if (id == 1) return y;
  if (id == 2) return z;
  assert(0);
}

double norm(const Vector &x) {
  return sqrt(innerProduct(x, x));
}

Vector operator + (const Vector &a, const Vector &b) {
  Vector c;
  for (int i = 0; i < 3; i++) c[i] = a[i] + b[i];
  return c;
}

Vector operator - (const Vector &a, const Vector &b) {
  Vector c;
  for (int i = 0; i < 3; i++) c[i] = a[i] - b[i];
  return c;
}

Vector operator * (const double a, const Vector &b) {
  Vector c;
  for (int i = 0; i < 3; i++) c[i] = a * b[i];
  return c;
}

Vector operator * (const Vector &a, const double b) {
  return b * a;
}

Vector operator * (const Vector &a, const Vector &b) {
  Vector c;
  for (int i = 0; i < 3; i++) c[i] = a[i] * b[i];
  return c;
}

Vector operator / (const Vector &a, const double b) {
  assert(fabs(b) >= EPS);
  return 1 / b * a;
}

double innerProduct(const Vector &a, const Vector &b) {
  double c = 0;
  for (int i = 0; i < 3; i++) c += a[i] * b[i];
  return c;
}

Vector crossProduct(const Vector &a, const Vector &b) {
  Vector c;
  c[0] = a[1] * b[2] - a[2] * b[1];
  c[1] = a[2] * b[0] - a[0] * b[2];
  c[2] = a[0] * b[1] - a[1] * b[0];
  return c;
}