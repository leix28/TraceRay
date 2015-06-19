//
//  core.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "core.h"

const char BALL = 'b';
const char RECT = 'r';

CollideInfo Ball::collide(const Ray &r) {
  assert(fabs(norm(r.direction) - 1) < EPS);
  CollideInfo info;
  info.distance = -1;
  info.reflectValid = info.transparentValid = 0;
  Vector v = r.position - position;
  if (norm(v) < radius) return info;
  if (innerProduct(v, r.direction) > 0) return info;
  if (norm(crossProduct(v, r.direction)) > radius) return info;
  
  assert(sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius) >= 0);
  info.distance = -innerProduct(r.direction, v) - sqrt(sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius));
  info.reflectValid = 1;
  info.reflect.position = r.position + info.distance * r.direction;
  Vector n = info.reflect.position - position;
  assert(fabs(norm(info.reflect.position - position) - radius) < EPS);
  n = n / norm(n);
  info.reflect.direction = reflect(r.direction, n);
  info.reflectValid = 1;
  info.normal = n;
  return info;
}

CollideInfo Rect::collide(const Ray &r) {
  CollideInfo info;
  info.distance = -1;
  info.reflectValid = info.transparentValid = 0;
  
  Vector v = ptr - r.position;
  
  Vector n = crossProduct(x, y);
  n = n / norm(n);
  
  info.distance = innerProduct(n, v) / innerProduct(r.direction, n);
  if (info.distance < EPS) {
    info.distance = -1;
    return info;
  }
  
  Vector p = r.position + info.distance * r.direction;
  
  double ax = innerProduct(p - ptr, x / norm(x));
  double ay = innerProduct(p - ptr, y / norm(y));
  if (ax < 0 || ax > norm(x) || ay < 0 || ay > norm(y)) {
    info.distance = -1;
    return info;
  }
  info.reflectValid = 1;
  info.reflect.position = p;
  info.reflect.direction = reflect(r.direction, n);
  info.normal = n;
  return info;
}

Vector reflect(const Vector &in, const Vector &normal) {
  return in - 2 * innerProduct(in, normal) * normal;
}
