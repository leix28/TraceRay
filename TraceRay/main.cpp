//
//  main.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/10.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include <iostream>
#include "scene.h"

Scene scene;

void loadConfig() {
  /* config format
   diffuse light
   
   camera position
   pix width height
   film center
   film width
   film height
   
   number of object
   
      object name
   */
  
  FILE *file = fopen("config", "r");
  
  double x, y, z;
  fscanf(file, "%lf%lf%lf", &x, &y, &z);
  scene.diffLight = Vector(x, y, z);

  fscanf(file, "%lf%lf%lf", &x, &y, &z);
  scene.camera.position = Vector(x, y, z);

  int u, v;
  fscanf(file, "%d%d", &u, &v);
  scene.camera.pixWidth = u;
  scene.camera.pixHeight = v;
  
  fscanf(file, "%lf%lf%lf", &x, &y, &z);
  scene.camera.filmCenter = Vector(x, y, z);
  
  fscanf(file, "%lf%lf%lf", &x, &y, &z);
  scene.camera.filmWidth = Vector(x, y, z);
  fscanf(file, "%lf%lf%lf", &x, &y, &z);
  scene.camera.filmHeight = Vector(x, y, z);
  
  int n;
  fscanf(file, "%d", &n);
  scene.model.clear();
  scene.model.resize(n);
  char filename[BUFFER_SIZE];
  for (int i = 0; i < n; i++) {
    fscanf(file, "%s", filename);
    scene.model[i].loadShapeFromFile(std::string(filename));
  }
  
  fclose(file);
}

int main(int argc, const char * argv[]) {
  loadConfig();
  scene.render();
  scene.saveToFile("out.png");
  return 0;
}
