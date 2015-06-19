//
//  camera.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
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
  n = crossProduct(filmWidth, filmHeight);
  n = n / norm(n);
  target = p + d * dis / innerProduct(d, n);
  for (int i = -sample; i <= sample; i++)
    for (int j = -sample; j <= sample; j++) {
      r.position = getFilm((double)row / pixHeight + aperture * i / sample, (double)col / pixWidth + aperture * j / sample);
      r.direction = target - r.position;
      assert(norm(r.direction) > EPS);
      r.direction = r.direction / norm(r.direction);
      r.inside = 0;
      rv.push_back(r);
    }
  return rv;
}