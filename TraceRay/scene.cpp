//
//  scene.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "scene.h"
#include "opencv2/opencv.hpp"

void Scene::saveToFile(std::string filename) {
  assert(image.size() && image[0].size());
  
  int h = (int)image.size();
  int w = (int)image[0].size();
  
  cv::Mat out(h, w, CV_64FC3);
  
  for (auto i = 0; i < h; i++)
    for (auto j = 0; j < w; j++) {
      out.at<double>(i * w * 3 + j * 3) = image[i][j][2];
      out.at<double>(i * w * 3 + j * 3 + 1) = image[i][j][1];
      out.at<double>(i * w * 3 + j * 3 + 2) = image[i][j][0];
    }
  
  imwrite(filename.c_str(), out);
}