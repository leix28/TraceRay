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
  scene.camera.position = Vector(0, 0, 10);
  scene.camera.filmCenter = Vector(0, 0, 8);
  scene.camera.pixHeight = 1000;
  scene.camera.pixWidth = 1000;
  scene.camera.filmHeight = Vector(0, -1, 0);
  scene.camera.filmWidth = Vector(1, 0, 0);
  
  scene.ambLight = Vector(1, 1, 1);
  scene.MAX_DEP = 4;
  
  Ball *ball = new Ball();
  ball->position = Vector(-1, 0, -1);
  ball->radius = 1;
  ball->attribute.ks = Vector(0.5, 0.5, 0.5);
  ball->attribute.kd = Vector(0.8, 0.8, 0);
  ball->attribute.ka = Vector(0.2, 0.2, 0);
  ball->attribute.alpha = 30;
  ball->attribute.pd = Vector(0.8, 0.8, 0.8);
  ball->attribute.ps = Vector(0.2, 0.2, 0.2);
  scene.item.push_back(make_pair(BALL, ball));
  
  ball = new Ball();
  ball->position = Vector(1, 0, 1);
  ball->radius = 1;
  ball->attribute.ks = Vector(0.8, 0.8, 0.8);
  ball->attribute.kd = Vector(0, 0, 0.8);
  ball->attribute.ka = Vector(0, 0, 0.2);
  ball->attribute.alpha = 80;
  ball->attribute.pd = Vector(0, 0, 0.5);
  ball->attribute.ps = Vector(0, 0, 0.5);
  scene.item.push_back(make_pair(BALL, ball));
  
  Rect *rect = new Rect();
  rect->ptr = Vector(-50, -1, -50);
  rect->x = Vector(0, 0, 100);
  rect->y = Vector(100, 0, 0);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.9, 0.9, 0.9);
  rect->attribute.ka = Vector(0.1, 0.1, 0.1);
  rect->attribute.alpha = 1;
  rect->attribute.pd = Vector(0.9, 0.9, 0.9);
  rect->attribute.ps = Vector(0.1, 0.1, 0.1);
  scene.item.push_back(make_pair(RECT, rect));
  
  Light lit;
  lit.position = Vector(3, 3, 3);
  lit.diffuse = Vector(0.04, 0.04, 0.04);
  lit.specular = Vector(0.04, 0.04, 0.04);
  for (int i = -2; i <= 2; i++)
    for (int j = -2; j <= 2; j++) {
      lit.position[0] += 0.1 * i;
      lit.position[2] += 0.1 * j;
      scene.light.push_back(lit);
      lit.position[0] -= 0.1 * i;
      lit.position[2] -= 0.1 * j;
    }
  
  scene.render();
  scene.save("out.png");
  return 0;
}
