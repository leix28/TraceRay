//
//  scene.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "scene.h"
#include "opencv2/opencv.hpp"

Vector Scene::trace(Ray r, int dep) {
  Vector color;
  if (dep >= 3) return color;
  double t = INFD;
  Ray ref;
  Attribute attr;
  for (auto &m : model) {
    auto tmp = m.collision(r);
    if (tmp.first > 0 && tmp.first < t) {
      attr = m.attribute;
      t = tmp.first;
      ref = tmp.second;
    }
  }
  
  bool isLight = 0;
  Vector lightColor;
  for (auto &l : light) {
    auto tmp = l.collision(r);
    if (tmp.first > 0 && tmp.first < t) {
      isLight = 1;
      t = tmp.first;
      lightColor = l.attribute.diffuse;
    }
  }
  if (isLight) return lightColor;
  
  if (t > 0) {
    color = color + diffLight * attr.diffuse;
    color = color + trace(ref, dep + 1) * attr.specular;
  }
  return color;
}

void Scene::render() {
  trace(camera.getRay(250, 250), 0);
  image.clear();
  image.resize(camera.pixHeight, std::vector<Vector>(camera.pixWidth));
  for (int i = 0; i < camera.pixHeight; i++) {
    for (int j = 0; j < camera.pixWidth; j++) {
      Ray r = camera.getRay(i, j);
      image[i][j] = trace(r, 0);
    }
    printf("%d\n", i);
  }
}

void Scene::saveToFile(std::string filename) {
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