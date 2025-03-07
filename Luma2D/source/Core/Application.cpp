#include "Core/Application.h"
#include "Core/Base.h"

#include <raylib.h>
#include <dlfcn.h>
#include <Test.h>

namespace Luma2D
{
    namespace Core
    {
        static bool isInitialized = false;
        static Test::Foo_t foo = NULL;
        static Test::Bar_t bar = NULL;
        static void* libTest = NULL;

        Application* App = NULL;

        Application::Application(const ApplicationSpecification& appInfo) : m_specification(appInfo)
        {
            if (isInitialized)
            {
                TraceLog(LOG_WARNING, "Cannot create main application more than once");
                return;
            }

            App = this;

            libTest = dlopen("../Test/libTest.so", RTLD_NOW);
            if (libTest == NULL)
            {
                TraceLog(LOG_FATAL, "Could not open libTest.so!");
                Quit();
                return;
            }

            foo = (Test::Foo_t)dlsym(libTest, "Foo");
            if (foo == NULL)
                TraceLog(LOG_WARNING, "Couldn't find symbol for foo");

            bar = (Test::Bar_t)dlsym(libTest, "Bar");
            if (bar == NULL)
                TraceLog(LOG_WARNING, "Couldn't find symbol for bar");

            // foo();
            // bar();

            InitWindow(m_specification.windowWidth, m_specification.windowHeight, m_specification.name.c_str());
            SetTargetFPS(m_specification.targetFramerate);

            TraceLog(LOG_INFO, "Successfully created the application");
        }

        Application::~Application()
        {
            dlclose(libTest);
            CloseWindow();
            this->OnShutdown();
        }

        void Application::Run()
        {
            while (m_isRunning)
            {
                m_isRunning = !WindowShouldClose();

                this->OnUpdate();

                BeginDrawing();
                ClearBackground(m_clearColor);
                this->OnRender();
                this->OnRenderUI();
                EndDrawing();
            }
        }

        void Application::Quit()
        {
            TraceLog(LOG_INFO, "Quitting the application...");
            m_isRunning = false;
        }

    }
}
