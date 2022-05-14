#pragma once
#include <DirectXMath.h>
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
		void Update(float dt) override;
		void Destroy() override;

		void LoadSprites(std::vector<std::string> locations);
		void LoadTextures(json textures);
		void SetBgColor();
	private:
		GLib::Sprite* getSprite(const std::string& string);
		std::unordered_map<std::string, GLib::Sprite*> m_Sprites;
		std::unordered_map<std::string, GLib::Texture*> m_Textures;
		GLib::Sprite* m_CollisionBox;
		DirectX::XMVECTORF32 m_ClearColor;

		// Static Helpers
	private:
		void UpdateComponent(Components::SpriteRenderer* spriteRenderer, Core::Entity* entity);
		static GLib::Sprite* CreateSprite(const char* i_pFilename, Core::Point3D);
		static GLib::Sprite* CreateSprite(GLib::Texture* tex, Core::Point3D scale);
		static GLib::Texture* CreateTexture(const char* fileName);
		static void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
	};
}}

