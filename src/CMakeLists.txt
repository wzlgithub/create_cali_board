CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ADD_DEFINITIONS(-std=c++11)
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)
ADD_EXECUTABLE(compose_dm dm_creator.cpp)
TARGET_LINk_LIBRARIES(compose_dm ${OpenCV_LIBS} libDataMatrixDetector.a)
