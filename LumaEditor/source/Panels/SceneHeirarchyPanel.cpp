#include "SceneHeirarchyPanel.h"

#include <Luma2D.h>
#include <imgui.h>
#include <memory>

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
}
