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
  scene.camera.position = Vector(5, 5, 20);
  scene.camera.filmCenter = Vector(5, 5, 10);
  scene.camera.pixHeight = 500;
  scene.camera.pixWidth = 500;
  scene.camera.filmHeight = Vector(0, -10, 0);
  scene.camera.filmWidth = Vector(10, 0, 0);
  
  scene.ambLight = Vector(1, 1, 1);
  scene.MAX_DEP = 10;
  
  //ceil
  Rect *rect = new Rect();
  rect->ptr = Vector(0, 10, 0);
  rect->x = Vector(10, 0, 0);
  rect->y = Vector(0, 0, 10);
  rect->attribute.ks = Vector(0.1, 0.1, 0.1);
  rect->attribute.kd = Vector(0.6, 0.6, 0.6);
  rect->attribute.ka = Vector(0.3, 0.3, 0.3);
  rect->attribute.alpha = 10;
  rect->attribute.pd = Vector(0.8, 0.8, 0.8);
  rect->attribute.ps = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));
  
  //floor
  rect = new Rect();
  rect->ptr = Vector(0, 0, 0);
  rect->x = Vector(0, 0, 10);
  rect->y = Vector(10, 0, 0);
  rect->attribute.ks = Vector(0.1, 0.1, 0.1);
  rect->attribute.kd = Vector(0.6, 0.6, 0.6);
  rect->attribute.ka = Vector(0.3, 0.3, 0.3);
  rect->attribute.alpha = 10;
  rect->attribute.pd = Vector(0.8, 0.8, 0.8);
  rect->attribute.ps = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));
  
  //left
  rect = new Rect();
  rect->ptr = Vector(0, 0, 0);
  rect->x = Vector(0, 10, 0);
  rect->y = Vector(0, 0, 10);
  rect->attribute.ks = Vector(0.1, 0.1, 0.1);
  rect->attribute.kd = Vector(0.6, 0.6, 0.6);
  rect->attribute.ka = Vector(0.3, 0.3, 0.3);
  rect->attribute.alpha = 10;
  rect->attribute.pd = Vector(0.8, 0, 0);
  rect->attribute.ps = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));
  
  //right
  rect = new Rect();
  rect->ptr = Vector(10, 0, 0);
  rect->x = Vector(0, 0, 10);
  rect->y = Vector(0, 10, 0);
  rect->attribute.ks = Vector(0.1, 0.1, 0.1);
  rect->attribute.kd = Vector(0.6, 0.6, 0.6);
  rect->attribute.ka = Vector(0.3, 0.3, 0.3);
  rect->attribute.alpha = 10;
  rect->attribute.pd = Vector(0, 0.8, 0);
  rect->attribute.ps = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));
  
  //back
  rect = new Rect();
  rect->ptr = Vector(0, 0, 0);
  rect->x = Vector(10, 0, 0);
  rect->y = Vector(0, 10, 0);
  rect->attribute.ks = Vector(0.1, 0.1, 0.1);
  rect->attribute.kd = Vector(0.6, 0.6, 0.6);
  rect->attribute.ka = Vector(0.3, 0.3, 0.3);
  rect->attribute.alpha = 10;
  rect->attribute.pd = Vector(0.8, 0.8, 0.8);
  rect->attribute.ps = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));
  
  
  Ball *ball = new Ball();
  ball->position = Vector(6, 2, 7);
  ball->radius = 2;
  ball->attribute.ks = Vector(0.8, 0.8, 0.8);
  ball->attribute.kd = Vector(0.9, 0.9, 0.9);
  ball->attribute.ka = Vector(0.1, 0.1, 0.1);
  ball->attribute.alpha = 50;
  ball->attribute.pd = Vector(0, 0, 0);
  ball->attribute.ps = Vector(0, 0, 0);
  ball->attribute.pt = Vector(1, 1, 1);
  ball->attribute.index = 1.7;
  scene.item.push_back(make_pair(BALL, ball));

  Attribute attr;
  attr.ks = Vector(0.1, 0.1, 0.1);
  attr.kd = Vector(0.8, 0.8, 0.8);
  attr.ka = Vector(0.2, 0.2, 0.2);
  attr.alpha = 10;
  attr.pd = Vector(1, 1, 1);
  insertBox(scene.item, Vector(2, 0, 2), Vector(3, 0, -2), Vector(0, 3, 0), Vector(2, 0, 3), attr);
  
  Light lit;
  lit.position = Vector(5, 10 - EPS, 5);
  lit.diffuse = Vector(0.04, 0.04, 0.04);
  lit.specular = Vector(0.04, 0.04, 0.04);
  for (int i = -2; i <= 2; i++)
    for (int j = -2; j <= 2; j++) {
      lit.position[0] += .1 * i;
      lit.position[2] += .1 * j;
      scene.light.push_back(lit);
      lit.position[0] -= .1 * i;
      lit.position[2] -= .1 * j;
    }
  scene.render();
  scene.save("out.png");
  return 0;
}
