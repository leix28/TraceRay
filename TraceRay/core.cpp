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

Attribute::Attribute(const double d, const double s, const fvector3D &c, const bool l) {
    
    diffuse = d;
    specular = s;
    color = c;
    light = l;
}

double Attribute::getDiffuse() const {
    return diffuse;
}

double Attribute::getSpecular() const {
    return specular;
}

fvector3D Attribute::getColor() const {
    return color;
}

bool Attribute::isLight() const {
    return light;
}

void Attribute::setDiffuse(const double d) {
    diffuse = d;
}

void Attribute::setSpecular(const double s) {
    specular = s;
}

void Attribute::setColor(const fvector3D &c) {
    color = c;
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