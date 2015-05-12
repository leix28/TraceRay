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
    fvector3D light;
    fvector3D diffuse, specular;
public:
    Attribute();
    Attribute(const fvector3D &d, const fvector3D &s, const fvector3D &c);
    fvector3D getDiffuse() const;
    fvector3D getSpecular() const;
    fvector3D getLight() const;
    
    void setDiffuse(const fvector3D &d);
    void setSpecular(const fvector3D &s);
    void setLight(const fvector3D &l);
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
