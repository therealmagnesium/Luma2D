#include "LumaEditor.h"

#include <Luma2D.h>
#include <raylib.h>
#include <imgui.h>

using namespace Luma2D::Core;
using namespace Luma2D::Graphics;

static LumaEditorState state;
static std::shared_ptr<Entity> shape = NULL;
static std::shared_ptr<Entity> sprite = NULL;

void Luma2D_OnCreate()
{
    state.idleTexture = LoadTexture("assets/Idle.png");
    state.runTexture = LoadTexture("assets/Run.png");

    SetTextureFilter(state.idleTexture, TEXTURE_FILTER_POINT);
    SetTextureFilter(state.runTexture, TEXTURE_FILTER_POINT);

    shape = state.activeScene.AddEntity("Shape");
    auto& shapeTC = shape->GetComponent<TransformComponent>();
    auto& shapeSC = shape->AddComponent<ShapeRendererComponent>(64.f, 8.f, 6, BLUE);
    shapeTC.position = (Vector2){400.f, 400.f};
    shapeTC.scale = 4.f;
    shapeSC.hasFill = false;

    sprite = state.activeScene.AddEntity("Sprite");
    auto& tc = sprite->GetComponent<TransformComponent>();
    auto& sc = sprite->AddComponent<SpriteRendererComponent>((Texture*)NULL, (Vector2){16.f, 16.f});
    auto& ac = sprite->AddComponent<AnimatorComponent>(&sc.sprite, 2);
    tc.position = (Vector2){800.f, 200.f};
    tc.scale = 4.f;

    Animation idleAnimation = CreateAnimation("Idle", 24, 11, 0, AnimationType::Horizontal);
    Animation runAnimation = CreateAnimation("Run", 22, 12, 0, AnimationType::Horizontal);

    AnimControllerAddAnimation(ac.controller, idleAnimation, &state.idleTexture);
    AnimControllerAddAnimation(ac.controller, runAnimation, &state.runTexture);
    AnimControllerSwitchAnimation(ac.controller, 0);

    App->SetClearColor(BLACK);
}

void Luma2D_OnUpdate()
{
    state.activeScene.Update();

    auto& ac = sprite->GetComponent<AnimatorComponent>();

    if (IsKeyPressed(KEY_ONE))
        AnimControllerSwitchAnimation(ac.controller, 0);

    if (IsKeyPressed(KEY_TWO))
        AnimControllerSwitchAnimation(ac.controller, 1);
}

void Luma2D_OnRender()
{
    state.activeScene.Draw();
}

void Luma2D_OnRenderUI()
{
    DrawFPS(20, 20);
    DrawText("Hot Reloading", 20, 200, 64, WHITE);

    // ImGui::ShowDemoWindow();
}

void Luma2D_OnShutdown()
{
    UnloadTexture(state.idleTexture);
    UnloadTexture(state.runTexture);
}
