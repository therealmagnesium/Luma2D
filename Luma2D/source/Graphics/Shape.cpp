#include "Graphics/Shape.h"
#include "Core/Base.h"
#include <raylib.h>

namespace Luma2D
{
    namespace Graphics
    {
        void DrawShape(Shape& shape, bool isOutlined)
        {
            if (shape.numSides > 32)
                shape.numSides = 32;

            if (!isOutlined)
                DrawPoly(shape.position, shape.numSides, shape.radius * shape.scale, shape.rotation, shape.color);
            else
                DrawPolyLinesEx(shape.position, shape.numSides, shape.radius * shape.scale, shape.rotation,
                                shape.lineThickness, shape.color);
        }
    }
}
