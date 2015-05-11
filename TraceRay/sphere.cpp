//
//  sphere.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "sphere.h"

SphereNode::SphereNode() {
    setRadius(1.0);
}

SphereNode::SphereNode(const fvector3D &pos, const double r) {
    setPosition(pos);
    setRadius(r);
}


double SphereNode::getRadius() const {
    return radius;
}

void SphereNode::setRadius(const double r) {
    radius = r;
}


double SphereNode::getCollide(const Ray &r) const {
    assert(r.getSource().subtract(getPosition()).length() >= getRadius());
    
    fvector3D v = r.getSource().subtract(getPosition());
    double tmp = sqr(r.getDirection().dotProduct(v)) - (v.dotProduct(v) - sqr(getRadius()));
    if (tmp < 0) return -1;
    
    return -r.getDirection().dotProduct(v) - sqrt(tmp);
}

bool SphereNode::isSurface(const fvector3D &p) const {
    double dlt = p.subtract(getPosition()).length() - getRadius();
    return -EPS < dlt && dlt < EPS;
}

fvector3D SphereNode::getNormalVector(const fvector3D &p) const {
    assert(isSurface(p));
    return p.subtract(getPosition()).normalize();
}