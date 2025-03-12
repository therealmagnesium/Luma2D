#include "Graphics/Shape.h"
#include "Core/Base.h"
#include <raylib.h>

namespace Luma2D
{
    namespace Graphics
    {
        Shape CreateShape(Vector2 position, float rotation, float scale, float radius, float lineThickness,
                          u32 numSides, Color color)
        {
            Shape shape;
            shape.position = position;
            shape.rotation = rotation;
            shape.scale = scale;
            shape.radius = radius;
            shape.lineThickness = lineThickness;
            shape.numSides = numSides;
            shape.color = color;

            return shape;
        }

        void DrawShape(Shape& shape, bool hasFill)
        {
            if (shape.numSides > 32)
                shape.numSides = 32;

            if (hasFill)
                DrawPoly(shape.position, shape.numSides, shape.radius * shape.scale, shape.rotation, shape.color);
            else
                DrawPolyLinesEx(shape.position, shape.numSides, shape.radius * shape.scale, shape.rotation,
                                shape.lineThickness, shape.color);
        }
    }
}
