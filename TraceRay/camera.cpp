//
//  camera.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "camera.h"

Camera::Camera() {
    setPosition(fvector3D(-1, 0, 0));
    setFilm(fvector3D(0, 0, 0), fvector3D(0, 1, 0), fvector3D(0, 0, 1));
    setResolution(0.01);
}

Camera::Camera(const fvector3D &pos, const fvector3D &c, const fvector3D &h, const fvector3D &w, const double r) {
    setPosition(pos);
    setFilm(c, h, w);
    setResolution(r);
}

fvector3D Camera::getPosition() const {
    return position;
}

fvector3D Camera::getFilmCenter() const {
    return center;
}

fvector3D Camera::getFilmHeight() const {
    return height;
}

fvector3D Camera::getFilmWidth() const {
    return width;
}

std::pair<int, int> Camera::getResolution() const {
    return pixel;
}

void Camera::setPosition(const fvector3D &p) {
    position = p;
}

void Camera::setFilm(const fvector3D &c, const fvector3D &h, const fvector3D &w) {
    assert(fabs(w.dotProduct(h)) < EPS);
    center = c;
    width = w;
    height = h;
}

void Camera::setResolution(const double r) {
    resolution = r;
    pixel.first = height.length() / resolution;
    pixel.second = width.length() / resolution;
    assert(pixel.first > 0 && pixel.second > 0);
}

Ray Camera::getRay(int x, int y) const {
    assert(0 <= x && x < pixel.first && 0 <= y && y < pixel.second);
    
    fvector3D dh = height.multiply((double)x / pixel.first).subtract(height.multiply(0.5));
    fvector3D dw = width.multiply((double)y / pixel.second).subtract(width.multiply(0.5));
    fvector3D p = center.add(dh).add(dw);
    return Ray(getPosition(), p.subtract(getPosition()));
}