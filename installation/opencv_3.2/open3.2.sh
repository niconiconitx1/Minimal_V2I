sudo apt purge libopencv*
sudo apt-get purge libopencv4tegra-dev libopencv4tegra
sudo apt-get purge libopencv4tegra-repo
sudo apt-get update
apt-cache show libopencv4tegra
pkg-config --modversion opencv
pkg-config --cflags --libs opencv
sudo apt search opencv | grep installed
sudo apt-get install libv4l-dev 
sudo apt-get install v4l2ucp
sudo apt-get install v4l-utils
sudo apt-get install \
    libglew-dev \
    libtiff5-dev \
    zlib1g-dev \
    libjpeg-dev \
    libpng12-dev \
    libjasper-dev \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libpostproc-dev \
    libswscale-dev \
    libeigen3-dev \
    libtbb-dev \
    libgtk2.0-dev \
    pkg-config
sudo apt-get install cmake
cd #opencv-3.2.0 #/your opencv dir/
#Programs는 home폴더에 생성
# 거기 안에 open-3.2.0.zip 압축 해제

#sudo mkdir Programs
cd Programs

#sudo mv ../opencv-3.2.0 . -rf # 이거는 실행 안해도 될듯
cd opencv-3.2.0
sudo mkdir build
cd build
sudo cmake \
    -DCMAKE_BUILD_TYPE= RELEASE\
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DBUILD_PNG=OFF \
    -DBUILD_TIFF=OFF \
    -DBUILD_TBB=OFF \
    -DBUILD_JPEG=OFF \
    -DBUILD_JASPER=OFF \
    -DBUILD_ZLIB=OFF \
    -DBUILD_EXAMPLES=ON \
    -DBUILD_opencv_java=OFF \
    -DBUILD_opencv_python2=ON \
    -DBUILD_opencv_python3=OFF \
    -DENABLE_PRECOMPILED_HEADERS=OFF \
    -DWITH_OPENCL=OFF \
    -DWITH_OPENMP=OFF \
    -DWITH_FFMPEG=ON \
    -DWITH_GSTREAMER=ON \
    -DWITH_GSTREAMER_0_10=OFF \
    -DWITH_CUDA=ON \
    -DWITH_GTK=ON \
    -DWITH_VTK=OFF \
    -DWITH_TBB=ON \
    -DWITH_1394=OFF \
    -DWITH_OPENEXR=OFF \
    -DCUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda-8.0 \
    -DCUDA_ARCH_BIN=6.2 \
    -DCUDA_ARCH_PTX="" \
    -DINSTALL_C_EXAMPLES=ON \
    -DINSTALL_TESTS=OFF \
    -DOPENCV_TEST_DATA_PATH=../opencv_extra/testdata \
    ../  # opencv-3.2.0
sudo make -j6
sudo make install
