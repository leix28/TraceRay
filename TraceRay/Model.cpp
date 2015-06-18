//
//  Model.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "model.h"

void Model::loadShapeFromFile(std::string filename, double s, double dx, double dy, double dz) {
  char buffer[BUFFER_SIZE];
  FILE *file = fopen(filename.c_str(), "r");
  
  std::vector<Vector> vertex;
  
  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    int ptr = 0;
    while (buffer[ptr] != 0 && buffer[ptr] != 'v' && buffer[ptr] != 'f') ptr++;
    if (buffer[ptr] == 'v') {
      Vector v;
      sscanf(buffer, "%*s%lf%lf%lf", &v[0], &v[1], &v[2]);
      v[0] = v[0] * s + dx;
      v[1] = v[1] * s + dy;
      v[2] = v[2] * s + dz;
      vertex.push_back(v);
    }
    if (buffer[ptr] == 'f') {
      int x, y, z;
      sscanf(buffer, "%*s%d%d%d", &x, &y, &z);
      shape.push_back(Piece(vertex[x - 1], vertex[y - 1], vertex[z - 1]));
    }
  }
  
  fclose(file);
}

std::pair<double, Ray> Model::collision(Ray r) {
  double t = INFD;
  Ray ref;
  for (const auto &p : shape) {
    auto tmp = ::collision(r, p);
    if (tmp.first < EPS) continue;
    if (tmp.first < t) {
      t = tmp.first;
      ref = tmp.second;
    }
  }
  if (t == INFD) return make_pair(-1, Ray());
  return make_pair(t, ref);
}