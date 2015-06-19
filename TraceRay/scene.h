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

class Scene {
public:
  int MAX_DEP;
  std::vector< std::pair<char, void*> > item;
  std::vector<Light> light;
  Vector ambLight;
  std::vector< std::vector<Vector> > image;
  Camera camera;
  Vector trace(const Ray &r, int dep);
  std::pair<CollideInfo, Attribute> getCollide(const Ray &r);
  Vector getPhongColor(const Ray &r, const CollideInfo &info, const Attribute &attr);
  void render();
  void save(std::string filename);
  void thread();
  std::mutex mtx;
  int px, py;
};

#endif /* defined(__TraceRay__scene__) */
