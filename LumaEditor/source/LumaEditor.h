#pragma once
#include "Panels/SceneHeirarchyPanel.h"
#include "Panels/SceneViewportPanel.h"
#include <Luma2D.h>

using namespace Luma2D::Core;
using namespace Luma2D::Graphics;

struct LumaEditorState
{
    Scene activeScene;
    SceneHeirarchyPanel sceneHeirarchyPanel;
    SceneViewportPanel sceneViewportPanel;
    Texture idleTexture;
    Texture runTexture;
};

void Luma2D_OnCreate();
void Luma2D_OnUpdate();
void Luma2D_OnRender();
void Luma2D_OnRenderUI();
void Luma2D_OnShutdown();
