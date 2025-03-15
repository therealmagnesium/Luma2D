#include "Core/Scene.h"
#include "Graphics/Shape.h"
#include "Graphics/Sprite.h"

namespace Luma2D
{
    namespace Core
    {
        std::shared_ptr<Entity> Scene::AddEntity(const char* tag)
        {
            return m_entityManager.AddEntity(tag);
        }

        void Scene::DestroyEntity(std::shared_ptr<Entity>& entity)
        {
            m_entityManager.DestroyEntity(entity);
        }

        void Scene::Update()
        {
            m_entityManager.Update();

            for (auto& entity : m_entityManager.GetEntities())
            {
                if (entity->HasComponent<AnimatorComponent>())
                {
                    auto& ac = entity->GetComponent<AnimatorComponent>();
                    Graphics::AnimControllerUpdate(ac.controller);
                }
            }
        }

        void Scene::Draw()
        {
            for (auto& entity : m_entityManager.GetEntities())
            {
                auto& tc = entity->GetComponent<TransformComponent>();

                if (entity->HasComponent<ShapeRendererComponent>())
                {
                    auto& sc = entity->GetComponent<ShapeRendererComponent>();
                    sc.shape.position = tc.position;
                    sc.shape.rotation = tc.rotation;
                    sc.shape.scale = tc.scale;

                    Graphics::DrawShape(sc.shape, sc.hasFill);
                }

                if (entity->HasComponent<SpriteRendererComponent>())
                {
                    auto& sc = entity->GetComponent<SpriteRendererComponent>();
                    sc.sprite.position = tc.position;
                    sc.sprite.rotation = tc.rotation;
                    sc.sprite.scale = tc.scale;

                    Graphics::DrawSprite(sc.sprite, sc.tint);
                }
            }
        }
    }
}
