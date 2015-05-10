//
//  foundation.h
//  TraceRay
//
//  Created by LazyLie on 15/5/10.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__foundation__
#define __TraceRay__foundation__

#include <stdio.h>


class fvector3D {
public:
    fvector3D();
    fvector3D(double _v[3]);
    fvector3D(double _x, double _y, double _z);
    
    double get(const int index) const;
    void set(const int index, const double value);
    
    double length() const;
    
    fvector3D add(const fvector3D &y) const;
    fvector3D subtract(const fvector3D &y) const;
    fvector3D multiply(const double y) const;
    fvector3D multiply(const fvector3D y) const;
    double dotProduct(const fvector3D &y) const;
    fvector3D crossProduct(const fvector3D &y) const;
    
private:
    double v[3];
};


#endif /* defined(__TraceRay__foundation__) */
