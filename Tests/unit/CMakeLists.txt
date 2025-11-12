# Rdk-CvBasicLib Unit Tests CMake Configuration
cmake_minimum_required(VERSION 3.16)

# Find Google Test
find_package(GTest REQUIRED)

# Create test executable for CvBasicLib tests
add_executable(RdkCvBasicLibTests
    TestCvBasicLibComponents.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/Libraries_con.cpp
)

target_include_directories(RdkCvBasicLibTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Rdk/Core
    ${CMAKE_SOURCE_DIR}/Rdk/Deploy/Include
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core
    ${CMAKE_SOURCE_DIR}/Tests
)

target_link_libraries(RdkCvBasicLibTests PRIVATE
    rdk.static.qt
    Rdk-CvBasicLib.qt
    Rdk-HardwareLib.qt
    Nmsdk-PulseLib.qt
    Nmsdk-MotionControlLib.qt
    TestHelpers
    GTest::gtest
    GTest::gtest_main
    glog::glog
    Threads::Threads
)

target_compile_features(RdkCvBasicLibTests PRIVATE cxx_std_20)
target_compile_definitions(RdkCvBasicLibTests PRIVATE RDK_QT RDK_LIB_CVS_REVISION=0)

# Register tests
add_test(NAME RdkCvBasicLibTests COMMAND RdkCvBasicLibTests)

