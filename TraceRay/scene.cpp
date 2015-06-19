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
  if (info.distance != -1) {
    color = attr.ka * ambLight;
    for (const auto &lit : light) {
      Vector lm = lit.position - info.reflect.position;
      double dis = norm(lm);
      lm = lm / norm(lm);
      
      Ray lt;
      lt.position = info.reflect.position;
      lt.direction = lm;
      double sha = getCollide(lt).first.distance;
      if (sha > 0 && sha < dis) continue;
      
      double t = innerProduct(lm, info.normal);
      if (t > 0)
        color = color + t * attr.kd * lit.diffuse;
      t = innerProduct(-r.direction, reflect(-lm, info.normal));
      if (t > 0)
        color = color + pow(t, attr.alpha) * attr.ks * lit.specular;
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
  
  Vector color = attr.pd * getPhongColor(r, info, attr);

  if (info.reflectValid)
    color = color + attr.ps * trace(info.reflect, dep + 1);
  
  return scale(color);
}

void Scene::render() {
  image.clear();
  image.resize(camera.pixHeight, std::vector<Vector>(camera.pixWidth));
  for (int i = 0; i < camera.pixHeight; i++)
    for (int j = 0; j < camera.pixWidth; j++)
      image[i][j] = trace(camera.getRay(i, j), 0);
}