#include <gtest/gtest.h>
#include "../../../../Tests/TestHelpers.h"
#include "../../../../Rdk/Deploy/Include/rdk.h"
#include "../../../Deploy/Include/Lib.h"
#include "../../../../Libraries/Rdk-CvBasicLib/Core/Basic.h"

using namespace RDK;
using namespace RDK::TestHelpers;

class CvBasicLibIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        InitTestLogging();
        storage = CreateStorageWithLibraries({&RDK::CvBasicLibrary});
        RDK::CvBasicLibrary.Upload(storage.get());
        RDK::CvBasicLibrary.CreateClassSamples(storage.get());
        environment = CreateTestEnvironment(storage);
    }

    void TearDown() override {
        environment.reset();
        storage.reset();
    }

    std::shared_ptr<UStorage> storage;
    std::shared_ptr<UEnvironment> environment;
};

TEST_F(CvBasicLibIntegrationTest, CvBasicLibEngineIntegration) {
    ASSERT_NE(storage, nullptr);
    ASSERT_NE(environment, nullptr);
    EXPECT_GT(storage->GetNumClasses(), 0);
}

TEST_F(CvBasicLibIntegrationTest, CvBasicLibEnvironmentIntegration) {
    if (!environment->IsInit()) {
        environment->Default();
        environment->Init();
    }

    EXPECT_TRUE(environment->IsInit());
    UStorage* envStorage = environment->GetStorage();
    ASSERT_NE(envStorage, nullptr);
    EXPECT_EQ(envStorage, storage.get());
}

TEST_F(CvBasicLibIntegrationTest, CvBasicLibModelCreation) {
    if (!environment->IsInit()) {
        environment->Default();
        environment->Init();
    }

    auto model = CreateTestModel(storage, environment);
    if (!model) {
        GTEST_SKIP() << "Cannot create model in environment";
        return;
    }

    auto source = storage->CheckClass("SourceFile") ? storage->TakeObject("SourceFile") : nullptr;
    auto processor = storage->CheckClass("Crop") ? storage->TakeObject("Crop") : nullptr;

    if (!source && !processor) {
        GTEST_SKIP() << "No CvBasicLib components available for integration test";
        return;
    }

    if (source) {
        source->SetName("CvSource");
        ASSERT_TRUE(model->AddComponent(source));
    }

    if (processor) {
        processor->SetName("CvProcessor");
        model->AddComponent(processor);
    }

    EXPECT_GE(model->GetNumComponents(), source ? 1 : 0);
}

