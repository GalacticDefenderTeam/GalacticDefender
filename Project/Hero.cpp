#include "Hero.h"

Engine::Hero::Hero(Texture* texture, Shader* shader, Quad* quad) :BaseCharacter(texture, shader, quad)
{
	sprite->SetNumXFrames(96);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("up", 0, 2);
	sprite->AddAnimation("upright", 12, 14);
	sprite->AddAnimation("right", 24, 26);
	sprite->AddAnimation("downright", 36, 38);
	sprite->AddAnimation("down", 48, 50);
	sprite->AddAnimation("downleft", 60, 62);
	sprite->AddAnimation("left", 72, 74);
	sprite->AddAnimation("upleft", 84, 86);
	sprite->PlayAnim("down");
	sprite->SetScale(3);
	sprite->SetAnimationDuration(90);

	inputManager = NULL;
}

Engine::Hero::~Hero()
{
	
}

void Engine::Hero::Update(float deltaTime)
{
	if (Engine::CharacterState::ALIVE == state) {
		Move(deltaTime);
	}
}


void Engine::Hero::Move(float deltaTime)
{
	// Get Current Player's Position
	float speed = 0.07f;
	// s = v * t;
	// Control player's movement using keyboard or gamepad
	velocity = vec2(0, 0);
	string anim = "";
	if (inputManager->IsKeyPressed("walk-up")) {
		velocity += vec2(0.0f, speed);
		anim += "up";
	}

	if (inputManager->IsKeyPressed("walk-down")) {
		velocity += vec2(0.0f, -speed);
		anim += "down";
	}

	if (inputManager->IsKeyPressed("walk-right")) {
		velocity += vec2(speed, 0.0f);
		anim += "right";
	}

	if (inputManager->IsKeyPressed("walk-left")) {
		velocity += vec2(-speed, 0.0f);
		anim += "left";
	}
	
	// Update new player's position
	vec2 newPosition = GetPosition() + velocity * deltaTime;
	sprite->SetPosition(newPosition.x, newPosition.y);
	// Update player's animation
	sprite->PlayAnim(anim);
	sprite->Update(deltaTime);

}

void Engine::Hero::Init(Input* inputManager)
{
	this->inputManager = inputManager;

	inputManager->AddInputMapping(SDLK_LEFT,"walk-left" );
	inputManager->AddInputMapping(SDL_CONTROLLER_BUTTON_DPAD_LEFT,"walk-left" );
	inputManager->AddInputMapping(SDL_CONTROLLER_AXIS_LEFTX,"walk-left");

	inputManager->AddInputMapping(SDLK_RIGHT, "walk-right");
	inputManager->AddInputMapping(SDL_CONTROLLER_BUTTON_DPAD_RIGHT,"walk-right" );
	inputManager->AddInputMapping(SDL_CONTROLLER_AXIS_RIGHTX,"walk-right" );

	inputManager->AddInputMapping(SDLK_UP,"walk-up" );
	inputManager->AddInputMapping(SDL_CONTROLLER_BUTTON_DPAD_UP,"walk-up" );
	inputManager->AddInputMapping(SDL_CONTROLLER_AXIS_RIGHTY,"walk-up" );

	inputManager->AddInputMapping(SDLK_DOWN,"walk-down" );
	inputManager->AddInputMapping(SDL_CONTROLLER_BUTTON_DPAD_DOWN,"walk-down" );
	inputManager->AddInputMapping(SDL_CONTROLLER_AXIS_LEFTY,"walk-down" );
}
