//
//  camera.h
//  TraceRay
//
//  Created by LazyLie on 15/5/11.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__camera__
#define __TraceRay__camera__

#include <stdio.h>
#include "core.h"
#include <utility>

extern const double EPS;

class Camera {
    fvector3D position, center, width, height;
    double resolution;
    std::pair<int, int> pixel;
    
public:
    Camera();
    Camera(const fvector3D &pos, const fvector3D &c, const fvector3D &w, const fvector3D &h, const double r);
    
    fvector3D getPosition() const;
    fvector3D getFilmCenter() const;
    fvector3D getFilmWidth() const;
    fvector3D getFilmHeight() const;
    std::pair<int, int> getResolution() const;

    void setPosition(const fvector3D &p);
    void setFilm(const fvector3D &c, const fvector3D &w, const fvector3D &h);
    void setResolution(const double r);
 
    Ray getRay(int x, int y) const;
};

#endif /* defined(__TraceRay__camera__) */
