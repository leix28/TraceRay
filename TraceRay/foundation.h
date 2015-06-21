//
//  foundation.h
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__foundation__
#define __TraceRay__foundation__

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>

extern const double EPS;

class Vector {
public:
  Vector();
  Vector(double _x, double _y, double _z);

  double x, y, z;
};

Vector operator + (const Vector &a, const Vector &b);
Vector operator - (const Vector &a, const Vector &b);
Vector operator * (const double a, const Vector &b);
Vector operator * (const Vector &a, const double b);
Vector operator * (const Vector &a, const Vector &b);
Vector operator / (const Vector &a, const double b);
double innerProduct(const Vector &a, const Vector &b);
Vector crossProduct(const Vector &a, const Vector &b);

#endif /* defined(__TraceRay__foundation__) */
