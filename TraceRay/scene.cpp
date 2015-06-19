//
//  scene.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/18.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "scene.h"
#include "opencv2/opencv.hpp"

void Scene::save(std::string filename) {
  assert(image.size() && image[0].size());
  
  int h = (int)image.size();
  int w = (int)image[0].size();
  
  cv::Mat out(h, w, CV_64FC3);
  
  for (auto i = 0; i < h; i++)
    for (auto j = 0; j < w; j++) {
      out.at<double>(i * w * 3 + j * 3) = image[i][j][2] * 256;
      out.at<double>(i * w * 3 + j * 3 + 1) = image[i][j][1] * 256;
      out.at<double>(i * w * 3 + j * 3 + 2) = image[i][j][0] * 256;
    }
  
  imwrite(filename.c_str(), out);
}

std::pair<CollideInfo, Attribute> Scene::getCollide(const Ray &r) {
  CollideInfo info;
  Attribute attr;
  info.distance = INFD;
  info.reflectValid = info.transparentValid = 0;
  for (const auto &itm : item) {
    CollideInfo tmp;
    Attribute tattr;
    if (itm.first == BALL) {
      Ball *ball = (Ball*)itm.second;
      tattr = ball->attribute;
      tmp = ball->collide(r);
    } else if (itm.first == RECT) {
      Rect *rect = (Rect*)itm.second;
      tattr = rect->attribute;
      tmp = rect->collide(r);
    } else {
      assert(0);
    }
    if (tmp.distance > 0 && tmp.distance < info.distance) {
      info = tmp;
      attr = tattr;
    }
  }
  if (info.distance == INFD) info.distance = -1;
  return make_pair(info, attr);
}

Vector Scene::getPhongColor(const Ray &r, const CollideInfo &info, const Attribute &attr) {
  Vector color;
  Vector self = Vector(1, 1, 1);
  if (attr.hasimg) {
    self = (*attr.img)[info.x][info.y];
  }
  if (info.distance > 0) {
    color = attr.ka * ambLight * self;
    double rate = 1.0 / (lightSample + 1) / (lightSample + 1);
    for (int i = 0; i <= lightSample; i++)
      for (int j = 0; j <= lightSample; j++) {
        Vector p = light.ptr + ((double)i / lightSample * light.x) + ((double)j / lightSample * light.y) ;
        Vector lm = p - info.reflect.position;
        double dis = norm(lm);
        if (dis < EPS) continue;
        lm = lm / norm(lm);
        
        Ray lt;
        lt.position = info.reflect.position;
        lt.direction = lm;
        lt.inside = info.reflect.inside;
        double sha = getCollide(lt).first.distance;
        if (sha > 0 && sha < dis) continue;
        
        double t = innerProduct(lm, info.normal);
        if (t > 0)
          color = color + rate * t * attr.kd * light.attribute.kd * self;
        t = innerProduct(-r.direction, reflect(-lm, info.normal));
        if (t > 0)
          color = color + rate * pow(t, attr.alpha) * attr.ks * light.attribute.ks;
      }
  }
  return color;
}

Vector Scene::trace(const Ray &r, int dep) {
  if (dep > MAX_DEP)
    return Vector();
  CollideInfo info;
  Attribute attr;
  auto tmp = getCollide(r);
  
  info = tmp.first;
  attr = tmp.second;
  
  double lit = light.collide(r).distance;
  if (lit > 0 && (lit <= info.distance || info.distance < 0)) {
    if (dep == 0)
      return light.attribute.ks;
    else
      return light.attribute.kd;
  }
  
  Vector color;
  color = attr.pd * getPhongColor(r, info, attr);

  if (info.reflectValid)
    color = color + attr.ps * trace(info.reflect, dep + 1);
  
  if (info.transparentValid)
    color = color + attr.pt * trace(info.transparent, dep + 1);
  
  return scale(color);
}

void Scene::thread() {
  while (1) {
    mtx.lock();
    int x = px;
    int y = py;
    if (x == camera.pixHeight) {
      mtx.unlock();
      return;
    }
    py++;
    if (py == camera.pixWidth) {
      px++;
      py = 0;
      printf("%d\n", px);
    }
    mtx.unlock();
    auto rv = camera.getRay(x, y);
    for (const auto &r : rv) {
      image[x][y] = image[x][y] + trace(r, 0);
    }
    image[x][y] = image[x][y] / rv.size();
  }
}

void Scene::render() {
  image.clear();
  image.resize(camera.pixHeight, std::vector<Vector>(camera.pixWidth));
  
  px = 0;
  py = 0;
  
  std::thread *pool = new std::thread[THREAD_NUM];
  for (int i = 0; i < THREAD_NUM; i++) {
    pool[i] = std::thread(std::bind(&Scene::thread, this));
  }
  for (int i = 0; i < THREAD_NUM; i++) {
    pool[i].join();
  }
  
  delete[] pool;
}