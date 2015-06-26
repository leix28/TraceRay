//
//  camera.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/21.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "camera.h"

Vector Camera::getFilm(double row, double col) {
  return filmCenter + filmHeight * (row - 0.5) + filmWidth * (col - 0.5);
}

std::vector<Ray> Camera::getRay(int row, int col) {
  Ray r;
  std::vector<Ray> rv;
  Vector target, d, p, n;
  p = getFilm((double)row / pixHeight, (double)col / pixWidth);
  d = p - position;
  d = d / norm(d);
  if (sample == 0) {
    r.position = p;
    r.direction = d;
    r.inside = 0;
    rv.push_back(r);
    return rv;
  }
  
  n = crossProduct(filmWidth, filmHeight);
  n = n / norm(n);
  
  
  target = p + d * dis / innerProduct(d, n);
  for (int i = 0; i < sample; i++) {
    double dx = (double)rand() / RAND_MAX * 2 - 1;
    double dy = (double)rand() / RAND_MAX * 2 - 1;
    r.position = getFilm((double)row / pixHeight + aperture * dx, (double)col / pixWidth + aperture * dy);
    r.direction = target - r.position;
    assert(norm(r.direction) > EPS);
    r.direction = r.direction / norm(r.direction);
    r.inside = 0;
    rv.push_back(r);
  }
  return rv;
}