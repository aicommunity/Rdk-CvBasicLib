cmake_minimum_required (VERSION 2.8)
project(Rdk-CvBasicLib)

# Put all the archive targets into ${PROJECT_NAME}/Lib/

set(A_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../Bin/Platform/Linux/Libs/")
file(MAKE_DIRECTORY ${A_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${A_OUTPUT_DIR})

# Source files

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Core/")
set(SOURCE_FILES
"${SOURCE_DIR}/Basic.cpp"
"${SOURCE_DIR}/UBAColorConvert.cpp"
"${SOURCE_DIR}/UBACrop.cpp"
"${SOURCE_DIR}/UBAFlipImage.cpp"
"${SOURCE_DIR}/UBAModel.cpp"
"${SOURCE_DIR}/UBAReceiver.cpp"
"${SOURCE_DIR}/UBAReduce.cpp"
"${SOURCE_DIR}/UBAResize.cpp"
"${SOURCE_DIR}/UBARotate.cpp"
"${SOURCE_DIR}/UBASource.cpp"
"${SOURCE_DIR}/UBASourceMultiFile.cpp"
"${SOURCE_DIR}/UBPipeline.cpp"
"${SOURCE_DIR}/UBASourceFile.cpp")
	
# Headers
	
include_directories(${SOURCE_DIR})

# Create target file

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.9")
	set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()


