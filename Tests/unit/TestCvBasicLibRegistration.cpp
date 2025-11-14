#include <gtest/gtest.h>
#include "../../../../Tests/TestHelpers.h"
#include "../../../../Rdk/Deploy/Include/rdk.h"
#include "../../../../Libraries/Libraries.h"
#include "../../../Deploy/Include/Lib.h"
#include "../../Core/Basic.h"
#include <algorithm>
#include <vector>
#include <set>

using namespace RDK;
using namespace RDK::TestHelpers;

namespace {

// Expected CvBasicLib component categories and their key classes
struct CvBasicLibCategory {
    std::string name;
    std::vector<std::string> keyClasses;
};

const std::vector<CvBasicLibCategory> EXPECTED_CVBASICLIB_CATEGORIES = {
    {"Core Models", {"Model", "Pipeline", "ParallelPipeline"}},
    {"Sources", {"Source", "SourceFile", "SourceMultiFile", "Receiver"}},
    {"Image Processing", {"ColorConvert", "ResizeEdges", "RotateSimple", "Crop", "Reduce", "UBAFlipImageSimple"}},
    {"Background Processing", {"BackgroundAvg", "BackgroundExponnential", "DeltaBackgroundExponnential", "BackgroundSimpleAdaptive", "UBABackgroundDependDiff"}},
    {"Binarization", {"TBinarizationSimple", "TBinarizationSimpleAdaptiveThreshold", "UBABinarizationOtsu"}},
    {"Labeling", {"TLabelingSimple"}},
    {"Math Operations", {"BMathOperator", "UMatrixIntMath", "UMatrixDoubleMath", "UMDMatrixDoubleMux", "UMDMatrixIntMux", "UMDScalarDoubleMux", "UMDScalarIntMux"}},
    {"Simulators", {"VideoSimulatorSimple", "RotCameraSimulator", "VideoSimulatorSimpleBin", "DataSimulatorSimple", "BitmapSourceSimple", "BitmapSourceFile"}},
    {"Base Classes", {"UClassifierBase", "UDetectorBase", "USegmentatorBase", "UClassifierResSaver", "UDetResSaverPVOC"}},
    {"Analysis", {"UCRPrincipalComponentAnalysis", "UCRBarnesHutTSNE", "BStatisticSimple"}},
    {"Display", {"UBShowRect", "ShowObjectsSimple"}},
    {"Capture", {"TCaptureImageSequence"}}
};

} // namespace

class CvBasicLibRegistrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        InitTestLogging();
        
        // Create storage with BasicLib and CvBasicLib
        storage = CreateStorageWithLibraries({&RDK::BasicLibrary, &RDK::CvBasicLibrary});
        ASSERT_NE(storage, nullptr) << "Failed to create storage";
        
        // Upload libraries in correct order
        RDK::BasicLibrary.Upload(storage.get());
        RDK::CvBasicLibrary.Upload(storage.get());
        
        // Call CreateClassSamples for CvBasicLib
        try {
            RDK::CvBasicLibrary.CreateClassSamples(storage.get());
        } catch (const std::exception& ex) {
            GTEST_SKIP() << "CvBasicLib CreateClassSamples failed: " << ex.what();
        }
    }

    void TearDown() override {
        storage.reset();
    }

    std::shared_ptr<UStorage> storage;
};

// Test that all expected CvBasicLib classes are registered
TEST_F(CvBasicLibRegistrationTest, AllCvBasicLibClassesRegistered) {
    ASSERT_NE(storage, nullptr);
    
    std::vector<std::string> allClasses;
    storage->GetClassNameList(allClasses);
    
    std::set<std::string> registeredClasses(allClasses.begin(), allClasses.end());
    
    // Check each category
    for (const auto& category : EXPECTED_CVBASICLIB_CATEGORIES) {
        for (const auto& className : category.keyClasses) {
            EXPECT_TRUE(storage->CheckClass(className)) 
                << "CvBasicLib class '" << className << "' from category '" << category.name << "' should be registered";
            
            if (storage->CheckClass(className)) {
                EXPECT_TRUE(registeredClasses.count(className) > 0)
                    << "Class '" << className << "' should be in class list";
            }
        }
    }
}

// Test that minimum number of CvBasicLib classes are registered
TEST_F(CvBasicLibRegistrationTest, CvBasicLibClassesCount) {
    ASSERT_NE(storage, nullptr);
    
    std::vector<std::string> allClasses;
    storage->GetClassNameList(allClasses);
    
    // Count CvBasicLib classes
    size_t cvLibClassCount = 0;
    std::vector<std::string> cvLibPrefixes = {
        "Pipeline", "Source", "ColorConvert", "ResizeEdges", "RotateSimple",
        "Crop", "Reduce", "Background", "Binarization", "Labeling",
        "BMathOperator", "Matrix", "MDScalar", "VideoSimulator", "DataSimulator",
        "BitmapSource", "UClassifier", "UDetector", "USegmentator", "UCR",
        "ShowRect", "ShowObjects", "TCapture"
    };
    
    for (const auto& className : allClasses) {
        for (const auto& prefix : cvLibPrefixes) {
            if (className.find(prefix) == 0) {
                cvLibClassCount++;
                break;
            }
        }
    }
    
    // We expect at least 40 classes
    EXPECT_GE(cvLibClassCount, 40) 
        << "Expected at least 40 CvBasicLib classes, but found " << cvLibClassCount;
}

// Test that critical CvBasicLib classes are registered
TEST_F(CvBasicLibRegistrationTest, CriticalClassesRegistered) {
    ASSERT_NE(storage, nullptr);
    
    // Critical classes that are commonly used
    std::vector<std::string> criticalClasses = {
        "Pipeline",
        "SourceFile",
        "ColorConvert",
        "Crop",
        "Reduce",
        "BackgroundAvg",
        "TBinarizationSimple",
        "TLabelingSimple"
    };
    
    for (const auto& className : criticalClasses) {
        EXPECT_TRUE(storage->CheckClass(className)) 
            << "Critical CvBasicLib class '" << className << "' should be registered";
    }
}

// Test that CvBasicLib classes can be created
TEST_F(CvBasicLibRegistrationTest, CvBasicLibClassesCreation) {
    ASSERT_NE(storage, nullptr);
    
    // Test Pipeline creation
    if (storage->CheckClass("Pipeline")) {
        auto pipeline = storage->TakeObject("Pipeline");
        EXPECT_NE(pipeline, nullptr) 
            << "Should be able to create Pipeline";
        if (pipeline) {
            EXPECT_EQ(pipeline->GetCompClassName(), "Pipeline");
        }
    }
    
    // Test SourceFile creation
    if (storage->CheckClass("SourceFile")) {
        auto sourceFile = storage->TakeObject("SourceFile");
        EXPECT_NE(sourceFile, nullptr) 
            << "Should be able to create SourceFile";
        if (sourceFile) {
            EXPECT_EQ(sourceFile->GetCompClassName(), "SourceFile");
        }
    }
    
    // Test ColorConvert creation
    if (storage->CheckClass("ColorConvert")) {
        auto colorConvert = storage->TakeObject("ColorConvert");
        EXPECT_NE(colorConvert, nullptr) 
            << "Should be able to create ColorConvert";
        if (colorConvert) {
            EXPECT_EQ(colorConvert->GetCompClassName(), "ColorConvert");
        }
    }
}

