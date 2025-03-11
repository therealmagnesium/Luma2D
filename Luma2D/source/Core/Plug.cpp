#include "Core/Plug.h"
#include "Core/Application.h"

#include <dlfcn.h>
#include <raylib.h>

namespace Luma2D
{
    namespace Core
    {
        PlugState LoadPluginCode(const PlugData& data)
        {
            PlugState plug;

            plug.libHandle = dlopen(data.libPath.c_str(), RTLD_NOW);
            ASSERT_MSG(plug.libHandle != NULL, "Failed to load plugin data!");

            plug.plugins[data.createSym] = (Plug_t)dlsym(plug.libHandle, data.createSym.c_str());
            ASSERT_MSG(plug.plugins[data.createSym] != NULL, "Failed to load the Create symbol in the plugin code!");

            plug.plugins[data.updateSym] = (Plug_t)dlsym(plug.libHandle, data.updateSym.c_str());
            ASSERT_MSG(plug.plugins[data.updateSym] != NULL, "Failed to load the Update symbol in the plugin code!");

            plug.plugins[data.renderSym] = (Plug_t)dlsym(plug.libHandle, data.renderSym.c_str());
            ASSERT_MSG(plug.plugins[data.renderSym] != NULL, "Failed to load the Render symbol in the plugin code!");

            plug.plugins[data.renderUISym] = (Plug_t)dlsym(plug.libHandle, data.renderUISym.c_str());
            ASSERT_MSG(plug.plugins[data.renderUISym] != NULL,
                       "Failed to load the RenderUI symbol in the plugin code!");

            plug.plugins[data.shutdownSym] = (Plug_t)dlsym(plug.libHandle, data.shutdownSym.c_str());
            ASSERT_MSG(plug.plugins[data.shutdownSym] != NULL,
                       "Failed to load the Shutdown symbol in the plugin code!");

            plug.isValid = true;
            TraceLog(LOG_INFO, "Successfully loaded the plugin code");
            return plug;
        }

        void UnloadPlugin(PlugState& plug)
        {
            if (plug.isValid)
            {
                TraceLog(LOG_INFO, "Unloading the plugin code...");
                dlclose(plug.libHandle);
                plug.isValid = false;
            }
        }
    }
}
