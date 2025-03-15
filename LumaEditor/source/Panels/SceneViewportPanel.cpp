#include "SceneViewportPanel.h"

#include <Luma2D.h>
#include <raylib.h>
#include <imgui.h>

using namespace Luma2D::Core;
using namespace Luma2D::Graphics;

void SceneViewportPanel::SetContext(Scene* scene)
{
    m_context = scene;
}

void SceneViewportPanel::Display()
{
    ASSERT_MSG(m_context != NULL, "Cannot display scene viewport panel with null context!");

    RenderTexture& framebuffer = App->GetFramebuffer();
    u64 framebufferID = framebuffer.texture.id;

    ImGui::Begin("Scene Viewport", NULL, ImGuiWindowFlags_NoScrollbar);
    {
        ImVec2 aspectSize = GetLargestViewportSize();
        ImVec2 windowPosition = GetCenteredViewportPosition(aspectSize);

        ImGui::SetCursorPos(windowPosition);
        ImGui::Image(framebufferID, aspectSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();
}

ImVec2 SceneViewportPanel::GetLargestViewportSize()
{
    ApplicationSpecification& appInfo = App->GetInfo();
    ImVec2 windowSize = ImGui::GetContentRegionAvail();

    float aspectRatio = appInfo.windowWidth / (float)appInfo.windowHeight;
    ImVec2 aspectSize = ImVec2(windowSize.x, windowSize.x / aspectRatio);

    if (aspectSize.y > windowSize.y)
    {
        aspectSize.y = windowSize.y;
        aspectSize.x = aspectSize.y * aspectRatio;
    }

    return aspectSize;
}

ImVec2 SceneViewportPanel::GetCenteredViewportPosition(ImVec2 aspectSize)
{
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    ImVec2 offset(10.f, 35.f);

    ImVec2 viewportPosition;
    viewportPosition.x = (windowSize.x / 2.f) - (aspectSize.x / 2.f) + offset.x;
    viewportPosition.y = (windowSize.y / 2.f) - (aspectSize.y / 2.f) + offset.y;

    return viewportPosition;
}
