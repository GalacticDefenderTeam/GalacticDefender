#ifndef GDGAMESCREEN_H
#define GDGAMESCREEN_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"
#include <vector>
#include "DinoMainMenuScreen.h"
#include "GDGameScreen.h"
#include "ScreenManager.h"

namespace Engine {
	class GDGameScreen :
		public Engine::Screen
	{
	public:
		GDGameScreen();
		~GDGameScreen();

		void Init();
		void Update();
		void Draw();
		void ResetGameState();
	private:
		Texture* dotTexture = NULL;
		Sprite* monsterSprite = NULL;
		Sprite* backgroundSprite = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
		Music* music = NULL;;
		Sound* sound = NULL;
		Text* textScore = NULL;
		Text* textGameOver = NULL;
		Text* textRestart = NULL;
		bool debug = false;

		int score = 0;              // Variabel skor
		float scoreUpdateTime = 0;   // Waktu untuk menambah skor
		float offset = 0;
	};
}
#endif

