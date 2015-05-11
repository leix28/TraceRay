//
//  core.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/10.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "core.h"

fvector3D Node::getPosition() const {
    return position;
}

void Node::setPosition(const fvector3D &p) {
    position = p;
}

