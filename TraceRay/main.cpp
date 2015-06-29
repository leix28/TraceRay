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
  scene.MC_NUM = 100;

  scene.camera.position = Vector(5, 5, 20);
  scene.camera.filmCenter = Vector(5, 5, 10);
  scene.camera.pixHeight = 1000;
  scene.camera.pixWidth = 1000;
  scene.camera.filmHeight = Vector(0, -10, 0);
  scene.camera.filmWidth = Vector(10, 0, 0);
  scene.camera.aperture = 0.001;
  scene.camera.sample = 10;
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


  Obj *obj = new Obj();
  obj->load("bunny.obj", Vector(0.2, -0.02, 0.2), 30);
  obj->attribute.kt = Vector(0.9, 0.7, 0.2);
  scene.item.push_back(make_pair(OBJ, obj));

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

  scene.render();
  scene.save("out.png");

  return 0;
}
