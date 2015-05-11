//
//  scene.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "scene.h"

void Scene::addNode(const std::shared_ptr<Node> &node) {
    nodes.push_back(node);
}

double Scene::getCollise(const Ray &r) const {
    double tmp = -1;
    for (auto &node : nodes) {
        if (tmp == -1)
            tmp = node->getCollide(r);
        else
            tmp = fmin(tmp, node->getCollide(r));
    }
    return tmp;
}

fvector3D Scene::getNormalVector(const fvector3D &p) const {
    for (auto &node : nodes) {
        if (node->isSurface(p))
            return node->getNormalVector(p);
    }
    assert(0);
}