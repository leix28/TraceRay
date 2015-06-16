//
//  core.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "core.h"

Piece::Piece() {}

Piece::Piece(const Vector &x, const Vector &y, const Vector &z) {
  p[0] = x; p[1] = y; p[2] = z;
}

Vector& Piece::operator [] (const int id) {
  assert(id < 3);
  return p[id];
}

const Vector& Piece::operator [] (const int id) const {
  assert(id < 3);
  return p[id];
}

bool sameSign(double x, double y) {
  if (x > -0.0 && y > -0.0) return true;
  if (x < 0.0 && y < 0.0) return true;
  return false;
}

double collision(Ray r, Piece p) {
  auto n = crossProduct(p[1] - p[0], p[2] - p[0]);
  double a = innerProduct(r.position, n);
  double b = innerProduct(r.direction, n);
  if (fabs(b) < EPS) return -1;
  double t = a / b;
  if (t < 0) return -1;
  if (t > INFD) return -1;
  auto x = r.position + r.direction * t;
  if (!sameSign(innerProduct(x - p[0], p[1] - p[0]), innerProduct(p[2], p[1] - p[0]))) return -1;
  if (!sameSign(innerProduct(x - p[1], p[2] - p[1]), innerProduct(p[0], p[2] - p[1]))) return -1;
  if (!sameSign(innerProduct(x - p[2], p[0] - p[2]), innerProduct(p[1], p[0] - p[2]))) return -1;
  return t;
}