#include "LumaEditor.h"

#include <Luma2D.h>
#include <raylib.h>

static LumaEditorState state;

void Luma2D_OnCreate()
{
}

void Luma2D_OnUpdate()
{
    App->SetClearColor(BLACK);
}

void Luma2D_OnRender()
{
}

void Luma2D_OnRenderUI()
{
    DrawFPS(20, 20);
    DrawText("Hot Reloading", 20, 200, 64, WHITE);
}

void Luma2D_OnShutdown()
{
}
