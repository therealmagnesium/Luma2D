#pragma once
#include "Core/Base.h"
#include "Graphics/Sprite.h"

#include <string>

namespace Luma2D
{
    namespace Graphics
    {
        enum class AnimationType
        {
            Horizontal = 0,
            Vertical
        };

        struct Animation
        {
            bool isPlaying = false;
            bool isLooped = false;
            u32 counter = 0;
            u32 speed = 0;
            u32 currentFrame = 0;
            u32 totalFrames = 0;
            u32 frameOffset = 0;
            std::string name;
            AnimationType type;
        };

        Animation CreateAnimation(const std::string& name, bool isLooped, u32 speed, u32 totalFrames, u32 frameOffset,
                                  AnimationType type);
        void PlayAnimation(Animation& animation);
        void PauseAnimation(Animation& animation);
        void StopAnimation(Animation& animation);
        void UpdateAnimation(Animation& animation, Sprite& sprite, Texture* texture);
    }
}
