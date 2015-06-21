//
//  core.h
//  TraceRay
//
//  Created by LazyLie on 15/6/21.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__core__
#define __TraceRay__core__

#include <stdio.h>
#include "foundation.h"

extern const char RECT;
extern const char BALL;

class Ray {
public:
  Vector position, direction;
  bool inside;
};

class Attribute {
public:
  Vector ka, kd, ks, kt;
  double index;
};

class CollideInfo {
public:
  double distance, index;
  Vector normal;
};

class Ball {
public:
  Vector position;
  double radius;
  Attribute attribute;
  
  CollideInfo collide(const Ray &r);
};

class Rect {
public:
  Vector position, dx, dy;
  Attribute attribute;

  CollideInfo collide(const Ray &r);
};

void insertBox(std::vector< std::pair<char, void*> > &item, const Vector &p, const Vector &x, const Vector &y, const Vector &z, const Attribute &attr);

Ray reflect(const Ray &in, const Vector &position, const Vector &normal);

Ray transparent(const Ray &in, const Vector &position, const Vector &normal, const double index);

#endif /* defined(__TraceRay__core__) */
