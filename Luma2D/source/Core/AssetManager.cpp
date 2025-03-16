#include "Core/AssetManager.h"
#include "Core/Base.h"

#include <raylib.h>

namespace Luma2D
{
    namespace Core
    {
        static bool isInitialized = false;
        AssetManager* Assets = NULL;

        void AssetManager::Initialize()
        {
            if (isInitialized)
            {
                TraceLog(LOG_WARNING, "Cannot initialize the asset manager more than once");
                return;
            }

            Assets = this;
            isInitialized = true;
        }

        void AssetManager::Shutdown()
        {
            TraceLog(LOG_INFO, "Shutting down asset manageer...");
            for (auto& [name, texture] : m_textures)
                UnloadTexture(texture);
        }

        Texture* AssetManager::GetTexture(const char* name)
        {
            if (m_textures.find(name) == m_textures.end())
            {
                TraceLog(LOG_ERROR, "The asset manager couldn't find the texture %s!", name);
                return NULL;
            }

            return &m_textures[name];
        }

        std::vector<std::string> AssetManager::GetAllTextureNames()
        {
            std::vector<std::string> names;
            names.reserve(m_textures.size());

            for (auto& [name, texture] : m_textures)
                names.push_back(name);

            return names;
        }

        const char* AssetManager::GetTextureName(const Texture* texture)
        {
            const char* name = "";

            for (auto& textureNamePair : m_textures)
            {
                if (&textureNamePair.second == texture)
                {
                    name = textureNamePair.first.c_str();
                    break;
                }
            }

            return name;
        }

        void AssetManager::AddTexture(const char* name, const char* path, TextureFilter filter)
        {
            if (m_textures.find(name) != m_textures.end())
            {
                TraceLog(LOG_ERROR, "The texture %s is already loaded into the asset manager!", name);
                return;
            }

            Texture texture = LoadTexture(path);
            SetTextureFilter(texture, filter);

            if (texture.id != 0)
                m_textures[name] = texture;
        }
    }
}
