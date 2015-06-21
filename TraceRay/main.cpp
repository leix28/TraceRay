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
  scene.MC_NUM = 1000;
  
  scene.camera.position = Vector(5, 5, 20);
  scene.camera.filmCenter = Vector(5, 5, 10);
  scene.camera.pixHeight = 1000;
  scene.camera.pixWidth = 1000;
  scene.camera.filmHeight = Vector(0, -10, 0);
  scene.camera.filmWidth = Vector(10, 0, 0);
  scene.camera.aperture = 0.001;
  scene.camera.sample = 0;
  scene.camera.dis = 4;

  scene.ambLight = Vector(1, 1, 1);
  scene.MAX_DEP = 15;

  //ceil
  Rect *rect = new Rect();
  rect->ptr = Vector(0, 10, 0);
  rect->x = Vector(10, 0, 0);
  rect->y = Vector(0, 0, 10);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.3, 0.3, 0.3);
  rect->attribute.ka = Vector(0.3, 0.3, 0.3);
  rect->attribute.kt = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));

  //floor
  rect = new Rect();
  rect->ptr = Vector(0, 0, 0);
  rect->x = Vector(0, 0, 10);
  rect->y = Vector(10, 0, 0);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.3, 0.3, 0.3);
  rect->attribute.ka = Vector(0.3, 0.3, 0.3);
  rect->attribute.kt = Vector(0, 0, 0);
  rect->attribute.loadImg("floor.png");
  scene.item.push_back(make_pair(RECT, rect));

  //left
  rect = new Rect();
  rect->ptr = Vector(0, 0, 0);
  rect->x = Vector(0, 10, 0);
  rect->y = Vector(0, 0, 10);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.3, 0, 0);
  rect->attribute.ka = Vector(0.3, 0, 0);
  rect->attribute.kt = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));

  //right
  rect = new Rect();
  rect->ptr = Vector(10, 0, 0);
  rect->x = Vector(0, 0, 10);
  rect->y = Vector(0, 10, 0);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0, 0, 0.3);
  rect->attribute.ka = Vector(0, 0, 0.3);
  rect->attribute.kt = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));

  //back
  rect = new Rect();
  rect->ptr = Vector(0, 0, 0);
  rect->x = Vector(10, 0, 0);
  rect->y = Vector(0, 10, 0);
  rect->attribute.ks = Vector(0, 0, 0);
  rect->attribute.kd = Vector(0.3, 0.3, 0.3);
  rect->attribute.ka = Vector(0.3, 0.3, 0.3);
  rect->attribute.kt = Vector(0, 0, 0);
  scene.item.push_back(make_pair(RECT, rect));


  Ball *ball = new Ball();
  ball->position = Vector(6, 7, 7);
  ball->radius = 1.8;
  ball->attribute.ks = Vector(0.2, 0.2, 0.2);
  ball->attribute.kd = Vector(0, 0, 0);
  ball->attribute.ka = Vector(0, 0, 0);
  ball->attribute.kt = Vector(0.8, 0.8, 0.8);
  ball->attribute.index = 1.7;
  scene.item.push_back(make_pair(BALL, ball));

  Attribute attr;
  attr.ks = Vector(0, 0, 0);
  attr.kd = Vector(0.4, 0.4, 0.4);
  attr.ka = Vector(0.4, 0.4, 0.4);
  attr.kt = Vector(0, 0, 0);
  attr.loadImg("marble.png");
  insertBox(scene.item, Vector(1, 0, 4), Vector(2, 0, -2), Vector(0, 6, 0), Vector(2, 0, 2), attr);
  insertBox(scene.item, Vector(5, 0, 7), Vector(2, 0, 0), Vector(0, 3, 0), Vector(0, 0, 2), attr);

  Rect lit;
  lit.ptr = Vector(4, 9.99, 4);
  lit.x = Vector(2, 0, 0);
  lit.y = Vector(0, 0, 2);
  lit.attribute.kd = Vector(1, 1, 1);
  lit.attribute.ks = Vector(1, 1, 1);
  scene.light = lit;
  scene.lightSample = 2;

  scene.render();
  scene.save("out.png");
  return 0;
}
