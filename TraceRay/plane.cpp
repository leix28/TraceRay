//
//  plane.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/14.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "plane.h"

PlaneNode::PlaneNode() {
    setNormal(fvector3D(0, 0, 1));
}

PlaneNode::PlaneNode(const fvector3D &p, const fvector3D &n, const Attribute &a) {
    setPosition(p);
    setNormal(n);
    setAttribute(a);
}

fvector3D PlaneNode::getNormal()const {
    return normal;
}

void PlaneNode::setNormal(const fvector3D &n) {
    normal = n.normalize();
}

double PlaneNode::getCollide(const Ray &r) const {
    double t1 = getPosition().subtract(r.getSource()).dotProduct(getNormal());
    double t2 = r.getDirection().dotProduct(getNormal());
    if (fabs(t2) < EPS)
        return fabs(t1) > EPS ? -1 : 0;
    else {
        double t3 = t1 / t2;
        return t3 < 0 ? -1 : t3;
    }
}


bool PlaneNode::isSurface(const fvector3D &p) const {
    return fabs(p.subtract(getPosition()).dotProduct(getNormal())) < EPS;
}

fvector3D PlaneNode::getNormalVector(const fvector3D &p) const {
    return normal;
}