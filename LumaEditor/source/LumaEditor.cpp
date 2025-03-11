#include "LumaEditor.h"

#include <Luma2D.h>
#include <raylib.h>
#include <imgui.h>

static LumaEditorState state;

void Luma2D_OnCreate()
{
    state.shape.position = (Vector2){400.f, 400.f};
    state.shape.rotation = 0.f;
    state.shape.scale = 1.f;
    state.shape.numSides = 6;
    state.shape.radius = 64.f;
    state.shape.lineThickness = 12.f;
    state.shape.color = BLUE;
}

void Luma2D_OnUpdate()
{
    App->SetClearColor(BLACK);
}

void Luma2D_OnRender()
{
    DrawShape(state.shape, true);
}

void Luma2D_OnRenderUI()
{
    DrawFPS(20, 20);
    DrawText("Hot Reloading", 20, 200, 64, WHITE);

    // ImGui::ShowDemoWindow();
}

void Luma2D_OnShutdown()
{
}
