#pragma once
#include <Luma2D.h>

using namespace Luma2D::Core;

struct LumaEditorState
{
    PlugState plug;
};

void Luma2D_OnCreate();
void Luma2D_OnUpdate();
void Luma2D_OnRender();
void Luma2D_OnRenderUI();
void Luma2D_OnShutdown();
