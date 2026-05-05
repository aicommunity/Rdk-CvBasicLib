#include "../../../../Rdk/GUI/Qt/UComponentFormRegistry.h"
#include "../../../../Rdk/GUI/Qt/UGenericComponentControllerWidget.h"

namespace
{
UComponentFormDescriptor MakeCvDescriptor(const QString& id, const QString& title)
{
    UComponentFormDescriptor descriptor;
    descriptor.formId = id;
    descriptor.title = title;
    descriptor.singleInstance = true;
    descriptor.factory = [id, title](RDK::UApplication* app) -> UVisualControllerWidget*
    {
        return new UGenericComponentControllerWidget(id, title, nullptr, app);
    };
    return descriptor;
}
}

void RegisterCvBasicLibComponentGuiForms()
{
    UComponentFormRegistry& registry = UComponentFormRegistry::instance();
    registry.registerFormFactory("NCvImageSource", MakeCvDescriptor("cv.image.source", "CvBasicLib: Image Source"));
}
