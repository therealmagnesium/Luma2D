#pragma once
#include <Luma2D.h>
#include <imgui.h>

using namespace Luma2D::Core;
using namespace Luma2D::Graphics;

class SceneViewportPanel
{
public:
    void SetContext(Scene* scene);
    void Display();

private:
    ImVec2 GetLargestViewportSize();
    ImVec2 GetCenteredViewportPosition(ImVec2 aspectSize);

private:
    Scene* m_context = NULL;
};
