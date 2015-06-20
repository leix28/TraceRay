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

Ray Scene::getDiffuse(const CollideInfo &info, const Attribute &attr) {
  double t = sqrt((double)rand() / RAND_MAX);
  Vector v;
  v[2] = t;
  v[0] = (double)rand() / RAND_MAX;
  v[1] = sqrt(1 - v[0] * v[0]);
  v[0] *= sqrt(1 - v[2] * v[2]);
  v[1] *= sqrt(1 - v[2] * v[2]);
  double theta = acos(info.normal[2]);
  double t1 = cos(theta) * v[1] + sin(theta) * v[2];
  double t2 = -sin(theta) * v[1] + cos(theta) * v[2];
  v[1] = t1; v[2] = t2;
  
  if (-EPS < info.normal[1] && info.normal[1] < EPS) {
    if (info.normal[0] >= 0)
      theta = PI / 2;
    else
      theta = -PI / 2;
  } else {
    theta = atan(info.normal[0] / info.normal[1]);
    if (info.normal[1] < 0) theta += PI;
  }
  
  double t0 = cos(theta) * v[0] + sin(theta) * v[1];
  t1 = -sin(theta) * v[0] + cos(theta) * v[1];
  v[0] = t0;
  v[1] = t1;
  
  Ray r;
  r.direction = v;
  assert(fabs(norm(v) - 1) < EPS);
  assert(innerProduct(r.direction, info.normal) >= 0);
  r.position = info.reflect.position;
  return r;
}

std::pair<char, Ray> Scene::mcSelect(const CollideInfo &info, const Attribute &attr) {
  double a[3];
  a[0] = sum(attr.kd);
  a[1] = a[0] + (info.reflectValid ? sum(attr.ks) : 0);
  a[2] = a[1] + (info.transparentValid ? sum(attr.kt) : 0);
  double t = (double)rand() / RAND_MAX * a[2];
  if (t < a[0]) {
    return make_pair('d', getDiffuse(info, attr));
  } else if (t < a[1]) {
    return make_pair('s', info.reflect);
  } else if (t < a[2]) {
    return make_pair('t', info.transparent);
  }
  assert(0);
}

Vector Scene::mix(const Vector &a, const Vector &b) {
  Vector c;
  c = a * b;
  if (sum(c) > EPS)
    c = c / sum(c) * sum(a);
  return c;
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

  Vector self(1, 1, 1);
  if (attr.hasimg) {
    self = (*attr.img)[info.x][info.y];
  }

  
  Vector color = attr.ka * ambLight * self;
  Vector tot = attr.kd;
  if (info.reflectValid) tot = tot + attr.ks;
  if (info.transparentValid) tot = tot + attr.kt;
  if (sum(tot) < EPS) return color;
  double rate = sum(tot) / (3 - sum(attr.ka));
  
  auto tt = mcSelect(info, attr);

  Vector c = trace(tt.second, dep + 1);

  if (tt.first == 'd') {
    color = color + rate * mix(c, attr.kd * self);
  } else if (tt.first == 's') {
    color = color + rate * mix(c, attr.ks * self);
  } else if (tt.first == 't') {
    color = color + rate * mix(c, attr.kt * self);
  }
  return color;
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
      for (int i = 0; i < MC_NUM; i++) {
        image[x][y] = image[x][y] + trace(r, 0);
      }
    }
    image[x][y] = image[x][y] / rv.size() / MC_NUM;
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