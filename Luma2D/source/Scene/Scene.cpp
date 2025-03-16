#include "Scene/Scene.h"
#include "Graphics/Shape.h"
#include "Graphics/Sprite.h"

namespace Luma2D
{
    namespace Scene
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
                if (entity->HasComponent<AnimatorComponent>() && entity->HasComponent<SpriteRendererComponent>())
                {
                    auto& src = entity->GetComponent<SpriteRendererComponent>();
                    auto& ac = entity->GetComponent<AnimatorComponent>();
                    Graphics::AnimControllerUpdate(ac.controller, &src.sprite);
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
                    auto& src = entity->GetComponent<ShapeRendererComponent>();
                    src.shape.position = tc.position;
                    src.shape.rotation = tc.rotation;
                    src.shape.scale = tc.scale;

                    Graphics::DrawShape(src.shape, src.hasFill);
                }

                if (entity->HasComponent<SpriteRendererComponent>())
                {
                    auto& src = entity->GetComponent<SpriteRendererComponent>();
                    src.sprite.position = tc.position;
                    src.sprite.rotation = tc.rotation;
                    src.sprite.scale = tc.scale;

                    Graphics::DrawSprite(src.sprite, src.tint);
                }
            }
        }
    }
}
