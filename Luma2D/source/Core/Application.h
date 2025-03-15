#pragma once
#include "Core/Base.h"
#include "Core/Plug.h"

#include <string>
#include <raylib.h>

namespace Luma2D
{
    namespace Core
    {
        struct ApplicationSpecification
        {
            std::string name;
            std::string version;
            std::string author;
            PlugData plugData;
            u32 windowWidth = 1280;
            u32 windowHeight = 720;
            u32 targetFramerate = 60;
        };

        class Application
        {
        public:
            Application(const ApplicationSpecification& appInfo);
            ~Application();

            inline void SetClearColor(const Color& color) { m_clearColor = color; }

            inline Color& GetClearColor() { return m_clearColor; }
            inline PlugState& GetPlugState() { return m_plug; }
            inline RenderTexture& GetFramebuffer() { return m_framebuffer; }
            inline ApplicationSpecification& GetInfo() { return m_specification; }

            void Run();
            void Quit();

        private:
            bool m_isRunning = true;
            Color m_clearColor = RAYWHITE;
            PlugState m_plug;
            RenderTexture m_framebuffer;
            ApplicationSpecification m_specification;
        };

        extern Application* App;
    }
}
