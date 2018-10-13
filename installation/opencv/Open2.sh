#! /usr/bin/env bash
sudo add-apt-repository universe
sudo apt-get update
# Some general development libraries
sudo apt-get -y install build-essential make cmake cmake-curses-gui g++
# libav video input/output development libraries
sudo apt-get -y install libavformat-dev libavutil-dev libswscale-dev
# Video4Linux camera development libraries
sudo apt-get -y install libv4l-dev
# Eigen3 math development libraries
sudo apt-get -y install libeigen3-dev
# OpenGL development libraries (to allow creating graphical windows)
sudo apt-get -y install libglew1.6-dev
# GTK development libraries (to allow creating graphical windows)
sudo apt-get -y install libgtk2.0-dev
# (Optional) Gstreamer development libraries (for Network IP camera input)
sudo apt-get install libgstreamer1.0 libgstreamer1.0-dev libgstreamer-plugins-bad1.0-0 libgstreamer-plugins-base1.0-0 libgstreamer-plugins-base1.0-dev
VERSION=2.4.9
cd ~/Downloads
rm ${VERSION}.zip
wget https://github.com/opencv/opencv/archive/${VERSION}.zip
VERSION=2.4.9
cd ~/Downloads
unzip ${VERSION}.zip
mv opencv-${VERSION} ~/
cd ~/opencv-${VERSION}
mkdir build
cd build
cmake -DWITH_CUDA=ON -DCUDA_ARCH_BIN="3.2" -DCUDA_ARCH_PTX="" -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF ..
cmake -DCMAKE_BUILD_TYPE=RELEASE -DWITH_CUBLAS=ON -DENABLE_FAST_MATH=ON -DCUDA_FAST_MATH=ON ..
cd ~/Downloads
rm ${VERSION}.zip
wget https://github.com/opencv/opencv_contrib/archive/${VERSION}.zip
unzip ${VERSION}.zip
mv opencv_contrib-${VERSION} ~/
cd ~/opencv-${VERSION}/build
cmake -DOPENCV_EXTRA_MODULES_PATH=~/opencv_contrib-${VERSION}/modules ..
ccmake ..
make -j4
sudo make install
echo "# Use OpenCV and other custom-built libraries." >> ~/.bashrc
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/" >> ~/.bashrc
source ~/.bashrc
sudo ldconfig
# Make sure we have installed a C++ compiler.
sudo apt-get install build-essential g++
# Test a simple OpenCV program. Creates a graphical window, hence you should plug a HDMI monitor in or use a remote viewer such as X Tunneling or VNC or TeamViewer on your desktop.
cd ~/opencv-2.4.9/samples/cpp
g++ edge.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -o edge
(Or for OpenCV 3.0: g++ edge.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -o edge)
./edge

