//
//  foundation.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/10.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "foundation.h"
#include <cassert>
#include <cmath>

fvector3D::fvector3D() {
    v[0] = v[1] = v[2] = 0;
}

fvector3D::fvector3D(double _v[3]) {
    v[0] = _v[0]; v[1] = _v[1]; v[2] = _v[2];
}

fvector3D::fvector3D(double _x, double _y, double _z) {
    v[0] = _x; v[1] = _y; v[2] = _z;
}

double fvector3D::get(const int index) const {
    assert(0 <= index && index < 3);
    return v[index];
}

void fvector3D::set(const int index, const double value) {
    assert(0 <= index && index < 3);
    v[index] = value;
}

double fvector3D::length() const {
    return sqrt(this->dotProduct(*this));
}


fvector3D fvector3D::add(const fvector3D &y) const {
    fvector3D z;
    z.set(0, get(0) + y.get(0));
    z.set(1, get(1) + y.get(1));
    z.set(2, get(2) + y.get(2));
    return z;
}

fvector3D fvector3D::subtract(const fvector3D &y) const {
    fvector3D z;
    z.set(0, get(0) - y.get(0));
    z.set(1, get(1) - y.get(1));
    z.set(2, get(2) - y.get(2));
    return z;
}

fvector3D fvector3D::multiply(const double y) const {
    fvector3D z;
    z.set(0, get(0) * y);
    z.set(1, get(1) * y);
    z.set(2, get(2) * y);
    return z;
}

double fvector3D::dotProduct(const fvector3D &y) const {
    double z = 0;
    z += get(0) * y.get(0) + get(1) * y.get(1) + get(2) + y.get(2);
    return z;
}

fvector3D fvector3D::crossProduct(const fvector3D &y) const {
    fvector3D z;
    z.set(0, get(1) * y.get(2) - get(2) - y.get(1));
    z.set(1, get(2) * y.get(0) - get(0) - y.get(2));
    z.set(2, get(0) * y.get(1) - get(1) - y.get(0));
    return z;
}


