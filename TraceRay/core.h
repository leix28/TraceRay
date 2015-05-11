//
//  core.h
//  TraceRay
//
//  Created by LazyLie on 15/5/10.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__core__
#define __TraceRay__core__

#include <stdio.h>
#include "foundation.h"

extern const double EPS;

class Attribute {
    fvector3D color;
    double diffuse, specular;
    bool light;
public:
    Attribute();
    Attribute(const double d, const double s, const fvector3D &c, const bool l);
    double getDiffuse() const;
    double getSpecular() const;
    fvector3D getColor() const;
    bool isLight() const;
    
    void setDiffuse(const double d);
    void setSpecular(const double s);
    void setColor(const fvector3D &c);
};

class Node {
    fvector3D position;
    Attribute attribute;
public:
    fvector3D getPosition() const;
    void setPosition(const fvector3D &p);
    Attribute getAttribute() const;
    void setAttribute(const Attribute &attr);
    virtual double getCollide(const Ray &r) const = 0;
    virtual bool isSurface(const fvector3D &p) const = 0;
    virtual fvector3D getNormalVector(const fvector3D &p) const = 0;
};

#endif /* defined(__TraceRay__core__) */
