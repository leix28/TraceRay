//
//  sphere.h
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__sphere__
#define __TraceRay__sphere__

#include <stdio.h>
#include "core.h"

class SphereNode : public Node {
    double radius;
    
public:
    SphereNode();
    SphereNode(const fvector3D &pos, const double r);
    
    double getRadius() const;
    void setRadius(const double r);
    
    double getCollide(const Ray &r) const;
    bool isSurface(const fvector3D &p) const;
    fvector3D getNormalVector(const fvector3D &p) const;
};


#endif /* defined(__TraceRay__sphere__) */
