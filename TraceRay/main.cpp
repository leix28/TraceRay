//
//  main.cpp
//  TraceRay
//
//  Created by LazyLie on 15/5/10.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include <iostream>
#include "render.h"
#include "opencv2/opencv.hpp"

cv::Mat convertToCV(const std::vector< std::vector<fvector3D> > &matrix) {
    assert(matrix.size() && matrix[0].size());

    int h = (int)matrix.size();
    int w = (int)matrix[0].size();
    
    cv::Mat image(h, w, CV_64FC3);
    
    for (auto i = 0; i < h; i++)
        for (auto j = 0; j < w; j++) {
            image.at<double>(i, j, 0) = matrix[i][j].get(2) * 256;
            image.at<double>(i, j, 1) = matrix[i][j].get(1) * 256;
            image.at<double>(i, j, 2) = matrix[i][j].get(0) * 256;
        }
    
    return image;
}

int main(int argc, const char * argv[]) {
    Render render;
    
    auto result = render.renderScene();
    
    auto image = convertToCV(result);
    
    imwrite("img.png", image);
    
    return 0;
}
