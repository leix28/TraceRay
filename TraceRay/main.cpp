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
  scene.MC_NUM = 50;

  scene.camera.position = Vector(5, 5, 20);
  scene.camera.filmCenter = Vector(5, 5, 10);
  scene.camera.pixHeight = 1000;
  scene.camera.pixWidth = 1000;
  scene.camera.filmHeight = Vector(0, -10, 0);
  scene.camera.filmWidth = Vector(10, 0, 0);
  scene.camera.aperture = 0.008;
  scene.camera.sample = 20;
  scene.camera.dis = 4;

  scene.MAX_DEP = 5;

  //ceil
  Rect *rect = new Rect();
  rect->position = Vector(0, 10, 0);
  rect->dx = Vector(10, 0, 0);
  rect->dy = Vector(0, 0, 10);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.95, 0.95, 0.8);
  rect->attribute.ka = Vector(0, 0, 0);
  rect->attribute.kt = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));

  //floor
  rect = new Rect();
  rect->position = Vector(0, 0, 0);
  rect->dx = Vector(0, 0, 10);
  rect->dy = Vector(10, 0, 0);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.95, 0.95, 0.8);
  rect->attribute.ka = Vector(0, 0, 0);
  rect->attribute.kt = Vector(0, 0, 0);
  rect->attribute.loadImg("floor.png");
  scene.item.push_back(make_pair(RECT, rect));

  //left
  rect = new Rect();
  rect->position = Vector(0, 0, 0);
  rect->dx = Vector(0, 10, 0);
  rect->dy = Vector(0, 0, 10);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.7, 0.15, 0.15);
  rect->attribute.ka = Vector(0, 0, 0);
  rect->attribute.kt = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));

  //right
  rect = new Rect();
  rect->position = Vector(10, 0, 0);
  rect->dx = Vector(0, 0, 10);
  rect->dy = Vector(0, 10, 0);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.4, 0.2, 0.6);
  rect->attribute.ka = Vector(0, 0, 0);
  rect->attribute.kt = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));

  //back
  rect = new Rect();
  rect->position = Vector(0, 0, 0);
  rect->dx = Vector(10, 0, 0);
  rect->dy = Vector(0, 10, 0);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.95, 0.95, 0.8);
  rect->attribute.ka = Vector(0, 0, 0);
  rect->attribute.kt = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));


  Ball *ball = new Ball();
  ball->position = Vector(7, 7.5, 7);
  ball->radius = 2;
  ball->attribute.ks = Vector(0, 0, 0);
  ball->attribute.kd = Vector(0, 0, 0);
  ball->attribute.ka = Vector(0, 0, 0);
  ball->attribute.kt = Vector(1, 1, 1);
  ball->attribute.index = 1.7;
  scene.item.push_back(make_pair(BALL, ball));

  ball = new Ball();
  ball->position = Vector(3, 5.5, 4);
  ball->radius = 1.5;
  ball->attribute.ks = Vector(0, 0, 0);
  ball->attribute.kd = Vector(1, 1, 1);
  ball->attribute.ka = Vector(0, 0, 0);
  ball->attribute.kt = Vector(0, 0, 0);
  ball->attribute.index = 1.7;
  ball->attribute.loadImg("maoxian.png");
  scene.item.push_back(make_pair(BALL, ball));


  Attribute attr;
  attr.ks = Vector(0.2, 0.2, 0.2);
  attr.kd = Vector(1, 1, 1);
  attr.ka = Vector(0, 0, 0);
  attr.kt = Vector(0, 0, 0);
  attr.loadImg("marble.png");
  insertBox(scene.item, Vector(1, 0, 4), Vector(2, 0, -2), Vector(0, 4, 0), Vector(2, 0, 2), attr);
  insertBox(scene.item, Vector(7, 0, 6), Vector(2, 0, 1), Vector(0, 3, 0), Vector(-1, 0, 2), attr);

  Rect lit;
  lit.position = Vector(3.5, 9.999, 3.5);
  lit.dx = Vector(3, 0, 0);
  lit.dy = Vector(0, 0, 3);
  lit.attribute.ka = Vector(1, 1, 1);
  lit.attribute.kd = Vector(0, 0, 0);
  lit.attribute.ks = Vector(0, 0, 0);
  lit.attribute.kt = Vector(0, 0, 0);
  scene.light = lit;
  scene.lightSample = 1;

  for (int i = 3; i < 8; i += 2) {
    scene.camera.dis = i;
    scene.render();
    std::string name = "0.png";
    name[0] = '0' + i;
    scene.save(name);
  }
  return 0;
}
