cmake_minimum_required(VERSION 3.16)
project(Rdk_CvBasicLib LANGUAGES CXX)

set(TARGET_NAME Rdk-CvBasicLib.qt)

add_library(${TARGET_NAME} STATIC)

target_include_directories(${TARGET_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}/Rdk/Deploy/Include
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core
)

file(GLOB CV_HEADERS CONFIGURE_DEPENDS
  ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/*.h
)
file(GLOB CV_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/*.cpp
)

# UBAGuiSelection.cpp is needed for the UMouse implementation, which is used in Basic.h
# The file is returned to compilation to ensure UMouse symbols are available
list(FILTER CV_SOURCES EXCLUDE REGEX "/Libraries/Rdk-CvBasicLib/Core/UCR.*\\.cpp$")
list(FILTER CV_SOURCES EXCLUDE REGEX "/Libraries/Rdk-CvBasicLib/Core/TCapture.*\\.cpp$")

target_sources(${TARGET_NAME}
  PRIVATE
    ${CV_SOURCES}
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/UCRPrincipalComponentAnalysis.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/UCRBarnesHutTSNE.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/TSNE/tsne.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/TSNE/sptree.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/TCapture.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/TCaptureImageSequence.cpp
)

target_compile_definitions(${TARGET_NAME} PUBLIC RDK_QT RDK_LIB_CVS_REVISION=0)

include(${CMAKE_SOURCE_DIR}/cmake/SelectQt.cmake)
target_link_libraries(${TARGET_NAME} PUBLIC
  Nmsdk::Qt::Core
  Threads::Threads
  rdk.static.qt
  Rdk-BasicLib.qt
)
target_link_libraries(${TARGET_NAME} PUBLIC Nmsdk::Boost)

if (RDK_USE_OPENCV AND OpenCV_FOUND)
  target_link_libraries(${TARGET_NAME} PUBLIC ${OpenCV_LIBS})
endif()


