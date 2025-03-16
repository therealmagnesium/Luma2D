#pragma once
#include "Core/Base.h"
#include "Graphics/Animation.h"
#include "Graphics/Shape.h"
#include "Graphics/Sprite.h"

#include <raylib.h>

namespace Luma2D
{
    namespace Scene
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

        struct ShapeRendererComponent
        {
            bool isEnabled = false;
            bool hasFill = true;
            Graphics::Shape shape;

            ShapeRendererComponent() = default;
            ShapeRendererComponent(float radius, float lineThickness, u32 numSides, Color color)
            {
                shape = Graphics::CreateShape((Vector2){0.f, 0.f}, 0.f, 1.f, radius, lineThickness, numSides, color);
            }
        };

        struct SpriteRendererComponent
        {
            bool isEnabled = false;
            Color tint = WHITE;
            Graphics::Sprite sprite;

            SpriteRendererComponent() = default;
            SpriteRendererComponent(Texture* texture, Vector2 origin)
            {
                sprite = Graphics::CreateSprite(texture, (Vector2){0.f, 0.f}, 0.f, 1.f, origin);
            }
        };

        struct AnimatorComponent
        {
            bool isEnabled = false;
            Graphics::AnimationController controller;

            AnimatorComponent() = default;
            AnimatorComponent(Graphics::Sprite* sprite, u32 estimatedAnimCount)
            {
                controller = Graphics::CreateAnimationController(sprite, estimatedAnimCount);
            }
        };
    }
}
