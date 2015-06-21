all:
	g++  -I/usr/include/opencv -I/usr/include/opencv2 -L/usr/lib/ -o main  TraceRay/camera.cpp TraceRay/core.cpp TraceRay/foundation.cpp TraceRay/main.cpp TraceRay/scene.cpp -std=c++11 -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -O2 -Wall
