//
//  plane.h
//  TraceRay
//
//  Created by LazyLie on 15/5/14.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__plane__
#define __TraceRay__plane__

#include <stdio.h>
#include "core.h"

extern const double EPS;

class PlaneNode : public Node {
    fvector3D normal;
public:
    PlaneNode();
    PlaneNode(const fvector3D &p, const fvector3D &n, const Attribute &a);
    
    fvector3D getNormal() const;
    void setNormal(const fvector3D &n);
    
    double getCollide(const Ray &r) const;
    bool isSurface(const fvector3D &p) const;
    fvector3D getNormalVector(const  fvector3D &p) const;
    
};

#endif /* defined(__TraceRay__plane__) */
