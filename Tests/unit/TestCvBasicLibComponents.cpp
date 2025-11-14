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

// Test additional image processing components
TEST_F(CvBasicLibComponentsTest, CreateAdditionalImageProcessingComponents) {
    // Test Reduce component
    if (storage->CheckClass("Reduce")) {
        auto reduce = storage->TakeObject("Reduce");
        ASSERT_NE(reduce, nullptr);
        EXPECT_EQ(reduce->GetCompClassName(), "Reduce");
        reduce->SetName("TestReduce");
        EXPECT_EQ(reduce->GetName(), "TestReduce");
    }

    // Test FlipImage component
    if (storage->CheckClass("UBAFlipImageSimple")) {
        auto flip = storage->TakeObject("UBAFlipImageSimple");
        ASSERT_NE(flip, nullptr);
        EXPECT_EQ(flip->GetCompClassName(), "UBAFlipImageSimple");
        flip->SetName("TestFlipImage");
        EXPECT_EQ(flip->GetName(), "TestFlipImage");
    }

    // Test Model component
    if (storage->CheckClass("Model")) {
        auto model = storage->TakeObject("Model");
        ASSERT_NE(model, nullptr);
        EXPECT_EQ(model->GetCompClassName(), "Model");
        model->SetName("TestModel");
        EXPECT_EQ(model->GetName(), "TestModel");
    }

    // Test ParallelPipeline component
    if (storage->CheckClass("ParallelPipeline")) {
        auto parallelPipeline = storage->TakeObject("ParallelPipeline");
        ASSERT_NE(parallelPipeline, nullptr);
        EXPECT_EQ(parallelPipeline->GetCompClassName(), "ParallelPipeline");
        parallelPipeline->SetName("TestParallelPipeline");
        EXPECT_EQ(parallelPipeline->GetName(), "TestParallelPipeline");
    }
}

// Test additional detection components
TEST_F(CvBasicLibComponentsTest, CreateAdditionalDetectionComponents) {
    // Test DifferenceFrame component
    if (storage->CheckClass("DifferenceFrame")) {
        auto diffFrame = storage->TakeObject("DifferenceFrame");
        ASSERT_NE(diffFrame, nullptr);
        EXPECT_EQ(diffFrame->GetCompClassName(), "DifferenceFrame");
        diffFrame->SetName("TestDifferenceFrame");
        EXPECT_EQ(diffFrame->GetName(), "TestDifferenceFrame");
    }

    // Test MovingDetector component
    if (storage->CheckClass("MovingDetector")) {
        auto movingDetector = storage->TakeObject("MovingDetector");
        ASSERT_NE(movingDetector, nullptr);
        EXPECT_EQ(movingDetector->GetCompClassName(), "MovingDetector");
        movingDetector->SetName("TestMovingDetector");
        EXPECT_EQ(movingDetector->GetName(), "TestMovingDetector");
    }

    // Test ObjectDetector component
    if (storage->CheckClass("ObjectDetector")) {
        auto objectDetector = storage->TakeObject("ObjectDetector");
        ASSERT_NE(objectDetector, nullptr);
        EXPECT_EQ(objectDetector->GetCompClassName(), "ObjectDetector");
        objectDetector->SetName("TestObjectDetector");
        EXPECT_EQ(objectDetector->GetName(), "TestObjectDetector");
    }
}

// Test classification base components
TEST_F(CvBasicLibComponentsTest, CreateClassificationBaseComponents) {
    // Test UClassifierBase component
    if (storage->CheckClass("UClassifierBase")) {
        auto classifierBase = storage->TakeObject("UClassifierBase");
        ASSERT_NE(classifierBase, nullptr);
        EXPECT_EQ(classifierBase->GetCompClassName(), "UClassifierBase");
        classifierBase->SetName("TestClassifierBase");
        EXPECT_EQ(classifierBase->GetName(), "TestClassifierBase");
    }

    // Test UDetectorBase component
    if (storage->CheckClass("UDetectorBase")) {
        auto detectorBase = storage->TakeObject("UDetectorBase");
        ASSERT_NE(detectorBase, nullptr);
        EXPECT_EQ(detectorBase->GetCompClassName(), "UDetectorBase");
        detectorBase->SetName("TestDetectorBase");
        EXPECT_EQ(detectorBase->GetName(), "TestDetectorBase");
    }

    // Test USegmentatorBase component
    if (storage->CheckClass("USegmentatorBase")) {
        auto segmentatorBase = storage->TakeObject("USegmentatorBase");
        ASSERT_NE(segmentatorBase, nullptr);
        EXPECT_EQ(segmentatorBase->GetCompClassName(), "USegmentatorBase");
        segmentatorBase->SetName("TestSegmentatorBase");
        EXPECT_EQ(segmentatorBase->GetName(), "TestSegmentatorBase");
    }
}

// Test additional source components
TEST_F(CvBasicLibComponentsTest, CreateAdditionalSourceComponents) {
    // Test Source component
    if (storage->CheckClass("Source")) {
        auto source = storage->TakeObject("Source");
        ASSERT_NE(source, nullptr);
        EXPECT_EQ(source->GetCompClassName(), "Source");
        source->SetName("TestSource");
        EXPECT_EQ(source->GetName(), "TestSource");
    }

    // Test SourceMultiFile component
    if (storage->CheckClass("SourceMultiFile")) {
        auto sourceMultiFile = storage->TakeObject("SourceMultiFile");
        ASSERT_NE(sourceMultiFile, nullptr);
        EXPECT_EQ(sourceMultiFile->GetCompClassName(), "SourceMultiFile");
        sourceMultiFile->SetName("TestSourceMultiFile");
        EXPECT_EQ(sourceMultiFile->GetName(), "TestSourceMultiFile");
    }

    // Test Receiver component
    if (storage->CheckClass("Receiver")) {
        auto receiver = storage->TakeObject("Receiver");
        ASSERT_NE(receiver, nullptr);
        EXPECT_EQ(receiver->GetCompClassName(), "Receiver");
        receiver->SetName("TestReceiver");
        EXPECT_EQ(receiver->GetName(), "TestReceiver");
    }
}

