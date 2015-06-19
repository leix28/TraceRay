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

int main(int argc, const char * argv[]) {
  scene.camera.position = Vector(0, 0, 5);
  scene.camera.filmCenter = Vector(0, 0, 4);
  scene.camera.pixHeight = 1000;
  scene.camera.pixWidth = 1000;
  scene.camera.filmHeight = Vector(0, -1, 0);
  scene.camera.filmWidth = Vector(1, 0, 0);
  
  scene.ambLight = Vector(1, 1, 1);
  
  Ball *ball = new Ball();
  ball->position = Vector(0, 0, 0);
  ball->radius = 1;
  ball->attribute.ks = Vector(0.3, 0.3, 0.3);
  ball->attribute.kd = Vector(0.8, 0.8, 0.8);
  ball->attribute.ka = Vector(0.2, 0.2, 0.2);
  ball->attribute.alpha = 100;
  scene.item.push_back(make_pair(BALL, ball));
  
  Rect *rect = new Rect();
  rect->ptr = Vector(-50, -50, -3);
  rect->x = Vector(100, 0, 0);
  rect->y = Vector(0, 100, 0);
  rect->attribute.ks = Vector(0.3, 0.3, 0.3);
  rect->attribute.kd = Vector(0.8, 0.8, 0.8);
  rect->attribute.ka = Vector(0.2, 0.2, 0.2);
  rect->attribute.alpha = 1;
  scene.item.push_back(make_pair(RECT, rect));
  
  Light lit;
  lit.position = Vector(10, 10, 10);
  lit.diffuse = Vector(1, 0, 0);
  lit.specular = Vector(1, 1, 1);
  scene.light.push_back(lit);
  
  scene.render();
  scene.save("out.png");
  return 0;
}
