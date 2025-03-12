#include "Core/Application.h"
#include "Core/Plug.h"

#include <raylib.h>
#include <rlImGui.h>

namespace Luma2D
{
    namespace Core
    {
        static bool isInitialized = false;
        static Plug_t plugCreate = NULL;
        static Plug_t plugUpdate = NULL;
        static Plug_t plugRender = NULL;
        static Plug_t plugRenderUI = NULL;
        static Plug_t plugShutdown = NULL;

        Application* App = NULL;

        Application::Application(const ApplicationSpecification& appInfo) : m_specification(appInfo)
        {
            if (isInitialized)
            {
                TraceLog(LOG_WARNING, "Cannot initalize app more than once");
                return;
            }

            App = this;

            InitWindow(m_specification.windowWidth, m_specification.windowHeight, m_specification.name.c_str());
            SetTargetFPS(m_specification.targetFramerate);
            SetExitKey(KEY_NULL);

            rlImGuiSetup(true);

            m_plug = LoadPluginCode(m_specification.plugData);
            plugCreate = m_plug.plugins[m_specification.plugData.createSym];
            plugUpdate = m_plug.plugins[m_specification.plugData.updateSym];
            plugRender = m_plug.plugins[m_specification.plugData.renderSym];
            plugRenderUI = m_plug.plugins[m_specification.plugData.renderUISym];
            plugShutdown = m_plug.plugins[m_specification.plugData.shutdownSym];

            isInitialized = true;
        }

        Application::~Application()
        {
            TraceLog(LOG_INFO, "Exiting the application...");

            rlImGuiShutdown();
            UnloadPlugin(m_plug);
            CloseWindow();
        }

        void Application::Run()
        {
            plugCreate();

            while (m_isRunning)
            {
                m_isRunning = !WindowShouldClose();

                if (IsKeyPressed(KEY_ESCAPE))
                    Quit();

                if (IsKeyPressed(KEY_THREE))
                {
                    plugShutdown();

                    UnloadPlugin(m_plug);
                    m_plug = LoadPluginCode(m_specification.plugData);

                    plugCreate = m_plug.plugins[m_specification.plugData.createSym];
                    plugUpdate = m_plug.plugins[m_specification.plugData.updateSym];
                    plugRender = m_plug.plugins[m_specification.plugData.renderSym];
                    plugRenderUI = m_plug.plugins[m_specification.plugData.renderUISym];
                    plugShutdown = m_plug.plugins[m_specification.plugData.shutdownSym];

                    plugCreate();
                }

                plugUpdate();

                BeginDrawing();
                {
                    ClearBackground(m_clearColor);

                    plugRender();

                    rlImGuiBegin();
                    {
                        plugRenderUI();
                    }
                    rlImGuiEnd();
                }
                EndDrawing();
            }

            plugShutdown();
        }

        void Application::Quit()
        {
            m_isRunning = false;
        }
    }
}
