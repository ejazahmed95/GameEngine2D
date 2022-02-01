#pragma once
#include "Raven.h"
#include "PlayerController.h"
#include "MonsterController.h"

class MonsterChase: public Raven::Application
{
public:
	MonsterChase(): pc_(nullptr), mc_(nullptr) {}
	~MonsterChase() override;
	void updateAllObjects();
	void startGame();
	void Run();

	// For Windows App
	void RunWinApp();
	void startWinGame();
	void drawAllObjects();

	void GameStart() override;
	void GameEnd() override;
	void Update(float delta) override;

	// Removing copy constructors
	MonsterChase& operator=(const MonsterChase& m) = delete;
private:
	PlayerController* pc_;
	MonsterController* mc_;
	GLib::Sprite* playerSprite;
};

GLib::Sprite* CreateSprite(const char* i_pFilename);
void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);