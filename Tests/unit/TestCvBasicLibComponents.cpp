#include <gtest/gtest.h>
#include "../../../../Tests/TestHelpers.h"
#include "../../../../Rdk/Deploy/Include/rdk.h"
#include "../../../Deploy/Include/Lib.h"
#include "../../../../Libraries/Rdk-CvBasicLib/Core/Basic.h"
#include <sstream>

using namespace RDK;
using namespace RDK::TestHelpers;

class CvBasicLibComponentsTest : public ::testing::Test {
protected:
    void SetUp() override {
        InitTestLogging();
        storage = CreateStorageWithLibraries({&RDK::CvBasicLibrary});
        RDK::CvBasicLibrary.Upload(storage.get());
        RDK::CvBasicLibrary.CreateClassSamples(storage.get());
    }

    void TearDown() override {
        storage.reset();
    }

    std::shared_ptr<UStorage> storage;
};

TEST_F(CvBasicLibComponentsTest, RegistersPipelineAndSource) {
    ASSERT_NE(storage, nullptr);
    std::vector<std::string> classes;
    storage->GetClassNameList(classes);
    std::ostringstream oss;
    oss << "Available classes:";
    for (size_t i = 0; i < classes.size(); ++i) {
        if (i < 20) {
            oss << " " << classes[i];
        }
    }
    SCOPED_TRACE(oss.str());

    EXPECT_TRUE(storage->CheckClass("Pipeline")) << "Pipeline must be registered";
    EXPECT_TRUE(storage->CheckClass("SourceFile")) << "SourceFile must be registered";
}

TEST_F(CvBasicLibComponentsTest, CreateSourceComponent) {
    auto component = storage->TakeObject("SourceFile");
    ASSERT_NE(component, nullptr) << "Failed to instantiate SourceFile";
    EXPECT_TRUE(storage->CheckObject(component));
    EXPECT_EQ(component->GetCompClassName(), "SourceFile");

    component->SetName("CvSourceInstance");
    EXPECT_EQ(component->GetName(), "CvSourceInstance");
    // No need to call ReturnObject - shared_ptr will handle cleanup automatically
}

TEST_F(CvBasicLibComponentsTest, CreateProcessingComponent) {
    if (!storage->CheckClass("Crop")) {
        GTEST_SKIP() << "Crop component is not available";
        return;
    }

    auto processor = storage->TakeObject("Crop");
    ASSERT_NE(processor, nullptr);
    EXPECT_TRUE(storage->CheckObject(processor));
    EXPECT_EQ(processor->GetCompClassName(), "Crop");

    processor->SetName("CvProcessor");
    EXPECT_EQ(processor->GetName(), "CvProcessor");
    // No need to call ReturnObject - shared_ptr will handle cleanup automatically
}

TEST_F(CvBasicLibComponentsTest, CreateImageProcessingComponents) {
    // Test Crop component
    if (storage->CheckClass("Crop")) {
        auto crop = storage->TakeObject("Crop");
        ASSERT_NE(crop, nullptr);
        EXPECT_EQ(crop->GetCompClassName(), "Crop");
        crop->SetName("TestCrop");
        EXPECT_EQ(crop->GetName(), "TestCrop");
    }

    // Test ResizeEdges component
    if (storage->CheckClass("ResizeEdges")) {
        auto resize = storage->TakeObject("ResizeEdges");
        ASSERT_NE(resize, nullptr);
        EXPECT_EQ(resize->GetCompClassName(), "ResizeEdges");
        resize->SetName("TestResize");
        EXPECT_EQ(resize->GetName(), "TestResize");
    }

    // Test RotateSimple component
    if (storage->CheckClass("RotateSimple")) {
        auto rotate = storage->TakeObject("RotateSimple");
        ASSERT_NE(rotate, nullptr);
        EXPECT_EQ(rotate->GetCompClassName(), "RotateSimple");
        rotate->SetName("TestRotate");
        EXPECT_EQ(rotate->GetName(), "TestRotate");
    }

    // Test ColorConvert component
    if (storage->CheckClass("ColorConvert")) {
        auto colorConvert = storage->TakeObject("ColorConvert");
        ASSERT_NE(colorConvert, nullptr);
        EXPECT_EQ(colorConvert->GetCompClassName(), "ColorConvert");
        colorConvert->SetName("TestColorConvert");
        EXPECT_EQ(colorConvert->GetName(), "TestColorConvert");
    }
}

TEST_F(CvBasicLibComponentsTest, CreateDetectionComponents) {
    // Test BackgroundAvg component
    if (storage->CheckClass("BackgroundAvg")) {
        auto background = storage->TakeObject("BackgroundAvg");
        ASSERT_NE(background, nullptr);
        EXPECT_EQ(background->GetCompClassName(), "BackgroundAvg");
        background->SetName("TestBackground");
        EXPECT_EQ(background->GetName(), "TestBackground");
    }

    // Test TBinarizationSimple component
    if (storage->CheckClass("TBinarizationSimple")) {
        auto binarization = storage->TakeObject("TBinarizationSimple");
        ASSERT_NE(binarization, nullptr);
        EXPECT_EQ(binarization->GetCompClassName(), "TBinarizationSimple");
        binarization->SetName("TestBinarization");
        EXPECT_EQ(binarization->GetName(), "TestBinarization");
    }

    // Test TLabelingSimple component
    if (storage->CheckClass("TLabelingSimple")) {
        auto labeling = storage->TakeObject("TLabelingSimple");
        ASSERT_NE(labeling, nullptr);
        EXPECT_EQ(labeling->GetCompClassName(), "TLabelingSimple");
        labeling->SetName("TestLabeling");
        EXPECT_EQ(labeling->GetName(), "TestLabeling");
    }
}

TEST_F(CvBasicLibComponentsTest, CreateClassificationComponents) {
    // Test UCRPerseptron component
    if (storage->CheckClass("UCRPerseptron")) {
        auto perceptron = storage->TakeObject("UCRPerseptron");
        ASSERT_NE(perceptron, nullptr);
        EXPECT_EQ(perceptron->GetCompClassName(), "UCRPerseptron");
        perceptron->SetName("TestPerceptron");
        EXPECT_EQ(perceptron->GetName(), "TestPerceptron");
    }

    // Test UCRDirectCompare component
    if (storage->CheckClass("UCRDirectCompare")) {
        auto directCompare = storage->TakeObject("UCRDirectCompare");
        ASSERT_NE(directCompare, nullptr);
        EXPECT_EQ(directCompare->GetCompClassName(), "UCRDirectCompare");
        directCompare->SetName("TestDirectCompare");
        EXPECT_EQ(directCompare->GetName(), "TestDirectCompare");
    }

    // Test UCRDistance component
    if (storage->CheckClass("UCRDistance")) {
        auto distance = storage->TakeObject("UCRDistance");
        ASSERT_NE(distance, nullptr);
        EXPECT_EQ(distance->GetCompClassName(), "UCRDistance");
        distance->SetName("TestDistance");
        EXPECT_EQ(distance->GetName(), "TestDistance");
    }
}

TEST_F(CvBasicLibComponentsTest, CreatePipelineComponent) {
    if (!storage->CheckClass("Pipeline")) {
        GTEST_SKIP() << "Pipeline component is not available";
        return;
    }

    auto pipeline = storage->TakeObject("Pipeline");
    ASSERT_NE(pipeline, nullptr);
    EXPECT_EQ(pipeline->GetCompClassName(), "Pipeline");
    pipeline->SetName("TestPipeline");
    EXPECT_EQ(pipeline->GetName(), "TestPipeline");
    // No need to call ReturnObject - shared_ptr will handle cleanup automatically
}

