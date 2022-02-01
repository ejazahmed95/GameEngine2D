// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MonsterChase.h"

Raven::Application* Raven::CreateApplication() {
    return new MonsterChase();
}

char* readStringFromCIn() {
    char a[20];
    std::cin >> a;
    int len = 1;
    while (len <= 20 && a[len-1] != '\n') len++;
    //char* str = (char*)malloc(len * sizeof(char));
    char* str = new char[len];
    memcpy(str, a, len-1);
    str[len - 1] = '\0';
    return str;
}


void MonsterChase::Run() {
    int mCount;
    this->mc_ = new MonsterController();

    std::cout << "Enter Player Name" << std::endl;
    char* playerName = readStringFromCIn();
    this->pc_ = new PlayerController(playerName);

    std::cout << "How many monsters do you want?" << std::endl;
    std::cin >> mCount;
    for (int i = 0; i < mCount; i++) {
        std::cout << "Enter the name of monster " << i << ": ";
        mc_->addMonster(readStringFromCIn());
    }
    startGame();
}

void MonsterChase::startGame() {
    while (true) {
        std::cout << "Please use WASD to move and Q to quit" << std::endl;
        char in = standardInputReader().readChar();
        if (in == 'q' || in == 'Q') break;
        pc_->handleInput(in);
        updateAllObjects();
        std::cout << *pc_ << std::endl;
        std::cout << *mc_ << std::endl;
    }
}

MonsterChase::~MonsterChase()
{
    delete pc_;
    delete mc_;
}

void MonsterChase::updateAllObjects() {
    pc_->update(0);
    mc_->update(0);

	if (pc_->position().x() > 10000) {
		pc_->setVelocity(-2, 0);
	} else if (pc_->position().x() < -10000) {
		pc_->setVelocity(2, 0);
	}
}

#include <assert.h>
#include <DirectXColors.h>

void MonsterChase::RunWinApp() {
	
}



void MonsterChase::GameStart() {
	// Application::GameStart();
	int mCount = 1;
	char playerName[] = "Ejaz";
	this->mc_ = new MonsterController();
	this->pc_ = new PlayerController(playerName);
	for (int i = 0; i < mCount; i++) {
		//std::cout << "Enter the name of monster " << i << ": ";
		mc_->addMonster(mc_->getCustomName("monster-", 0));
	}
	startWinGame();
}

void MonsterChase::startWinGame() {
	playerSprite = CreateSprite("assets\\sprites\\gastly.dds");
	pc_->setVelocity(2, 0);
}

void MonsterChase::GameEnd() {
	GLib::Release(playerSprite);
}

void MonsterChase::Update(float delta) {
	// Application::Update(delta);
	// bool quit = false;
	// GLib::Service(quit);
	// GLib::BeginRendering(DirectX::Colors::Aqua);
	// drawAllObjects();
	// GLib::EndRendering();
}

void MonsterChase::drawAllObjects()
{
	GLib::Sprites::BeginRendering();

	float xOffset = pc_->position().x() * 0.01;
	GLib::Point2D	Offset = { -180.0f + xOffset, -100.0f };

	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	//sprintf_s(Buffer, lenBuffer, "The x position is::%f  || %f\n", xOffset, Offset.x);
	//OutputDebugStringA(Buffer);

	// Tell GLib to render this sprite at our calculated location
	if (playerSprite) {
		GLib::Render(*playerSprite, Offset, 0.0f, 0.0f);
	}

	GLib::Sprites::EndRendering();
}


GLib::Sprite* CreateSprite(const char* i_pFilename)
{
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

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
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
