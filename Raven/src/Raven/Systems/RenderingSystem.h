#pragma once
#include <string>
#include <unordered_map>
#include "BaseSystem.h"

namespace GLib {
	class Sprite;
}

namespace Raven { namespace System {
	class RenderingSystem: public BaseSystem {
	public:
		RenderingSystem();

		void Initialize() override;
		void Update(float dt) override;
		void Destroy() override;

		void LoadSprites(std::vector<std::string> locations);
	private:
		GLib::Sprite* getSprite(const std::string& string);
		std::unordered_map<std::string, GLib::Sprite*> m_Sprites;
		GLib::Sprite* collisionBox;

		// Static Helpers
	private:
		static GLib::Sprite* CreateSprite(const char* i_pFilename);
		static void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
	};
}}

