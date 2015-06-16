//
//  Model.h
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__Model__
#define __TraceRay__Model__

#include <stdio.h>
#include "core.h"

class Model {
public:
  std::vector<Piece> shape;
  Attribute attribute;
  void loadShapeFromFile(std::string filename);
  double collision(Ray r);
};

#endif /* defined(__TraceRay__Model__) */
