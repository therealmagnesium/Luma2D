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

    state.idleAnimation = CreateAnimation("Idle", true, 24, 11, 0, AnimationType::Horizontal);
    state.runAnimation = CreateAnimation("Run", false, 20, 12, 0, AnimationType::Horizontal);

    PlayAnimation(state.idleAnimation);

    App->SetClearColor(BLACK);
}

void Luma2D_OnUpdate()
{
    if (IsKeyPressed(KEY_ONE))
    {
        if (state.idleAnimation.isPlaying)
        {
            StopAnimation(state.idleAnimation);
            PlayAnimation(state.runAnimation);
        }
        else
        {
            StopAnimation(state.runAnimation);
            PlayAnimation(state.idleAnimation);
        }
    }

    if (state.idleAnimation.isPlaying)
        UpdateAnimation(state.idleAnimation, state.sprite, &state.idleTexture);
    else
        UpdateAnimation(state.runAnimation, state.sprite, &state.runTexture);
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
