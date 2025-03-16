#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <unordered_map>

namespace Luma2D
{
    namespace Core
    {
        class AssetManager
        {
        public:
            AssetManager() = default;

            void Initialize();
            void Shutdown();

            Texture* GetTexture(const char* name);
            const char* GetTextureName(const Texture* texture);
            std::vector<std::string> GetAllTextureNames();
            void AddTexture(const char* name, const char* path, TextureFilter filter);

        private:
            std::unordered_map<std::string, Texture> m_textures;
        };

        extern AssetManager* Assets;
    }
}
