//
//  Model.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "model.h"

void Model::loadShapeFromFile(std::string filename) {
  char buffer[BUFFER_SIZE];
  FILE *file = fopen(filename.c_str(), "r");
  
  std::vector<Vector> vertex;
  
  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    int ptr = 0;
    while (buffer[ptr] != 0 && buffer[ptr] != 'v' && buffer[ptr] != 'f') ptr++;
    if (buffer[ptr] == 'v') {
      Vector v;
      sscanf(buffer, "%*s%lf%lf%lf", &v[0], &v[1], &v[2]);
      vertex.push_back(v);
    }
    if (buffer[ptr] == 'f') {
      int x, y, z;
      sscanf(buffer, "%*s%d%d%d", &x, &y, &z);
      shape.push_back(Piece(vertex[x], vertex[y], vertex[z]));
    }
  }
  
  fclose(file);
}

double Model::collision(Ray r) {
  double t = INFD;
  for (const auto &p : shape) {
    double tmp = ::collision(r, p);
    if (tmp < 0) continue;
    t = min(t, tmp);
  }
  if (t == INFD) return -1;
  return t;
}