//
//  scene.h
//  TraceRay
//
//  Created by LazyLie on 15/6/21.
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
  int channel;
  std::vector< std::pair<char, void*> > item;
  std::vector< std::vector<Vector> > image;
  Camera camera;
  Rect light;
  int lightSample;
  
  double trace(const Ray &r, int dep, double ef);
  std::pair<CollideInfo, Attribute> getCollide(const Ray &r);
  std::pair<char, Ray> mcSelect(const Ray &r, const CollideInfo &info, const Attribute &attr);
  double getDiffuse(const Ray &r, const CollideInfo &info, const Attribute &attr);
  void render();
  void save(std::string filename);
  void thread();
  std::mutex mtx;
  int px, py;
};

#endif /* defined(__TraceRay__scene__) */
