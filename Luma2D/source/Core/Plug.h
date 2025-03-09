#pragma once
#include "Core/Base.h"
#include <string>
#include <unordered_map>

namespace Luma2D
{
    namespace Core
    {
        typedef void (*Plug_t)(void);

        struct PlugData
        {
            std::string libPath;
            std::string createSym;
            std::string updateSym;
            std::string renderSym;
            std::string renderUISym;
            std::string shutdownSym;
        };

        struct PlugState
        {
            bool isValid = false;
            void* libHandle = NULL;
            std::unordered_map<std::string, Plug_t> plugins;
        };

        PlugState LoadPluginCode(const PlugData& data);
        void UnloadPlugin(PlugState& plug);
    }
}
