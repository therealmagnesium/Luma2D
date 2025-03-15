#include "Core/Application.h"
#include "Core/Plug.h"

#include <imgui.h>
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

            m_framebuffer = LoadRenderTexture(m_specification.windowWidth, m_specification.windowHeight);

            rlImGuiSetup(true);
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/kumbh/KumbhSans-Regular.ttf", 20.f);

            ImGuiStyle& style = ImGui::GetStyle();
            style.FrameRounding = 2.5f;
            style.WindowMinSize.x = 380.f;

            style.Colors[ImGuiCol_WindowBg] = ImVec4(.086f, .098f, .149f, 1.f);
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.192f, 0.192f, 0.351f, 1.f);

            style.Colors[ImGuiCol_Header] = ImVec4(0.133f, 0.149f, 0.220f, 1.f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.183f, 0.199f, 0.270f, 1.f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.103f, 0.119f, 0.190f, 1.f);

            style.Colors[ImGuiCol_Button] = ImVec4(0.192f, 0.192f, 0.351f, 1.f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.242f, 0.242f, 0.401f, 1.f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.142f, 0.142f, 0.311f, 1.f);

            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.211f, 0.235f, 0.349f, 1.f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.261f, 0.285f, 0.399f, 1.f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.161f, 0.185f, 0.299f, 1.f);

            style.Colors[ImGuiCol_Tab] = ImVec4(0.211f, 0.235f, 0.349f, 1.f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.261f, 0.285f, 0.399f, 1.f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.161f, 0.185f, 0.299f, 1.f);
            style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.131f, 0.155f, 0.269f, 1.f);
            style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.161f, 0.185f, 0.299f, 1.f);

            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.111f, 0.135f, 0.249f, 1.f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.081f, 0.105f, 0.219f, 1.f);
            style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.111f, 0.135f, 0.249f, 1.f);

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
            UnloadRenderTexture(m_framebuffer);
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

                BeginTextureMode(m_framebuffer);
                {
                    ClearBackground(m_clearColor);
                    plugRender();
                }
                EndTextureMode();

                BeginDrawing();
                {
                    ClearBackground(m_clearColor);

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
