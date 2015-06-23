//
//  foundation.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "foundation.h"

const double EPS = 1e-8;
const double EPS_LOOSE = 1e-3;
const double INFD = 1e10;
const int THREAD_NUM = 8;
const double PI = 3.1415926536;

Vector::Vector() {
  x = y = z = 0;
}

Vector::Vector(double _x, double _y, double _z) {
  x = _x; y = _y; z = _z;
}

double& Vector::operator [] (const int id) {
  assert(0 <= id && id < 3);
  return (id == 0) ? x : (id == 1) ? y : z;
}

double Vector::operator [] (const int id) const {
  assert(0 <= id && id < 3);
  return (id == 0) ? x : (id == 1) ? y : z;
}

double norm(const Vector &v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector operator - (const Vector &a) {
  return Vector(-a.x, -a.y, -a.z);
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
