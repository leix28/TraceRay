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
  
  if (r.inside) {
    if (norm(r.position - position) > radius + EPS) return  info;
    double tmp = sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius);
    assert(tmp >= -EPS);
    if (tmp < 0) tmp = 0;
    info.distance = -innerProduct(r.direction, v) + sqrt(tmp);
    assert(info.distance >= -EPS);
    if (info.distance < 0) info.distance = 0;
    info.reflectValid = 1;
    info.reflect.position = r.position + info.distance * r.direction;
    assert(fabs(norm(info.reflect.position - position) - radius) < EPS);
    Vector n = position - info.reflect.position;
    n = n / norm(n);
    info.reflect.direction = reflect(r.direction, n);
    info.reflect.inside = 1;
    info.normal = n;
    
    double cosTheta = 1 - (1 - sqr(innerProduct(r.direction, n))) * sqr(attribute.index);
    if (cosTheta >= 0 && cosTheta <= 1) {
      cosTheta = sqrt(cosTheta);
      info.transparentValid = 1;
      info.transparent.position = info.reflect.position;
      info.transparent.direction = attribute.index * r.direction - (attribute.index * innerProduct(r.direction, n) + cosTheta) * n;
      info.transparent.direction = info.transparent.direction / norm(info.transparent.direction);
      
      info.transparent.inside = 0;
    }
    
    return info;
  } else {
    if (innerProduct(v, r.direction) > 0) return info;
    
    if (sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius) < 0) return info;
    info.distance = -innerProduct(r.direction, v) - sqrt(sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius));
    info.reflectValid = 1;
    info.reflect.position = r.position + info.distance * r.direction;
    Vector n = info.reflect.position - position;
    assert(fabs(norm(info.reflect.position - position) - radius) < EPS);
    n = n / norm(n);
    info.reflect.direction = reflect(r.direction, n);
    info.reflect.inside = 0;
    info.normal = n;
    
    double cosTheta = 1 - (1 - sqr(innerProduct(r.direction, n))) / sqr(attribute.index);
    if (cosTheta >= 0 && cosTheta <= 1) {
      cosTheta = sqrt(cosTheta);
      info.transparentValid = 1;
      info.transparent.position = info.reflect.position;
      info.transparent.direction = 1 / attribute.index * r.direction - (1 / attribute.index * innerProduct(r.direction, n) + cosTheta) * n;
      info.transparent.direction = info.transparent.direction / norm(info.transparent.direction);
      info.transparent.inside = 1;
    }
    
    return info;
  }
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
  info.reflect.inside = r.inside;
  
  return info;
}

Vector reflect(const Vector &in, const Vector &normal) {
  return in - 2 * innerProduct(in, normal) * normal;
}

void insertBox(std::vector< std::pair<char, void*> > &item, const Vector &p, const Vector &x, const Vector &y, const Vector &z, const Attribute &attr) {
  Rect *rect = new Rect();
  rect->attribute = attr;
  rect->ptr = p;
  rect->x = y;
  rect->y = x;
  item.push_back(make_pair(RECT, rect));
  
  rect = new Rect();
  rect->attribute = attr;
  rect->ptr = p;
  rect->x = x;
  rect->y = z;
  item.push_back(make_pair(RECT, rect));

  rect = new Rect();
  rect->attribute = attr;
  rect->ptr = p;
  rect->x = z;
  rect->y = y;
  item.push_back(make_pair(RECT, rect));
  
  Vector pp = p + x + y + z;
  rect = new Rect();
  rect->attribute = attr;
  rect->ptr = pp;
  rect->x = -x;
  rect->y = -y;
  item.push_back(make_pair(RECT, rect));

  rect = new Rect();
  rect->attribute = attr;
  rect->ptr = pp;
  rect->x = -z;
  rect->y = -x;
  item.push_back(make_pair(RECT, rect));

  rect = new Rect();
  rect->attribute = attr;
  rect->ptr = pp;
  rect->x = -y;
  rect->y = -z;
  item.push_back(make_pair(RECT, rect));

}
