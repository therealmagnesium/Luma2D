#pragma once
#include "Core/EntityManager.h"

namespace Luma2D
{
    namespace Core
    {
        class Scene
        {
        public:
            Scene() = default;

            std::shared_ptr<Entity> AddEntity(const char* tag);
            void DestroyEntity(std::shared_ptr<Entity>& entity);
            void Update();
            void Draw();

        private:
            EntityManager m_entityManager;
        };
    }
}
