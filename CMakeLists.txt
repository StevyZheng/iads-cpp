cmake_minimum_required(VERSION 3.8)
project(iads)

set(CMAKE_CXX_STANDARD 11)
set(BOOST_ROOT "/usr/include/boost")
INCLUDE_DIRECTORIES(/usr/include/boost)
set(Boost_USE_STATIC_LIBS ON)
# link_directories(/usr/lib)
find_package(Boost 1.66.0 COMPONENTS log thread system regex REQUIRED)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

set(SOURCE_FILES main.cpp lib/linux/Command.cpp lib/linux/Command.h lib/ThreadPool.h lib/Exception.h lib/linux/Common.cpp lib/linux/Common.h)
add_executable(iads ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(iads ${Boost_LIBRARIES})