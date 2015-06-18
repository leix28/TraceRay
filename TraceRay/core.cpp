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

std::pair<double, Ray> collision(Ray r, Piece p) {
  auto n = crossProduct(p[1] - p[0], p[2] - p[0]);
  double a = innerProduct(p[0] - r.position, n);
  double b = innerProduct(r.direction, n);
  if (fabs(b) < EPS) return make_pair(-1, Ray());
  double t = a / b;
  if (t < EPS) return make_pair(-1, Ray());
  if (t > INFD) return make_pair(-1, Ray());
  auto x = r.position + r.direction * t;
  if (innerProduct(crossProduct(x - p[0], p[1] - p[0]), crossProduct(p[2] - p[0], p[1] - p[0])) < 0) return make_pair(-1, Ray());
  if (innerProduct(crossProduct(x - p[1], p[2] - p[1]), crossProduct(p[0] - p[1], p[2] - p[1])) < 0) return make_pair(-1, Ray());
  if (innerProduct(crossProduct(x - p[2], p[0] - p[2]), crossProduct(p[1] - p[2], p[0] - p[2])) < 0) return make_pair(-1, Ray());
  Ray ref;
  ref.position = x;
  n = n / norm(n);
  ref.direction = r.direction - 2 * innerProduct(r.direction, n) * n;
  assert(fabs(norm(ref.direction) - 1) < EPS);
  return make_pair(t, ref);
}