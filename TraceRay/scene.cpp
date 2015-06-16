//
//  scene.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "scene.h"
#include "opencv2/opencv.hpp"

Vector Scene::trace(Ray r) {
  Vector color;
  for (auto &m : model) {
    double t = m.collision(r);
    if (t > 0) color = color + diffLight;
  }
  return color;
}

void Scene::render() {
  image.clear();
  image.resize(camera.pixHeight, std::vector<Vector>(camera.pixWidth));
  for (int i = 0; i < camera.pixHeight; i++)
    for (int j = 0; j < camera.pixWidth; j++) {
      Ray r = camera.getRay(i, j);
      image[i][j] = trace(r);
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