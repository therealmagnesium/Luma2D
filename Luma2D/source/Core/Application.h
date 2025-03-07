#pragma once
#include "Core/Base.h"

#include <raylib.h>
#include <string>

namespace Luma2D
{
    namespace Core
    {
        struct ApplicationSpecification
        {
            std::string name = "Untitled Project";
            std::string author = "None";
            std::string version = "1.0";
            u32 windowWidth = 1280;
            u32 windowHeight = 720;
            u32 targetFramerate = 60;
        };

        class Application
        {
        public:
            Application(const ApplicationSpecification& appInfo);
            virtual ~Application();

            inline ApplicationSpecification& GetInfo() { return m_specification; }

            void Run();
            void Quit();

        private:
            virtual void OnCreate() = 0;
            virtual void OnUpdate() = 0;
            virtual void OnRender() {}
            virtual void OnRenderUI() {}
            virtual void OnShutdown() {}

        private:
            bool m_isRunning = true;
            ApplicationSpecification m_specification;
            Color m_clearColor = RAYWHITE;
        };

        extern Application* App;
    }
}
