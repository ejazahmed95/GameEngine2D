#include "RenderingSystem.h"

#include <DirectXColors.h>
#include <GLib.h>

#include "../Components/SpriteRenderer.h"
#include "../Components/Transform.h"
#include "../Components/Collider2D.h"
#include "../CoreModule/Entity.h"


namespace Raven { namespace System {

	RenderingSystem::RenderingSystem() {
		// TODO: Find a better way for adding required components
		using namespace Components;
		m_Mask.Add(Transform::Id());
		m_Mask.Add(SpriteRenderer::Id());
		collisionBox = nullptr;
	}

	RenderingSystem::~RenderingSystem() {
		GLib::Release(collisionBox);
	}

	void RenderingSystem::Initialize() {
		BaseSystem::Initialize();
	}

	void RenderingSystem::UpdateComponent(Components::SpriteRenderer* component) {
		component->sprite = CreateSprite(m_Textures[component->texName], component->scale);
	}

	void RenderingSystem::Update(float dt) {
		bool quit = false;
		GLib::Service(quit);
		GLib::BeginRendering(DirectX::Colors::Aqua);

		GLib::Sprites::BeginRendering();
		for (const auto& element : m_RegisteredEntities) {
			auto spriteRenderer = element->GetComponent<Components::SpriteRenderer>();
			if (spriteRenderer->sprite == nullptr) UpdateComponent(spriteRenderer);
			auto transform = element->GetComponent<Components::Transform>();
			GLib::Point2D	Offset = { transform->position.X(), transform->position.Y() };
			GLib::Sprite* sprite = getSprite(spriteRenderer->spriteRef);
			// SLib::Log::D("Rendering Sprite::" + std::to_string(reinterpret_cast<uintptr_t>(sprite)));
			GLib::Render(*spriteRenderer->sprite, Offset, 0.0f, transform->rotation.Z());

			// If Debug
			auto collider = element->GetComponent<Components::Collider2D>();
			if (collider == nullptr) continue;
			GLib::Point2D boxLoc = { Offset.x, Offset.y };
			GLib::Render(*collisionBox, boxLoc, 0.0f, transform->rotation.Z());
		}
		GLib::Sprites::EndRendering();
		GLib::EndRendering();
	}

	void RenderingSystem::Destroy() {
		BaseSystem::Destroy();

		for(const auto& tex: m_Textures) {
			GLib::Release(tex.second);
		}
		for (const auto& spritePair : m_Sprites) {
			GLib::Release(spritePair.second);
		}
	}

	void RenderingSystem::LoadTextures(json textures) {
		for (auto& tex: textures) {
			std::string name = "";
			std::string path = "";
			tex.at("name").get_to(name);
			tex.at("path").get_to(path);
			m_Textures.insert({name, CreateTexture(path.c_str())});
		}
		collisionBox = CreateSprite(m_Textures["collision_box"], Core::Point3D(1, 1, 1));
	}

	void RenderingSystem::LoadSprites(std::vector<std::string> paths) {
		for (const auto & path : paths) {
			GLib::Sprite* sprite = CreateSprite(path.c_str(), Core::Point3D(1, 1, 1));
			if(sprite == nullptr) {
				// SLib::Log::
			}
			m_Sprites.insert({ path, sprite });
		}
		
	}

	GLib::Sprite* RenderingSystem::getSprite(const std::string& string) {
		// TODO: Return a default sprite and do not break the code
		return m_Sprites[string];
	}

	GLib::Texture* RenderingSystem::CreateTexture(const char* fileName) {
		assert(fileName);

		size_t sizeTextureFile = 0;

		// Load the source file (texture data)
		void* pTextureFile = LoadFile(fileName, sizeTextureFile);

		// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
		GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

		// exit if something didn't work
		// probably need some debug logging in here!!!!
		if (pTextureFile)
			delete[] pTextureFile;

		return pTexture;
	}

	GLib::Sprite* RenderingSystem::CreateSprite(GLib::Texture* tex, Core::Point3D scale) {
		if (tex == nullptr)
			return nullptr;

		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;

		// Get the dimensions of the texture. We'll use this to determine how big it is on screen
		bool result = GLib::GetDimensions(*tex, width, height, depth);
		assert(result == true);
		assert((width > 0) && (height > 0));

		// Define the sprite edges
		GLib::SpriteEdges	Edges = { -float(width * scale.X() / 2.0f), float(height * scale.Y()) , float(width * scale.X() / 2.0f), 0.0f };
		GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
		GLib::RGBA							Color = { 255, 255, 255, 255 };

		// Create the sprite
		GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs, tex);
		return pSprite;
	}

	GLib::Sprite* RenderingSystem::CreateSprite(const char* i_pFilename, Core::Point3D scale) {
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
		GLib::SpriteEdges	Edges = { -float(width * scale.X() / 2.0f), float(height * scale.Y()) , float(width * scale.X() / 2.0f), 0.0f };
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

