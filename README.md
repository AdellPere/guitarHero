# guitarHero

alias opencv="~/.compile_opencv.sh"

export LD_LIBRARY_PATH=/usr/local/opencv-2.4/lib:$LD_LIBRARY_PATH
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/local/opencv-2.4/include/opencv2/:/usr/local/opencv-2.4/include
export OPENCV_CFLAGS=-I/usr/local/opencv-2.4/include/opencv2/
export O_LIBS="-L/usr/local/opencv-2.4/lib/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann"
