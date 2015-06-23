all:
	g++  -I/usr/include/opencv -I/usr/include/opencv2 -L/usr/lib/ -o main  TraceRay/camera.cpp TraceRay/core.cpp TraceRay/foundation.cpp TraceRay/main.cpp TraceRay/scene.cpp -std=c++11 -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -O3 -Wall -march=native
icc:
	icpc  -I/usr/include/opencv -I/usr/include/opencv2 -L/usr/lib/ -o main  TraceRay/camera.cpp TraceRay/core.cpp TraceRay/foundation.cpp TraceRay/main.cpp TraceRay/scene.cpp -std=c++11 -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -O3 -Wall -ipo -xAVX -march=native
clang:
	clang++  -I/usr/local/include -L/usr/local/lib/ -o main  TraceRay/camera.cpp TraceRay/core.cpp TraceRay/foundation.cpp TraceRay/main.cpp TraceRay/scene.cpp -std=c++11 -stdlib=libc++ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -Ofast -Wall -march=native
