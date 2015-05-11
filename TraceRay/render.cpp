//
//  render.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "render.h"
#include "sphere.h"

Render::Render() {
    camera = std::shared_ptr<Camera>(new Camera());
    scene = std::shared_ptr<Scene>(new Scene());
    
    scene->addNode(std::shared_ptr<Node>(new SphereNode(fvector3D(4, 0, 0), 2)));
}

std::vector< std::vector<Color> > Render::renderScene() {
    const std::pair<int, int> resolution = camera->getResolution();
    std::vector< std::vector<Color> > graph(resolution.first, std::vector<Color>(resolution.second));
    
    return graph;
}