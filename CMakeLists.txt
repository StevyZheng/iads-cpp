cmake_minimum_required(VERSION 3.8)
project(iads)

set(CMAKE_CXX_STANDARD 11)
set(BOOST_ROOT "/usr/local/include/boost")
INCLUDE_DIRECTORIES(/usr/local/include/boost /usr/local/include/sqlcipher lib/eigen3.3.5)
set(Boost_USE_STATIC_LIBS ON)
link_directories(/usr/local/lib)
find_package(Boost 1.66.0 COMPONENTS log date_time thread filesystem system program_options regex REQUIRED)
link_libraries(libsqlcipher.a crypto)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread -ldl")

set(SOURCE_FILES main.cpp lib/linux/Command.cpp lib/linux/Command.h lib/ThreadPool.h lib/Exception.h lib/linux/Common.cpp lib/linux/Common.h lib/linux/SystemInfo.cpp lib/linux/SystemInfo.h lib/stevy.h lib/linux/Storage.cpp lib/linux/Storage.h lib/ConsoleTable.h lib/ConsoleTable.cpp lib/CmdlineParser.cpp lib/CmdlineParser.h lib/tableformatter.hpp lib/burn/BurnInTest.cpp lib/burn/BurnInTest.h lib/linux/Config.cpp lib/linux/Config.h lib/linux/Config.h apps/Logparser.cpp apps/Logparser.h)
add_executable(iads ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(iads ${Boost_LIBRARIES})