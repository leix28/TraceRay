//
//  core.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/10.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "core.h"

Attribute::Attribute() {
    diffuse = specular = 0;
}

Attribute::Attribute(const fvector3D &d, const fvector3D &s, const fvector3D &l) {
    
    setDiffuse(d);
    setSpecular(s);
    setLight(l);
}

fvector3D Attribute::getDiffuse() const {
    return diffuse;
}

fvector3D Attribute::getSpecular() const {
    return specular;
}

fvector3D Attribute::getLight() const {
    return light;
}


void Attribute::setDiffuse(const fvector3D &d) {
    diffuse = d;
}

void Attribute::setSpecular(const fvector3D &s) {
    specular = s;
}

void Attribute::setLight(const fvector3D &l) {
    light = l;
}

fvector3D Node::getPosition() const {
    return position;
}

void Node::setPosition(const fvector3D &p) {
    position = p;
}

Attribute Node::getAttribute() const {
    return attribute;
}

void Node::setAttribute(const Attribute &attr) {
    attribute = attr;
}