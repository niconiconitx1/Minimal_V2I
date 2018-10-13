#! /usr/bin/env bash
# Change Directory
$ cd /usr/local/include

# Remove openCV folder
sudo rm -rf opencv
sudo rm -rf opencv2

# Change Directory
cd /usr/local/lib

# Remove all libopencv_ related files
sudo rm libopencv_*

# Add universal repository to Ubuntu
sudo apt-add-repository universe
sudo apt-get update

# Some general development libraries
sudo apt-get install -y build-essential make cmake cmake-curses-gui g++

# libav video input/output development libraries
sudo apt-get install -y libavformat-dev libavutil-dev libswscale-dev

# Video4Linux camera development libraries
sudo apt-get install -y libv4l-dev

# Eigen3 math development libraries
sudo apt-get install -y libeigen3-dev

# OpenGL development libraries (to allow creating graphical windows)
sudo apt-get install -y libglew1.6-dev

# GTK development libraries (to allow creating graphical windows)
sudo apt-get install -y libgtk2.0-dev

# Compile and install opencv
cd ~/Programs
unzip opencv-3.1.0.zip
cd opencv-3.1.0
mkdir build
cd build
cmake -DWITH_CUDA=ON -DCUDA_ARCH_BIN="5.3" -DCUDA_ARCH_PTX="" -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DCUDA_FAST_MATH=ON  -DCMAKE_INSTALL_PREFIX=/home/ubuntu/Programs/opencv-3.1.0 ..
make -j4 install
