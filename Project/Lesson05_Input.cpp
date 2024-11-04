#include "Lesson05_Input.h"

Engine::Lesson05_Input::Lesson05_Input(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Input Handling";
}

Engine::Lesson05_Input::~Lesson05_Input()
{
	delete texture;
	delete sprite;
}

void Engine::Lesson05_Input::Init()
{
	texture = new Texture("monster.png");
	sprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(6)->SetNumYFrames(3)->AddAnimation("idle", 0, 3)->AddAnimation("walk", 6, 11)->PlayAnim("idle")->SetScale(3)->SetAnimationDuration(90);

	SetBackgroundColor(65, 180, 242);

	inputManager->AddInputMapping(SDLK_LEFT,"walk-left" )->AddInputMapping(SDL_BUTTON_LEFT,"walk-left" )->AddInputMapping(SDL_CONTROLLER_BUTTON_DPAD_LEFT,"walk-left" )->AddInputMapping(SDL_CONTROLLER_AXIS_LEFTX, "walk-left")->AddInputMapping(SDLK_RIGHT,"walk-right" )->AddInputMapping(SDL_BUTTON_RIGHT,"walk-right" )->AddInputMapping(SDL_CONTROLLER_BUTTON_DPAD_RIGHT,"walk-right" )->AddInputMapping(SDL_CONTROLLER_AXIS_RIGHTX,"walk-right" );
}

void Engine::Lesson05_Input::Update()
{
	
	float x = sprite->GetPosition().x;
	float y = sprite->GetPosition().y;
	float velocity = 0.07f;
	// s = v * t;
	sprite->PlayAnim("idle");

	if (inputManager->IsKeyPressed("walk-right")) {
		x += velocity * GetGameTime();
		sprite->SetFlipHorizontal(false)->PlayAnim("walk");
	}

	if (inputManager->IsKeyPressed("walk-left")) {
		x -= velocity * GetGameTime();
		sprite->SetFlipHorizontal(true)->PlayAnim("walk");
	}

	sprite->SetPosition(x, y)->Update(GetGameTime());
}

void Engine::Lesson05_Input::Render()
{
	sprite->Draw();
}

