cmake_minimum_required(VERSION 3.10)

project(arch_streamer)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 17)

include(FindPkgConfig)
pkg_check_modules(GST    REQUIRED gstreamer-1.0)
pkg_check_modules(GSTAPP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GLIB   REQUIRED glib-2.0)
pkg_check_modules(GFLAGS REQUIRED gflags)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

message(STATUS "GST:   ${GST_INCLUDE_DIRS},${GST_LIBRARY_DIRS},${GST_LIBRARIES}")
message(STATUS "GSTAPP:${GSTAPP_INCLUDE_DIRS},${GSTAPP_LIBRARY_DIRS},${GSTAPP_LIBRARIES}")
message(STATUS "GLIB:  ${GLIB_INCLUDE_DIRS},${GLIB_LIBRARY_DIRS},${GLIB_LIBRARIES}")
message(STATUS "JSON:  ${JSON_INCLUDE_DIRS},${JSON_LIBRARY_DIRS},${JSON_LIBRARIES}")
message(STATUS "GFLAGS:${GFLAGS_INCLUDE_DIRS},${GFLAGS_LIBRARY_DIRS},${GFLAGS_LIBRARIES}")

# opencv
include_directories(
        ${PROJECT_SOURCE_DIR}/inc
        ${GST_INCLUDE_DIRS}
        ${GSTAPP_INCLUDE_DIRS}
        ${GLIB_INCLUDE_DIRS}
        ${GFLAGS_INCLUDE_DIRS}
        ${JSONCPP_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${spdlog_INCLUDE_DIRS}
        ${DeepStream_INCLUDE_DIRS}
)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(
        ${GST_LIBRARY_DIRS}
        ${GSTAPP_LIBRARY_DIRS}
        ${GLIB_LIBRARY_DIRS}
        ${GFLAGS_LIBRARY_DIRS}
        ${JSONCPP_LIBRARY_DIRS}
        ${OpenCV_LIBRARY_DIRS}
        ${spdlog_LIBRARY_DIRS}
        ${DeepStream_LIBRARY_DIRS}
)

add_executable(rtmp2sink
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/StreamMgr.cpp
        ${CMAKE_SOURCE_DIR}/src/audio_manage.cpp
        ${CMAKE_SOURCE_DIR}/src/video_manage.cpp
        )

target_link_libraries(rtmp2sink
        ${GST_LIBRARIES}
        ${GSTAPP_LIBRARIES}
        ${GLIB_LIBRARIES}
        ${GFLAGS_LIBRARIES}
        ${JSONCPP_LIBRARIES}
        ${OpenCV_LIBRARIES}
        pthread
        gstpbutils-1.0
        )
