#include "GD_Game.h"
#include "DinoMainMenuScreen.h"
#include "GDGameScreen.h"
#include "DinoRestartMenuScreen.h"

Engine::GD_Game::GD_Game(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Dino Game";
}

Engine::GD_Game::~GD_Game()
{
}

void Engine::GD_Game::Init()
{
	Engine::ScreenManager::GetInstance(this)->AddScreen("ingame", new GDGameScreen())
		->AddScreen("mainmenu", new DinoMainMenuScreen())->AddScreen("restartmenu", new DinoRestartMenuScreen())->SetCurrentScreen("mainmenu");

}

void Engine::GD_Game::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();

}

void Engine::GD_Game::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}