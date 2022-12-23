cmake_minimum_required(VERSION 3.5)

project(decoder_demo)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-write-strings")	

set(PROJECT_LINK_DIR ${CMAKE_SOURCE_DIR}/lib)
set(GST_INCLUDE_PATH /usr/local/gstreamer-1.0)
include_directories(include)
include_directories(${GST_INCLUDE_PATH}/include/gstreamer-1.0
                    ${GST_INCLUDE_PATH}/lib/${CMAKE_SYSTEM_PROCESSOR}-linux-gnu/gstreamer-1.0/include
                    ${GST_INCLUDE_PATH}/lib/${CMAKE_SYSTEM_PROCESSOR}-linux-gnu/glib-2.0/include/
                    ${GST_INCLUDE_PATH}/include/glib-2.0
)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_LINK_DIR}/libalg_h264_decoder.so
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)