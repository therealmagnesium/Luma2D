#include "LumaEditor.h"

#include <Luma2D.h>
#include <raylib.h>
#include <imgui.h>

static LumaEditorState state;

void Luma2D_OnCreate()
{
    state.texture = LoadTexture("assets/Cherries.png");
    SetTextureFilter(state.texture, TEXTURE_FILTER_POINT);

    state.shape.position = (Vector2){400.f, 400.f};
    state.shape.rotation = 0.f;
    state.shape.scale = 1.f;
    state.shape.numSides = 6;
    state.shape.radius = 64.f;
    state.shape.lineThickness = 8.f;
    state.shape.color = BLUE;

    state.sprite = CreateSprite(&state.texture, (Vector2){600.f, 300.f}, 0.f, 6.f);

    state.animation = CreateAnimation("Cherry", true, 24, 17, 0, AnimationType::Horizontal);
    PlayAnimation(state.animation);

    App->SetClearColor(BLACK);
}

void Luma2D_OnUpdate()
{
    UpdateAnimation(state.animation, state.sprite);
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
    UnloadTexture(state.texture);
}
