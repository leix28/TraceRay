//
//  render.h
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__render__
#define __TraceRay__render__

#include <stdio.h>
#include "core.h"
#include "scene.h"
#include "camera.h"
#include <memory>

class Render{
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Scene> scene;
    
public:
    Render();
    
    std::vector< std::vector<Color> > renderScene();
    
};

#endif /* defined(__TraceRay__render__) */