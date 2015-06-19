all:
	g++ -I/usr/include/opencv2 -L/usr/lib/ -o main  TraceRay/camera.cpp TraceRay/core.cpp TraceRay/foundation.cpp TraceRay/main.cpp TraceRay/scene.cpp