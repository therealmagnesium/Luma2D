#pragma once
#include "Core/Base.h"
#include <raylib.h>

namespace Luma2D
{
    namespace Core
    {
        struct TransformComponent
        {
            bool isEnabled = false;
            Vector2 position;
            float rotation;
            float scale;

            TransformComponent()
            {
                position = (Vector2){0.f, 0.f};
                rotation = 0.f;
                scale = 0.f;
            }

            TransformComponent(Vector2 position, float rotation, float scale)
            {
                this->position = position;
                this->rotation = rotation;
                this->scale = scale;
            }
        };
    }
}
