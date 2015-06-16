//
//  render.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "render.h"

fvector3D lightDir(0, 0, -1);
fvector3D lightColor(1, 1, 1);

Render::Render() {
    camera = std::shared_ptr<Camera>(new Camera());
    scene = std::shared_ptr<Scene>(new Scene());
    
}

fvector3D Render::trace(const Ray &ray, int dep) const {
    double tmp = scene->getCollise(ray);
    if (tmp < 0) return fvector3D();
    fvector3D p = ray.getPoint(tmp);
    Attribute attr = scene->getAttribute(p);
    
    fvector3D normal = scene->getNormalVector(p);
    double NdotL = -normal.dotProduct(ray.getDirection());
    fvector3D diffuseTerm = lightColor.multiply(attr.getDiffuse().multiply(fmax(NdotL, 0)));
    
    if (dep == MAX_DEP)
        return diffuseTerm;
    
    Ray ref(p, ray.getDirection().subtract(normal.multiply(ray.getDirection().dotProduct(normal) * 2)));
    fvector3D reflectTerm = attr.getSpecular().multiply(trace(ref, dep + 1));
    return diffuseTerm.add(reflectTerm);
}

std::vector< std::vector<fvector3D> > Render::renderScene() {
    const std::pair<int, int> resolution = camera->getResolution();
    std::vector< std::vector<fvector3D> > graph(resolution.first, std::vector<fvector3D>(resolution.second));
    
    for (int i = 0; i < resolution.first; i++)
        for (int j = 0; j < resolution.second; j++) {
            Ray ray = camera->getRay(i, j);
            graph[i][j] = trace(ray, 0);
        }
    
    return graph;
}