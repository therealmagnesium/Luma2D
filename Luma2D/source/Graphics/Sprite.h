#pragma once
#include "Core/Base.h"
#include <raylib.h>

namespace Luma2D
{
    namespace Graphics
    {
        struct Sprite
        {
            Vector2 position;
            float rotation;
            float scale;
            Vector2 origin;
            Rectangle crop;
            Texture* texture = NULL;
        };

        Sprite CreateSprite(Texture* texture, Vector2 position, float rotation, float scale);
        void DrawSprite(Sprite& sprite, const Color& tint);
    }
}
