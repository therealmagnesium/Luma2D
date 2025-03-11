#pragma once
#include <Luma2D.h>

using namespace Luma2D::Core;
using namespace Luma2D::Graphics;

struct LumaEditorState
{
    Shape shape;
    Sprite sprite;
    Animation animation;
    Texture texture;
};

void Luma2D_OnCreate();
void Luma2D_OnUpdate();
void Luma2D_OnRender();
void Luma2D_OnRenderUI();
void Luma2D_OnShutdown();
