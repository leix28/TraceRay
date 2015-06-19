//
//  camera.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "camera.h"

Vector Camera::getFilm(int row, int col) {
  return filmCenter + filmHeight * ((double)row / pixHeight - 0.5) + filmWidth * ((double)col / pixWidth - 0.5);
}

Ray Camera::getRay(int row, int col) {
  Ray r;
  r.position = getFilm(row, col);
  r.direction = r.position - position;
  assert(norm(r.direction) > EPS);
  r.direction = r.direction / norm(r.direction);
  r.inside = 0;
  return r;
}