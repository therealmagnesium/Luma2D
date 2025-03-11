#include "Graphics/Sprite.h"
#include "Core/Base.h"
#include <raylib.h>

namespace Luma2D
{
    namespace Graphics
    {
        Sprite CreateSprite(Texture* texture, Vector2 position, float rotation, float scale, Vector2 origin)
        {
            Sprite sprite;
            sprite.texture = texture;
            sprite.position = position;
            sprite.rotation = rotation;
            sprite.scale = scale;
            sprite.origin = origin;

            return sprite;
        }

        void DrawSprite(Sprite& sprite, const Color& tint)
        {
            if (sprite.texture == NULL)
            {
                sprite.crop = (Rectangle){0.f, 0.f, 32.f, 32.f};

                Vector2 size;
                size.x = 64.f * sprite.scale;
                size.y = 64.f * sprite.scale;
                DrawRectangleV(sprite.position, size, tint);

                return;
            }

            if (sprite.crop.width == 0.f || sprite.crop.height == 0.f)
            {
                sprite.crop.width = sprite.texture->width;
                sprite.crop.height = sprite.texture->height;
            }

            Rectangle dest;
            dest.x = sprite.position.x;
            dest.y = sprite.position.y;
            dest.width = sprite.crop.width * sprite.scale;
            dest.height = sprite.crop.height * sprite.scale;

            DrawTexturePro(*sprite.texture, sprite.crop, dest, sprite.origin, sprite.rotation, tint);
        }
    }
}
