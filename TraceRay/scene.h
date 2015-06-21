//
//  scene.h
//  TraceRay
//
//  Created by LazyLie on 15/6/18.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__scene__
#define __TraceRay__scene__

#include <stdio.h>
#include "core.h"
#include "camera.h"
#include <thread>
#include <mutex>

class Scene {
public:
  int MAX_DEP;
  int MC_NUM;
  std::vector< std::pair<char, void*> > item;
  Rect light;
  int lightSample;
  Vector ambLight;
  std::vector< std::vector<Vector> > image;
  Camera camera;
  Vector trace(const Ray &r, int dep);
  Vector mix(const Vector &a, const Vector &b);
  Ray getDiffuse(const CollideInfo &info, const Attribute &attr);
  std::pair<CollideInfo, Attribute> getCollide(const Ray &r);
  std::pair<char, Ray> mcSelect(const CollideInfo &info, const Attribute &attr, const Vector &self);
  void render();
  void save(std::string filename);
  void thread();
  std::mutex mtx;
  int px, py;
};

#endif /* defined(__TraceRay__scene__) */
