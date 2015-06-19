//
//  core.h
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__core__
#define __TraceRay__core__

#include <stdio.h>
#include "foundation.h"
extern const char BALL;
extern const char RECT;

struct Attribute {
  Vector ks, kd, ka;  //Phong specular/diffuse/ambient
  double alpha;       //Phone shininess
  Vector pd, ps, pt;  //TraceRay diffuse/specular/transparent
  double index;
};

struct Ray {
  Vector position, direction;
  bool inside;
};

struct CollideInfo {
  double distance;
  Ray reflect, transparent;
  Vector normal;
  bool reflectValid, transparentValid;
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
  Vector ptr, x, y;
  Attribute attribute;
  CollideInfo collide(const Ray &r);
};

class Light {
public:
  Vector position, specular, diffuse;
};

Vector reflect(const Vector &in, const Vector &normal);

void insertBox(std::vector< std::pair<char, void*> > &item, const Vector &p, const Vector &x, const Vector &y, const Vector &z, const Attribute &attr);

#endif /* defined(__TraceRay__core__) */
