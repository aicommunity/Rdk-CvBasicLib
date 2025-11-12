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
    storage->ReturnObject(component);
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
    storage->ReturnObject(processor);
}

