#pragma once
#include <Luma2D.h>

using namespace Luma2D::Core;

class LumaEditor : public Application
{
public:
    LumaEditor(const ApplicationSpecification& appInfo) : Application(appInfo) {}
    ~LumaEditor() = default;

    void OnCreate() override {}
    void OnUpdate() override {}

private:
};
