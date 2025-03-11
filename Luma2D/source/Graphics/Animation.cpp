#include "Graphics/Animation.h"
#include "Graphics/Sprite.h"

#include "Core/Application.h"
#include "Core/Base.h"

#include <raylib.h>

namespace Luma2D
{
    namespace Graphics
    {
        Animation CreateAnimation(const std::string& name, bool isLooped, u32 speed, u32 totalFrames, u32 frameOffset,
                                  AnimationType type)
        {
            Animation animation;
            animation.name = name;
            animation.isLooped = isLooped;
            animation.speed = speed;
            animation.totalFrames = totalFrames;
            animation.frameOffset = frameOffset;
            animation.type = type;

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

        void UpdateAnimation(Animation& animation, Sprite& sprite, Texture* texture)
        {
            ASSERT_MSG(texture != NULL, "Cannot update animation with a null texture!");
            sprite.texture = texture;

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
    }
}
