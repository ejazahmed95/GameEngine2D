#include "RenderingSystem.h"

#include <DirectXColors.h>
#include <GLib.h>

#include "../Components/SpriteRenderer.h"
#include "../Components/Transform.h"
#include "../CoreModule/Entity.h"

namespace Raven {namespace Components {
	struct Transform;
	struct SpriteRenderer;
}}

namespace Raven { namespace System {

	RenderingSystem::RenderingSystem() {
		using namespace Components;
		m_Mask.Add(TComponent<Transform>::Id());
		m_Mask.Add(TComponent<SpriteRenderer>::Id());
	}

	void RenderingSystem::Initialize() {
		BaseSystem::Initialize();
	}

	void RenderingSystem::Update(float dt) {
		bool quit = false;
		GLib::Service(quit);
		GLib::BeginRendering(DirectX::Colors::Aqua);

		GLib::Sprites::BeginRendering();
		for (const auto& element : m_RegisteredEntities) {
			auto spriteRenderer = element->GetComponent<Components::SpriteRenderer>();
			auto transform = element->GetComponent<Components::Transform>();
			GLib::Point2D	Offset = { -180.0f + transform->position.X(), -100.0f + transform->position.Y() };
			GLib::Sprite* sprite = getSprite(spriteRenderer->m_spriteRef);
			// SLib::Log::D("Rendering Sprite::" + std::to_string(reinterpret_cast<uintptr_t>(sprite)));
			GLib::Render(*sprite, Offset, 0.0f, 0.0f);
		}
		GLib::Sprites::EndRendering();

		GLib::EndRendering();
	}

	void RenderingSystem::Destroy() {
		
	}

	void RenderingSystem::LoadSprites(std::vector<std::string> paths) {
		for (const auto & path : paths) {
			GLib::Sprite* sprite = CreateSprite(path.c_str());
			m_Sprites.insert({ path, sprite });
		}
	}

	GLib::Sprite* RenderingSystem::getSprite(const std::string& string) {
		return m_Sprites[string];
	}


	GLib::Sprite* RenderingSystem::CreateSprite(const char* i_pFilename) {
		assert(i_pFilename);

		size_t sizeTextureFile = 0;

		// Load the source file (texture data)
		void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

		// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
		GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

		// exit if something didn't work
		// probably need some debug logging in here!!!!
		if (pTextureFile)
			delete[] pTextureFile;

		if (pTexture == nullptr)
			return nullptr;

		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;

		// Get the dimensions of the texture. We'll use this to determine how big it is on screen
		bool result = GLib::GetDimensions(*pTexture, width, height, depth);
		assert(result == true);
		assert((width > 0) && (height > 0));

		// Define the sprite edges
		GLib::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
		GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
		GLib::RGBA							Color = { 255, 255, 255, 255 };

		// Create the sprite
		GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs, pTexture);

		// release our reference on the Texture
		GLib::Release(pTexture);

		return pSprite;
	}

	void* RenderingSystem::LoadFile(const char* i_pFilename, size_t& o_sizeFile)
	{
		assert(i_pFilename != NULL);

		FILE* pFile = NULL;

		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
			return NULL;

		assert(pFile != NULL);

		int FileIOError = fseek(pFile, 0, SEEK_END);
		assert(FileIOError == 0);

		long FileSize = ftell(pFile);
		assert(FileSize >= 0);

		FileIOError = fseek(pFile, 0, SEEK_SET);
		assert(FileIOError == 0);

		uint8_t* pBuffer = new uint8_t[FileSize];
		assert(pBuffer);

		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		assert(FileRead == FileSize);

		fclose(pFile);

		o_sizeFile = FileSize;

		return pBuffer;
	}
}}

