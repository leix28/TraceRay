//
//  scene.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/21.
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
    } else if (itm.first == OBJ) {
      Obj *obj = (Obj*)itm.second;
      tattr = obj->attribute;
      tmp = obj->collide(r);
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


std::pair<char, Ray> Scene::mcSelect(const Ray &r, const CollideInfo &info, const Attribute &attr) {
  double a[3];
  a[0] = attr.kd[channel];
  a[1] = attr.ks[channel] + a[0];
  a[2] = attr.kt[channel] + a[1];
  double rd = (double)rand() / RAND_MAX * a[2];
  if (rd < a[0]) {
    return make_pair('d', diffuse(r, r.position + r.direction * info.distance, info.normal));
  } else if (rd < a[1]) {
    return make_pair('r', reflect(r, r.position + r.direction * info.distance, info.normal));
  } else {
    return make_pair('t', transparent(r, r.position + r.direction * info.distance, info.normal, info.index));
  }
}

double Scene::getDiffuse(const Ray &r, const CollideInfo &info, const Attribute &attr) {
  if (r.inside) return 0;
  double color = 0;
  double rate = 1.0 / lightSample;
  for (int i = 0; i < lightSample; i++) {
    double dx = (double)rand() / RAND_MAX;
    double dy = (double)rand() / RAND_MAX;
    Vector p = (light.position + dx * light.dx + dy * light.dy);
    Ray t;
    t.inside = 0;
    t.position = r.position + info.distance * r.direction;
    t.direction = p - t.position;
    t.direction = t.direction / norm(t.direction);
    Vector dlt = p - t.position;

    double d = getCollide(t).first.distance;
    if (d < 0 || d > norm(dlt)) {
      double ang = innerProduct(dlt / norm(dlt), info.normal);
      if (ang > 0)
        color += light.attribute.ka[channel] * rate * ang;
    }
  }
  return color;
}

double Scene::trace(const Ray &r, int dep, double ef) {
  CollideInfo info;
  Attribute attr;
  auto tmp = getCollide(r);

  info = tmp.first;
  attr = tmp.second;

  double lit = light.collide(r).distance;
  if (lit > 0 && lit < info.distance) {
    return light.attribute.ka[channel];
  }

  if (info.distance > 0) {
    double self = 1;
    if (attr.hasimg) self = (*attr.img)[info.x][info.y][channel];
    double color = self * attr.ka[channel];
    double rate = attr.kd[channel] + attr.ks[channel] + attr.kt[channel];
    if (dep >= 2 * MAX_DEP || rate * self * ef < EPS_LOOSE) return color;
    auto tt = mcSelect(r, info, attr);
    if (tt.first == 'd') {
      if (dep >= MAX_DEP) return color + self * rate * getDiffuse(r, info, attr);
      color += self * rate * max(getDiffuse(r, info, attr), trace(tt.second, dep + 1, self * rate * ef));
    } else {
      color += self * rate * trace(tt.second, dep + 1, self * rate * ef);
    }
    return color;
  }
  return 0;
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
      printf("%d %d\n", channel, px);
    }
    mtx.unlock();
    auto rv = camera.getRay(x, y);
    for (const auto &r : rv) {
      double tot = 0;
      int cnt = 0;
      int flag = 0;
      for (int i = 0; i < MC_NUM; i++) {
        double bef = cnt ? tot / cnt : -1;
        double now = trace(r, 0, 1);
        tot += now;
        cnt++;
        if (fabs(now - bef) < EPS_LOOSE) {
          flag++;
          if (flag == 2) break;
        } else
          flag = 0;
      }
      image[x][y][channel] += tot / cnt;
    }
    image[x][y][channel] = image[x][y][channel] / rv.size();
  }
}

void Scene::render() {
  image.clear();
  image.resize(camera.pixHeight, std::vector<Vector>(camera.pixWidth));

  std::thread *pool = new std::thread[THREAD_NUM];
  for (int c = 0; c < 3; c++) {
    px = 0;
    py = 0;
    channel = c;
    for (int i = 0; i < THREAD_NUM; i++) {
      pool[i] = std::thread(std::bind(&Scene::thread, this));
    }
    for (int i = 0; i < THREAD_NUM; i++) {
      pool[i].join();
    }
  }
  delete[] pool;
}
