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
extern const char OBJ;
extern const int KDT_DEP;
extern const int BUFSIZE;

class Ray {
public:
  Vector position, direction;
  bool inside;
  Ray();
};

class Attribute {
public:
  Vector ka, kd, ks, kt;
  double index;
  bool hasimg = 0;
  std::vector< std::vector<Vector> > *img;
  Attribute();
  void loadImg(std::string filename);
};

class CollideInfo {
public:
  double distance = -1, index;
  int x, y;
  Vector normal;
};

class Ball {
public:
  Vector position;
  double radius;
  Attribute attribute;
  std::pair<int, int> getXY(Vector p, const Vector &normal);
  CollideInfo collide(const Ray &r);
};

class Rect {
public:
  Vector position, dx, dy;
  Attribute attribute;

  CollideInfo collide(const Ray &r);
};

class Tri {
public:
  Vector position, dx, dy, mn, mx;
  CollideInfo collide(const Ray &r);
};

class Obj {
public:
  Vector mn, mx;
  std::vector<Tri> *tri;
  Attribute attribute;
  bool hitbox(Vector mn, Vector mx, const Ray &r);
  void insert(int id, const Tri &tri, int dep, Vector mn, Vector mx);
  void load(std::string filename, const Vector &move, double scale);
  CollideInfo search(int id, const Ray &r, int dep, Vector mn, Vector mx);
  CollideInfo collide(const Ray &r);
};

void insertBox(std::vector< std::pair<char, void*> > &item, const Vector &p, const Vector &x, const Vector &y, const Vector &z, const Attribute &attr);

Ray reflect(const Ray &in, const Vector &position, const Vector &normal);

Ray transparent(const Ray &in, const Vector &position, const Vector &normal, const double index);

Ray diffuse(const Ray &in, const Vector &position, const Vector &normal);

#endif /* defined(__TraceRay__core__) */
