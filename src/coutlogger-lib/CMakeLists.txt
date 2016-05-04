cmake_minimum_required(VERSION 3.3)
project(coutlogger-lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Project headers directory
include_directories("src/main/include")

#
#See README.md
#
#Library dependencies
#opencv
#include_directories("target/nar/opencv-core-2.4.10-noarch/include")
#include_directories("target/nar/opencv-highgui-2.4.10-noarch/include")
#include_directories("target/nar/opencv-imgproc-2.4.10-noarch/include")
#log4z
#include_directories("target/nar/log4z-3.0.1-noarch/include")
#rapidjson
#include_directories("target/nar/rapidjson-1.0.2-noarch/include")
#basen-lib
#include_directories("target/nar/basen-lib-1.0-noarch/include")
#
#My dependencies
#commons-lib
#include_directories("target/nar/commons-1.0-noarch/include")
#jdk-jni
#include_directories("target/nar/jni-include-jdk1.7.0_80-noarch/include")
#include_directories("target/nar/jni-include-win32-jdk1.7.0_80-noarch/include")
#pipe-lib
#include_directories("target/nar/pipe-lib-1.0-noarch/include")
#jni-lib
#include_directories("target/nar/jni-lib-1.0-noarch/include")
#process-lib
#include_directories("target/nar/process-lib-1.0-noarch/include")
#winreg-lib
#include_directories("target/nar/winreg-lib-1.0-noarch/include")
#
#Test dependencies
#gtest
#include_directories("target/test-nar/gtest-1.7.0-noarch/include")
#

#Project sources and headers
set(SOURCE_FILES src/main/include/main.h src/main/c/main.cpp src/main/include/coutlogger/coutlogger.h)
add_executable(coutlogger-lib ${SOURCE_FILES})

#Tests sources and headers
add_executable(coutlogger-lib-test src/test/c/main-test.cpp)
