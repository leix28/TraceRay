//
//  core.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/21.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "core.h"
#include "opencv2/opencv.hpp"
const char RECT = 'r';
const char BALL = 'b';
const char OBJ = 'o';
const int KDT_DEP = 14;
const int BUFSIZE = 100;

Ray::Ray() {inside = 0; }
Attribute::Attribute() {index = 1; }

void Attribute::loadImg(std::string filename) {
  hasimg = 1;
  img = new std::vector< std::vector<Vector> >();
  img->clear();
  auto tmp = cv::imread(filename);
  img->resize(tmp.rows, std::vector<Vector>(tmp.cols));
  for (int i = 0; i < tmp.rows; i++)
    for (int j = 0; j < tmp.cols; j++) {
      (*img)[i][j][0] = tmp.at<uint8_t>(i * tmp.cols * 3 + j * 3 + 2) / 256.0;
      (*img)[i][j][1] = tmp.at<uint8_t>(i * tmp.cols * 3 + j * 3 + 1) / 256.0;
      (*img)[i][j][2] = tmp.at<uint8_t>(i * tmp.cols * 3 + j * 3 + 0) / 256.0;
    }
}

std::pair<int, int> Ball::getXY(Vector p, const Vector &normal) {
  p = p - position;
  std::pair<int, int> ret;
  int h = (int)(*attribute.img).size();
  int w = (int)(*attribute.img)[0].size();
  if (fabs(p.x) >= fabs(p.y) && fabs(p.x) >= fabs(p.z)) {
    p = p * (radius / p.x);
    ret.first = p.y / radius / 2 * h;
    ret.second = p.z / radius / 2 * w;
  } else if (fabs(p.y) > fabs(p.x) && fabs(p.y) >= fabs(p.z)) {
    p = p * (radius / p.y);
    ret.first = p.x / radius / 2 * w;
    ret.second = p.z / radius / 2 * h;
  } else {
    p = p * (radius / p.z);
    ret.first = p.x / radius / 2 * h;
    ret.second = p.y / radius / 2 * w;
  }
  ret.first = (ret.first % h + h + h / 2) % h;
  ret.second = (ret.second % w + w + w / 2) % w;
  return ret;
}

CollideInfo Ball::collide(const Ray &r) {
  CollideInfo info;
  info.distance = -1;
  Vector v = r.position - position;

  if (r.inside) {
    if (norm(r.position - position) > radius + EPS) return info;
    double tmp = sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius);
    assert(tmp >= -EPS);
    if (tmp < 0) tmp = 0;
    info.distance = -innerProduct(r.direction, v) + sqrt(tmp);
    assert(info.distance >= -EPS);
    if (info.distance < 0) info.distance = 0;
    info.normal = position - (r.position + info.distance * r.direction);
    info.normal = info.normal / norm(info.normal);
    info.index = 1.0 / attribute.index;
    if (attribute.hasimg) {
      auto tmp = getXY(r.position + info.distance * r.direction, -info.normal);
      info.x = tmp.first;
      info.y = tmp.second;
    }
    return info;
  } else {
    if (innerProduct(v, r.direction) > 0) return info;

    if (sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius) < 0) return info;
    info.distance = -innerProduct(r.direction, v) - sqrt(sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius));
    info.normal = r.position + info.distance * r.direction - position;
    info.normal = info.normal / norm(info.normal);
    info.index = attribute.index;
    if (attribute.hasimg) {
      auto tmp = getXY(r.position + info.distance * r.direction, info.normal);
      info.x = tmp.first;
      info.y = tmp.second;
    }
    return info;
  }
}

CollideInfo Rect::collide(const Ray &r) {
  CollideInfo info;
  info.distance = -1;

  Vector v = position - r.position;
  Vector n = crossProduct(dx, dy);
  n = n / norm(n);

  if (r.inside) n = -n;

  if (innerProduct(n, r.direction) >= 0) return info;

  info.distance = innerProduct(n, v) / innerProduct(r.direction, n);
  if (info.distance < EPS) {
    info.distance = -1;
    return info;
  }

  Vector p = r.position + info.distance * r.direction;

  double lx = norm(dx);
  double ly = norm(dy);
  double ax = innerProduct(p - position, dx / lx);
  double ay = innerProduct(p - position, dy / ly);
  if (ax < 0 || ax > lx || ay < 0 || ay > ly) {
    info.distance = -1;
    return info;
  }
  info.normal = n;
  info.index = r.inside ? (1.0 / attribute.index) : attribute.index;
  if (attribute.hasimg) {
    info.x = ax / 0.01;
    info.y = ay / 0.01;
    info.x %= (*attribute.img).size();
    info.y %= (*attribute.img)[0].size();
  }
  return info;
}

CollideInfo Tri::collide(const Ray &r) {
  CollideInfo info;
  info.distance = -1;

  Vector n = crossProduct(dx, dy);
  n = n / norm(n);

  if (r.inside) n = -n;

  if (innerProduct(n, r.direction) >= 0) return info;

  Vector e1 = -dx, e2 = -dy, s = position - r.position;
  if (r.inside) {
    e1 = -dy;
    e2 = -dx;
  }
  Vector v = Vector(det(s, e1, e2), det(r.direction, s, e2), det(r.direction, e1, s));
  v = v / det(r.direction, e1, e2);

  if (v.x > EPS && 0 <= v.y && v.y <= 1 && 0 <= v.z && v.z <= 1 && v.y + v.z <= 1) {
    info.distance = v.x;
    info.normal = n;
    return info;
  } else {
    info.distance = -1;
    return info;
  }
}

void Obj::insert(int id, const Tri &t, int dep, Vector mn, Vector mx) {
  if (dep == KDT_DEP - 1) {
    tri[id].push_back(t);
    return;
  }
  int channel = dep % 3;
  double mid = (mn[channel] + mx[channel]) / 2;
  if (t.mn[channel] < mid) {
    double bak = mx[channel];
    mx[channel] = mid;
    insert(id * 2, t, dep + 1, mn, mx);
    mx[channel] = bak;
  }
  if (t.mx[channel] > mid) {
    double bak = mn[channel];
    mn[channel] = mid;
    insert(id * 2 + 1, t, dep + 1, mn, mx);
    mn[channel] = bak;
  }
}

void Obj::load(std::string filename, const Vector &move, double scale) {
  tri = new std::vector<Tri>[1 << KDT_DEP];
  char buffer[BUFSIZE];
  FILE *file = fopen(filename.c_str(), "r");
  std::vector<std::string> vertexIn;
  std::vector<std::string> faceIn;
  while (fgets(buffer, BUFSIZE, file) != NULL) {
    int ptr = 0;
    while (buffer[ptr] != 0 && buffer[ptr] != 'v' && buffer[ptr] != 'f' && buffer[ptr] != '#') ptr++;
    if (buffer[ptr] == 'v') vertexIn.push_back(std::string(buffer));
    if (buffer[ptr] == 'f') faceIn.push_back(std::string(buffer));
  }
  fclose(file);

  int vertexN = (int)vertexIn.size();
  std::vector<Vector> vertex(vertexN);

  mn = Vector(INFD, INFD, INFD);
  mx = Vector(-INFD, -INFD, -INFD);
  for (int i = 0; i < vertexN; i++) {
    sscanf(vertexIn[i].c_str(), "%*s%lf%lf%lf", &vertex[i][0], &vertex[i][1], &vertex[i][2]);
    vertex[i] = (vertex[i] + move) * scale;
    for (int j = 0; j < 3; j++) {
      mn[j] = fmin(mn[j], vertex[i][j]);
      mx[j] = fmax(mx[j], vertex[i][j]);
    }
  }
  for (auto s : faceIn) {
    int x, y, z;
    Tri t;
    sscanf(s.c_str(), "%*s%d%d%d", &x, &y, &z);
    x--; y--; z--;
    t.position = vertex[x];
    t.dx = vertex[y] - vertex[x];
    t.dy = vertex[z] - vertex[x];
    for (int i = 0; i < 3; i++) {
      t.mn[i] = fmin(fmin(vertex[x][i], vertex[y][i]), vertex[z][i]);
      t.mx[i] = fmax(fmax(vertex[x][i], vertex[y][i]), vertex[z][i]);
    }
    insert(1, t, 0, mn, mx);
  }
}

bool Obj::hitbox(Vector mn, Vector mx, const Ray &r) {
  for (int i = 0; i < 3; i++) {
    double t = (mn[i] - r.position[i]) / r.direction[i];
    if (t < 0) continue;
    Vector p = r.position + r.direction * t;
    if (mn.x - EPS <= p.x && p.x <= mx.x + EPS && mn.y - EPS <= p.y && p.y <= mx.y + EPS && mn.z - EPS <= p.z && p.z <= mx.z + EPS) return 1;
  }
  for (int i = 0; i < 3; i++) {
    double t = (mx[i] - r.position[i]) / r.direction[i];
    if (t < 0) continue;
    Vector p = r.position + r.direction * t;
    if (mn.x - EPS <= p.x && p.x <= mx.x + EPS && mn.y - EPS <= p.y && p.y <= mx.y + EPS && mn.z - EPS <= p.z && p.z <= mx.z + EPS) return 1;
  }
  return 0;
}

CollideInfo Obj::search(int id, const Ray &r, int dep, Vector mn, Vector mx) {
  if (!hitbox(mn, mx, r)) return CollideInfo();
  int channel = dep % 3;
  if (dep == KDT_DEP - 1) {
    CollideInfo info;
    for (auto &t : tri[id]) {
      auto tmp = t.collide(r);
      if (tmp.distance > 0 && (tmp.distance < info.distance || info.distance < 0))
        info = tmp;
    }
    return info;
  } else {
    double mid = (mn[channel] + mx[channel]) / 2;
    double bak;
    if (r.position[channel] < mid) {
      bak = mx[channel];
      mx[channel] = mid;
      auto info = search(id * 2, r, dep + 1, mn, mx);
      mx[channel] = bak;
      if (info.distance > 0) return info;
      bak = mn[channel];
      mn[channel] = mid;
      return search(id * 2 + 1, r, dep + 1, mn, mx);
    } else {
      bak = mn[channel];
      mn[channel] = mid;
      auto info = search(id * 2 + 1, r, dep + 1, mn, mx);
      mn[channel] = bak;
      if (info.distance > 0) return info;
      bak = mx[channel];
      mx[channel] = mid;
      return search(id * 2, r, dep + 1, mn, mx);
    }
  }
}

CollideInfo Obj::collide(const Ray &r) {
  auto tmp = search(1, r, 0, mn, mx);
  tmp.index = attribute.index;
  if (r.inside) tmp.index = 1 / tmp.index;
  return tmp;
}

Ray reflect(const Ray &in, const Vector &position, const Vector &normal) {
  Ray ref;
  ref.inside = in.inside;
  ref.position = position;
  ref.direction = in.direction - 2 * innerProduct(in.direction, normal) * normal;
  return ref;
}

Ray transparent(const Ray &in, const Vector &position, const Vector &normal, const double index) {
  Ray tra;
  double cosTheta = 1 - (1 - sqr(innerProduct(in.direction, normal))) / sqr(index);
  if (cosTheta >= 0 && cosTheta <= 1) {
    cosTheta = sqrt(cosTheta);
    tra.position = position;
    tra.direction = 1 / index * in.direction - (1 / index * innerProduct(in.direction, normal) + cosTheta) * normal;
    tra.direction = tra.direction / norm(tra.direction);
    tra.inside = !in.inside;
    return tra;
  } else {
    return reflect(in, position, normal);
  }
}

Ray diffuse(const Ray &in, const Vector &position, const Vector &normal) {
  Ray dif;
  dif.position = position;
  dif.direction.x = (double)rand() / RAND_MAX * 2 - 1;
  dif.direction.y = (double)rand() / RAND_MAX * 2 - 1;
  dif.direction.z = (double)rand() / RAND_MAX * 2 - 1;
  while (norm(dif.direction) < EPS || norm(dif.direction) > 1 || innerProduct(dif.direction, normal) < 0) {
    dif.direction.x = (double)rand() / RAND_MAX * 2 - 1;
    dif.direction.y = (double)rand() / RAND_MAX * 2 - 1;
    dif.direction.z = (double)rand() / RAND_MAX * 2 - 1;
  }
  dif.direction = dif.direction / norm(dif.direction);
  dif.inside = in.inside;
  return dif;
}

void insertBox(std::vector< std::pair<char, void*> > &item, const Vector &p, const Vector &x, const Vector &y, const Vector &z, const Attribute &attr) {
  Rect *rect = new Rect();
  rect->attribute = attr;
  rect->position = p;
  rect->dx = y;
  rect->dy = x;
  item.push_back(make_pair(RECT, rect));

  rect = new Rect();
  rect->attribute = attr;
  rect->position = p;
  rect->dx = x;
  rect->dy = z;
  item.push_back(make_pair(RECT, rect));

  rect = new Rect();
  rect->attribute = attr;
  rect->position = p;
  rect->dx = z;
  rect->dy = y;
  item.push_back(make_pair(RECT, rect));

  Vector pp = p + x + y + z;
  rect = new Rect();
  rect->attribute = attr;
  rect->position = pp;
  rect->dx = -x;
  rect->dy = -y;
  item.push_back(make_pair(RECT, rect));

  rect = new Rect();
  rect->attribute = attr;
  rect->position = pp;
  rect->dx = -z;
  rect->dy = -x;
  item.push_back(make_pair(RECT, rect));

  rect = new Rect();
  rect->attribute = attr;
  rect->position = pp;
  rect->dx = -y;
  rect->dy = -z;
  item.push_back(make_pair(RECT, rect));

}
