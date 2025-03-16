#include "SceneHeirarchyPanel.h"

#include <Luma2D.h>
#include <imgui.h>
#include <rlImGuiColors.h>
#include <memory>

using namespace Luma2D::Core;
using namespace Luma2D::Graphics;
using namespace Luma2D::Scene;

template <typename T, typename UIFunc>
static void DrawComponent(const char* name, std::shared_ptr<Entity>& entity, UIFunc uiFunction)
{
    const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
                                             ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_AllowItemOverlap;

    if (entity->HasComponent<T>())
    {
        auto& component = entity->GetComponent<T>();
        ImVec2 availableRegion = ImGui::GetContentRegionAvail();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.f, 4.f));
        float lineHeight = ImGui::GetFont()->FontSize + ImGui::GetStyle().FramePadding.y * 2.f;
        ImGui::PopStyleVar();

        bool open = ImGui::CollapsingHeader(name);
        ImGui::SameLine(availableRegion.x - lineHeight * .5f);

        if (ImGui::Button("+", ImVec2(20.f, 20.f)))
            ImGui::OpenPopup("Component Settings");

        bool removeComponent = false;
        if (ImGui::BeginPopup("Component Settings"))
        {
            if (ImGui::MenuItem("Remove component"))
                removeComponent = true;

            ImGui::EndPopup();
        }

        if (open)
            uiFunction(component);

        if (removeComponent)
            entity->RemoveComponent<T>();
    }
}

void SceneHeirarchyPanel::SetContext(Scene* scene)
{
    m_context = scene;
}

void SceneHeirarchyPanel::Display()
{
    ASSERT_MSG(m_context != NULL, "Cannot display scene heirarchy panel with null context!");

    ImGui::Begin("Scene Heirarchy Panel");
    {
        for (auto& entity : m_context->GetEntities())
            this->DrawEntityNode(entity);

        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            m_selectionContext = NULL;

        if (m_selectionContext == NULL)
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    m_context->AddEntity("Entity");

                ImGui::EndPopup();
            }
        }
    }
    ImGui::End();

    ImGui::Begin("Properties Panel");
    {
        if (m_selectionContext != NULL)
            this->DrawComponents(m_selectionContext);
    }
    ImGui::End();
}

void SceneHeirarchyPanel::DrawEntityNode(std::shared_ptr<Entity>& entity)
{
    ImGuiTreeNodeFlags flags = ((entity == m_selectionContext) ? ImGuiTreeNodeFlags_Selected : 0) |
                               ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;
    bool isOpen = ImGui::TreeNodeEx((void*)entity->GetID(), flags, "%s", entity->GetTag());

    if (ImGui::IsItemClicked())
        m_selectionContext = entity;

    bool entityDeleted = false;
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Delete Entity"))
            entityDeleted = true;

        ImGui::EndPopup();
    }

    if (isOpen)
        ImGui::TreePop();

    if (entityDeleted)
    {
        m_context->DestroyEntity(m_selectionContext);
        m_selectionContext = NULL;
    }
}

void SceneHeirarchyPanel::DrawComponents(std::shared_ptr<Entity>& entity)
{
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, entity->GetTag(), sizeof(buffer));

    if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
        entity->SetTag(buffer);

    ImGui::SameLine();
    ImGui::PushItemWidth(-1.f);

    if (ImGui::Button("Add Component"))
        ImGui::OpenPopup("Add Component");

    if (ImGui::BeginPopup("Add Component"))
    {
        if (ImGui::MenuItem("Transform"))
        {
            m_selectionContext->AddComponent<TransformComponent>();
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::MenuItem("Shape"))
        {
            m_selectionContext->AddComponent<ShapeRendererComponent>();
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::MenuItem("Sprite"))
        {
            m_selectionContext->AddComponent<SpriteRendererComponent>();
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::MenuItem("Animator"))
        {
            m_selectionContext->AddComponent<AnimatorComponent>();
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    ImGui::PopItemWidth();

    DrawComponent<TransformComponent>("Transform", entity, [&](TransformComponent& component) {
        ImGui::DragFloat2("Position", &component.position.x, 0.1f);
        ImGui::DragFloat("Rotation", &component.rotation, 0.1f);
        ImGui::DragFloat("Scale", &component.scale, 0.1f);
    });

    DrawComponent<ShapeRendererComponent>("Shape Renderer", entity, [&](ShapeRendererComponent& component) {
        ImVec4 shapeColor = rlImGuiColors::Convert(component.shape.color);

        ImGui::Checkbox("Has Fill?", &component.hasFill);
        ImGui::DragFloat("Radius", &component.shape.radius);
        ImGui::DragFloat("Border Thickness", &component.shape.lineThickness);
        ImGui::DragInt("Edge Count", (s32*)&component.shape.numSides, 0.5f, 3, 32);
        ImGui::ColorEdit3("Color", &shapeColor.x);

        component.shape.color = rlImGuiColors::Convert(shapeColor);
    });

    DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [&](SpriteRendererComponent& component) {
        ImVec4 tint = rlImGuiColors::Convert(component.tint);
        std::vector<std::string> textureNames = Assets->GetAllTextureNames();
        std::string textureNamePreview = Assets->GetTextureName(component.sprite.texture);

        if (ImGui::BeginCombo("Texture", textureNamePreview.c_str()))
        {
            for (u32 i = 0; i < textureNames.size(); i++)
            {
                if (ImGui::Selectable(textureNames[i].c_str()))
                {
                    textureNamePreview = textureNames[i];
                    component.sprite.texture = Assets->GetTexture(textureNamePreview.c_str());
                    break;
                }
            }
            ImGui::EndCombo();
        }

        ImGui::DragFloat2("Origin", &component.sprite.origin.x);
        ImGui::DragFloat4("Crop", &component.sprite.crop.x);
        ImGui::ColorEdit3("Tint", &tint.x);

        component.tint = rlImGuiColors::Convert(tint);
    });

    DrawComponent<AnimatorComponent>("Animator", entity, [&](AnimatorComponent& component) {
        std::string previousAnimIndex = component.controller.currentAnimationIndex;

        if (ImGui::BeginCombo("Animations", previousAnimIndex.c_str()))
        {
            for (auto& [name, animation] : component.controller.animations)
            {
                if (ImGui::Selectable(name.c_str()))
                {
                    AnimControllerSwitchAnimation(component.controller, name.c_str());
                    break;
                }
            }

            ImGui::EndCombo();
        }
    });
}
