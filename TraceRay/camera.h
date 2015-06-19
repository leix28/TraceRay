//
//  camera.h
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__camera__
#define __TraceRay__camera__

#include <stdio.h>
#include "core.h"

class Camera {
public:
  Vector filmCenter, filmHeight, filmWidth, position;
  int pixHeight, pixWidth;
  int sample;
  double aperture;
  double dis;
  Vector getFilm(double row, double col);
  std::vector<Ray> getRay(int row, int col);
};

#endif /* defined(__TraceRay__camera__) */
