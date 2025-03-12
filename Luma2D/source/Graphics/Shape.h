#pragma once
#include "Core/Base.h"
#include <raylib.h>

namespace Luma2D
{
    namespace Graphics
    {
        struct Shape
        {
            Vector2 position;
            float rotation;
            float scale;
            float radius;
            float lineThickness;
            u32 numSides;
            Color color;
        };

        Shape CreateShape(Vector2 position, float rotation, float scale, float radius, float lineThickness,
                          u32 numSides, Color color);
        void DrawShape(Shape& shape, bool hasFill = true);
    }
}
