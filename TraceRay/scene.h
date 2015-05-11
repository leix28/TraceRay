//
//  scene.h
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__scene__
#define __TraceRay__scene__

#include <stdio.h>
#include <vector>
#include "core.h"
#include <memory>

class Scene {
    std::vector< std::shared_ptr<Node> > nodes;
public:
    void addNode(const std::shared_ptr<Node> &node);
    double getCollise(const Ray &r) const;
    fvector3D getNormalVector(const fvector3D &p) const;
};

#endif /* defined(__TraceRay__scene__) */
