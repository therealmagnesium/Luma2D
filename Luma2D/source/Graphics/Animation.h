#pragma once
#include "Core/Base.h"
#include "Graphics/Sprite.h"

#include <string>
#include <unordered_map>
#include <vector>

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
            bool isValid = false;
            bool isPlaying = false;
            u32 counter = 0;
            u32 speed = 0;
            u32 currentFrame = 0;
            u32 totalFrames = 0;
            u32 frameOffset = 0;
            std::string name;
            AnimationType type;
        };

        struct AnimationController
        {
            bool isValid = false;
            u32 currentAnimationIndex = 0;
            Sprite* sprite = NULL;
            std::vector<Animation> animations;
            std::unordered_map<std::string, Texture*> animNameTextureMap;
        };

        Animation CreateAnimation(const std::string& name, u32 speed, u32 totalFrames, u32 frameOffset,
                                  AnimationType type);
        void PlayAnimation(Animation& animation);
        void PauseAnimation(Animation& animation);
        void StopAnimation(Animation& animation);
        void UpdateAnimation(Animation& animation, Sprite& sprite);

        AnimationController CreateAnimationController(Sprite* sprite, u32 estimatedAnimCount);
        void AnimControllerAddAnimation(AnimationController& controller, Animation& animation, Texture* texture);
        void AnimControllerSwitchAnimation(AnimationController& controller, u32 animIndex);
        void AnimControllerUpdate(AnimationController& controller);
    }
}
