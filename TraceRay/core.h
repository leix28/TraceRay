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

struct Attribute {
  Vector diffuse, specular, transparent;
  double index;
};

struct Ray {
  Vector position, direction;
  double index;
};

class Piece {
public:
  Piece();
  Piece(const Vector &x, const Vector &y, const Vector &z);
  Vector& operator [] (const int id);
  const Vector& operator [] (const int id) const;
private:
  Vector p[3];
};

std::pair<double, Ray> collision(Ray r, Piece s);

#endif /* defined(__TraceRay__core__) */
