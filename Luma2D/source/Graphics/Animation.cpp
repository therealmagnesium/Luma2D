#include "Graphics/Animation.h"
#include "Graphics/Sprite.h"

#include "Core/Application.h"
#include "Core/Base.h"

#include <raylib.h>

namespace Luma2D
{
    namespace Graphics
    {
        Animation CreateAnimation(const std::string& name, u32 speed, u32 totalFrames, u32 frameOffset,
                                  AnimationType type)
        {
            Animation animation;
            animation.name = name;
            animation.speed = speed;
            animation.totalFrames = totalFrames;
            animation.frameOffset = frameOffset;
            animation.type = type;
            animation.isValid = true;

            return animation;
        }

        void PauseAnimation(Animation& animation)
        {
            animation.isPlaying = false;
        }

        void StopAnimation(Animation& animation)
        {
            animation.isPlaying = false;
            animation.currentFrame = 0;
            animation.counter = 0;
        }

        void PlayAnimation(Animation& animation)
        {
            animation.isPlaying = true;
        }

        void UpdateAnimation(Animation& animation, Sprite& sprite)
        {
            QUIET_ASSEERT_MSG(sprite.texture != NULL,
                              "Cannot update animation because there is no valid texture reference!");

            static bool hasPlayedOnce = false;
            float frameSize = 0.f;

            switch (animation.type)
            {
                case AnimationType::Horizontal:
                {
                    frameSize = (float)sprite.texture->width / animation.totalFrames;
                    sprite.crop.width = frameSize;
                    sprite.crop.height = frameSize;

                    break;
                }

                case AnimationType::Vertical:
                {
                    frameSize = (float)sprite.texture->height / animation.totalFrames;
                    sprite.crop.width = frameSize;
                    sprite.crop.height = frameSize;

                    break;
                }
            }

            if (animation.isPlaying)
            {
                animation.counter++;

                Core::ApplicationSpecification& appInfo = Core::App->GetInfo();
                if (animation.counter >= (appInfo.targetFramerate / animation.speed))
                {
                    animation.counter = 0;
                    animation.currentFrame++;

                    if (animation.currentFrame > animation.totalFrames - 1)
                        animation.currentFrame = 0;

                    switch (animation.type)
                    {
                        case AnimationType::Horizontal:
                            sprite.crop.x = (float)animation.currentFrame * frameSize;
                            sprite.crop.y = (float)animation.frameOffset * frameSize;
                            break;

                        case AnimationType::Vertical:
                            sprite.crop.x = (float)animation.frameOffset * frameSize;
                            sprite.crop.y = (float)animation.currentFrame * frameSize;
                            break;
                    }
                }
            }
        }

        AnimationController CreateAnimationController(Sprite* sprite, u32 estimatedAnimCount)
        {
            ASSERT_MSG(sprite != NULL, "Animation Controller cannot have a null sprite reference!");

            AnimationController controller;
            controller.sprite = sprite;
            controller.currentAnimationIndex = 0;
            controller.animations.reserve(estimatedAnimCount);
            controller.isValid = true;

            return controller;
        }

        void AnimControllerAddAnimation(AnimationController& controller, Animation& animation, Texture* texture)
        {
            ASSERT_MSG(controller.isValid,
                       "Animation Controllers must be created with CreateAnimationController(Sprite*, u32)!");

            ASSERT_MSG(texture != NULL, "Cannot add animation to Animation Controller with a null texture reference!");

            if (animation.isValid)
                controller.animations.push_back(animation);

            controller.animNameTextureMap[animation.name] = texture;
        }

        void AnimControllerSwitchAnimation(AnimationController& controller, u32 animIndex)
        {
            ASSERT_MSG(controller.isValid,
                       "Animation Controllers must be created with CreateAnimationController(Sprite*, u32)!");
            ASSERT_MSG(animIndex <= controller.animations.size(),
                       "Failed to switch animations because the animIndex is out of bounds!");

            StopAnimation(controller.animations[controller.currentAnimationIndex]); // Stop the previous animation

            // Switch the current animation index
            if (controller.animations[animIndex].isValid)
                controller.currentAnimationIndex = animIndex;

            PlayAnimation(controller.animations[controller.currentAnimationIndex]); // Play the new animation
        }

        void AnimControllerUpdate(AnimationController& controller)
        {
            ASSERT_MSG(controller.isValid,
                       "Animation Controllers must be created with CreateAnimationController(Sprite*, u32)!");

            ASSERT_MSG(controller.sprite != NULL, "An Animation Controller has a referencce to a sprite that is null!");

            Animation& currentAnimation = controller.animations[controller.currentAnimationIndex];
            controller.sprite->texture = controller.animNameTextureMap[currentAnimation.name];
            UpdateAnimation(currentAnimation, *controller.sprite);
        }
    }
}
