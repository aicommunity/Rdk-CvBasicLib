# Rdk-CvBasicLib Integration Tests CMake Configuration
cmake_minimum_required(VERSION 3.16)

# Find Google Test
find_package(GTest REQUIRED)

# Create test executable for CvBasicLib integration tests
add_executable(RdkCvBasicLibIntegrationTests
    TestCvBasicLibIntegration.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/Libraries_con.cpp
)

target_include_directories(RdkCvBasicLibIntegrationTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Rdk/Core
    ${CMAKE_SOURCE_DIR}/Rdk/Deploy/Include
    ${CMAKE_SOURCE_DIR}/Libraries/Rdk-CvBasicLib/Core
    ${CMAKE_SOURCE_DIR}/Tests
)

target_link_libraries(RdkCvBasicLibIntegrationTests PRIVATE
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

target_compile_features(RdkCvBasicLibIntegrationTests PRIVATE cxx_std_20)
target_compile_definitions(RdkCvBasicLibIntegrationTests PRIVATE RDK_QT RDK_LIB_CVS_REVISION=0)

# Register tests
add_test(NAME RdkCvBasicLibIntegrationTests COMMAND RdkCvBasicLibIntegrationTests)

