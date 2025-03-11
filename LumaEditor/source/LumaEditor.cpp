#include "LumaEditor.h"

#include <Luma2D.h>
#include <raylib.h>
#include <imgui.h>

static LumaEditorState state;

void Luma2D_OnCreate()
{
    state.idleTexture = LoadTexture("assets/Idle.png");
    state.runTexture = LoadTexture("assets/Run.png");

    SetTextureFilter(state.idleTexture, TEXTURE_FILTER_POINT);
    SetTextureFilter(state.runTexture, TEXTURE_FILTER_POINT);

    state.shape.position = (Vector2){400.f, 400.f};
    state.shape.rotation = 0.f;
    state.shape.scale = 1.f;
    state.shape.numSides = 6;
    state.shape.radius = 64.f;
    state.shape.lineThickness = 8.f;
    state.shape.color = BLUE;

    state.sprite = CreateSprite(&state.idleTexture, (Vector2){600.f, 300.f}, 0.f, 6.f, (Vector2){16.f, 16.f});

    state.animController = CreateAnimationController(&state.sprite, 2);

    Animation idleAnimation = CreateAnimation("Idle", 24, 11, 0, AnimationType::Horizontal);
    Animation runAnimation = CreateAnimation("Run", 22, 12, 0, AnimationType::Horizontal);

    AnimControllerAddAnimation(state.animController, idleAnimation, &state.idleTexture);
    AnimControllerAddAnimation(state.animController, runAnimation, &state.runTexture);

    PlayAnimation(state.animController.animations[state.animController.currentAnimationIndex]);

    App->SetClearColor(BLACK);
}

void Luma2D_OnUpdate()
{
    if (IsKeyPressed(KEY_ONE))
        AnimControllerSwitchAnimation(state.animController, 0);

    if (IsKeyPressed(KEY_TWO))
        AnimControllerSwitchAnimation(state.animController, 1);

    AnimControllerUpdate(state.animController);
}

void Luma2D_OnRender()
{
    DrawShape(state.shape, true);
    DrawSprite(state.sprite, WHITE);
}

void Luma2D_OnRenderUI()
{
    DrawFPS(20, 20);
    // DrawText("Hot Reloading", 20, 200, 64, WHITE);

    // ImGui::ShowDemoWindow();
}

void Luma2D_OnShutdown()
{
    UnloadTexture(state.idleTexture);
    UnloadTexture(state.runTexture);
}
