#pragma once
#include <string>
#include <unordered_map>
#include "BaseSystem.h"
#include "GLib.h"
#include "../nlohmann/json.hpp"

namespace Raven {namespace Core {
	class Point3D;
}}

namespace Raven {namespace Components {
	struct SpriteRenderer;
}}

using json = nlohmann::json;


namespace Raven { namespace System {
	class RenderingSystem: public BaseSystem {
	public:
		RenderingSystem();
		~RenderingSystem() override;
		void Initialize() override;
		void UpdateComponent(Components::SpriteRenderer* sprite_renderer, Core::Entity* entity);
		void Update(float dt) override;
		void Destroy() override;

		void LoadSprites(std::vector<std::string> locations);
		void LoadTextures(json textures);
	private:
		GLib::Sprite* getSprite(const std::string& string);
		std::unordered_map<std::string, GLib::Sprite*> m_Sprites;
		std::unordered_map<std::string, GLib::Texture*> m_Textures;
		GLib::Sprite* collisionBox;

		// Static Helpers
	private:
		static GLib::Sprite* CreateSprite(const char* i_pFilename, Core::Point3D);
		static GLib::Sprite* CreateSprite(GLib::Texture* tex, Core::Point3D scale);
		static GLib::Texture* CreateTexture(const char* fileName);
		static void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
	};
}}

