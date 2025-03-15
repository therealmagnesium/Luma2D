#pragma once
#include <Luma2D.h>
#include <memory>

using namespace Luma2D::Core;
using namespace Luma2D::Graphics;

class SceneHeirarchyPanel
{
public:
    void SetContext(Scene* scene);
    void Display();

private:
    void DrawEntityNode(std::shared_ptr<Entity>& entity);
    void DrawComponents(std::shared_ptr<Entity>& entity);

private:
    Scene* m_context = NULL;
    std::shared_ptr<Entity> m_selectionContext = NULL;
};
