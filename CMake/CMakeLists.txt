cmake_minimum_required(VERSION 3.16)
project(Rdk_CvBasicLib LANGUAGES CXX)

set(TARGET_NAME Rdk-CvBasicLib.qt)

add_library(${TARGET_NAME} STATIC)

target_include_directories(${TARGET_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}/Rdk/Deploy/Include
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core
    ${CMAKE_SOURCE_DIR}/Rdk/Core/Engine
    ${CMAKE_SOURCE_DIR}/Rdk/Core/System
)

file(GLOB CV_HEADERS
  ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/*.h
)
file(GLOB CV_SOURCES
  ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core/*.cpp
)

# Исключаем только заведомо GUI-зависимый файл; остальные нужны для символов из Basic.cpp
list(FILTER CV_SOURCES EXCLUDE REGEX "/Libraries/Rdk-CvBasicLib/Core/UBAGuiSelection\\.cpp$")
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

find_package(Qt5 REQUIRED COMPONENTS Core)
target_link_libraries(${TARGET_NAME} PUBLIC Qt5::Core Threads::Threads rdk.static.qt Rdk-BasicLib.qt)
# Boost.Filesystem заменен на std::filesystem (C++20)
# Boost.System больше не требуется
# find_package(Boost QUIET COMPONENTS filesystem system)
# if(Boost_FOUND)
#   target_link_libraries(${TARGET_NAME} PUBLIC Boost::filesystem Boost::system)
# endif()

if (RDK_USE_OPENCV AND OpenCV_FOUND)
  target_link_libraries(${TARGET_NAME} PUBLIC ${OpenCV_LIBS})
endif()


