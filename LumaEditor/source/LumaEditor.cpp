#include "LumaEditor.h"

#include <Luma2D.h>
#include <raylib.h>
#include <imgui.h>

using namespace Luma2D::Core;
using namespace Luma2D::Graphics;
using namespace Luma2D::Scene;

static LumaEditorState state;
static std::shared_ptr<Entity> shape = NULL;
static std::shared_ptr<Entity> sprite = NULL;

void Luma2D_OnCreate()
{
    Assets->AddTexture("Player Idle", "assets/Idle.png", TEXTURE_FILTER_POINT);
    Assets->AddTexture("Player Run", "assets/Run.png", TEXTURE_FILTER_POINT);

    shape = state.activeScene.AddEntity("Shape");
    auto& shapeTC = shape->GetComponent<TransformComponent>();
    auto& shapeSC = shape->AddComponent<ShapeRendererComponent>(64.f, 8.f, 6, BLUE);
    shapeTC.position = (Vector2){400.f, 400.f};
    shapeTC.scale = 4.f;
    shapeSC.hasFill = false;

    sprite = state.activeScene.AddEntity("Sprite");
    auto& tc = sprite->GetComponent<TransformComponent>();
    auto& sc = sprite->AddComponent<SpriteRendererComponent>((Texture*)NULL, (Vector2){64.f, 64.f});
    auto& ac = sprite->AddComponent<AnimatorComponent>();
    tc.position = (Vector2){800.f, 200.f};
    tc.scale = 4.f;

    Animation idleAnimation = CreateAnimation("Idle", 24, 11, 0, AnimationType::Horizontal);
    Animation runAnimation = CreateAnimation("Run", 22, 12, 0, AnimationType::Horizontal);

    AnimControllerAddAnimation(ac.controller, idleAnimation, Assets->GetTexture("Player Idle"));
    AnimControllerAddAnimation(ac.controller, runAnimation, Assets->GetTexture("Player Run"));
    AnimControllerSwitchAnimation(ac.controller, "Idle");

    state.sceneHeirarchyPanel.SetContext(&state.activeScene);
    state.sceneViewportPanel.SetContext(&state.activeScene);

    App->SetClearColor((Color){15, 15, 15, 255});
}

void Luma2D_OnUpdate()
{
    state.activeScene.Update();
}

void Luma2D_OnRender()
{
    state.activeScene.Draw();
}

void Luma2D_OnRenderUI()
{
    DrawFPS(20, 20);

    ImGui::DockSpaceOverViewport();
    ImGui::ShowDemoWindow();

    state.sceneHeirarchyPanel.Display();
    state.sceneViewportPanel.Display();
}

void Luma2D_OnShutdown()
{
}
