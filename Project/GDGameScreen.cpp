#include "GDGameScreen.h"
#include "DinoRestartMenuScreen.h"


Engine::GDGameScreen::GDGameScreen()
{
}
Engine::GDGameScreen::~GDGameScreen()
{

	delete dotTexture;
	delete monsterSprite;
	delete dotSprite1;
	delete dotSprite2;
	delete dotSprite3;
	delete dotSprite4;
	delete music;
	delete sound;
	delete textScore;
	delete textGameOver;
	delete textRestart;

}

void Engine::GDGameScreen::Init()
{
	

	Texture* monsterTexture = new Texture("Dino.png");

	monsterSprite = new Sprite(monsterTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	monsterSprite->SetPosition(90, 0)->SetNumXFrames(24)->SetNumYFrames(1)->SetAnimationDuration(70)->SetScale(5.0f)->AddAnimation("attack", 13, 14)->AddAnimation("idle", 17, 20)->AddAnimation("run", 17, 20)->AddAnimation("jump", 17, 20);
	monsterSprite->SetBoundingBoxSize(monsterSprite->GetScaleWidth() - (43 * monsterSprite->GetScale()),
		monsterSprite->GetScaleHeight() - (4 * monsterSprite->GetScale()));


	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite2 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite3 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite4 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());


	// Add input mapping 
	game->GetInputManager()->AddInputMapping("Up", SDLK_UP)->AddInputMapping("Down", SDLK_DOWN)->AddInputMapping("Attack", SDLK_x)->AddInputMapping("Right", SDLK_RIGHT)->AddInputMapping("Left", SDLK_LEFT);

	// Playing music
	music = (new Music("2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.ogg"))->SetVolume(40)->Play(true);

	sound = (new Sound("jump.wav"))->SetVolume(100);

	textScore = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	textGameOver = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	textRestart = new Text("lucon.ttf", 24, game->GetDefaultTextShader());

	int offset = 20; // Atur offset sesuai kebutuhan
	textScore->SetScale(2.0f)->SetColor(0, 0, 0)->SetPosition(50, game->GetSettings()->screenHeight - (textScore->GetFontSize() * textScore->GetScale()) - offset);
	//Set the background color
	game->SetBackgroundColor(102, 195, 242);
	// Set debug
	debug = false;

	// Add input mappings
	game->GetInputManager()->AddInputMapping("mainmenu", SDLK_ESCAPE);

}

void Engine::GDGameScreen::ResetGameState() {
	// Reset posisi monster dan kecepatan
	monsterSprite->SetPosition(90, 0);


	// Reset skor dan timer
	score = 0;
	scoreUpdateTime = 0;


}

void Engine::GDGameScreen::Update()
{

		if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
			// Mengatur ScreenManager untuk beralih ke layar menu utama
			ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
		}
		scoreUpdateTime += game->GetGameTime();  // Hitung waktu berlalu
		if (scoreUpdateTime >= 500) {      // Tambahkan skor setiap 500ms
			score += 1;
			scoreUpdateTime = 0;           // Reset timer
		}

		textScore->SetText("Score: " + std::to_string(score));
		monsterSprite->PlayAnim("idle");

		// Move monster sprite using keyboard
		vec2 oldMonsterPos = monsterSprite->GetPosition();
		float x = oldMonsterPos.x, y = oldMonsterPos.y;

		float monsterWidth = monsterSprite->GetScaleWidth();
		float monsterHeight = monsterSprite->GetScaleHeight();

		// Dapatkan lebar dan tinggi layar
		float screenWidth = game->GetSettings()->screenWidth;
		float screenHeight = game->GetSettings()->screenHeight;

		if (game->GetInputManager()->IsKeyPressed("Right")) {
			x += 0.5f * game->GetGameTime();
			monsterSprite->PlayAnim("run")->SetFlipHorizontal(false);
		}

		if (game->GetInputManager()->IsKeyPressed("Left")) {
			x -= 0.5f * game->GetGameTime();
			monsterSprite->PlayAnim("run")->SetFlipHorizontal(false);
		}
		if (game->GetInputManager()->IsKeyPressed("Up")) {
			y += 0.5f * game->GetGameTime();
			monsterSprite->PlayAnim("run")->SetFlipHorizontal(false);
		}
		if (game->GetInputManager()->IsKeyPressed("Down")) {
			y -= 0.5f * game->GetGameTime();
			monsterSprite->PlayAnim("run")->SetFlipHorizontal(false);
		}

		// Batasi posisi agar tidak keluar layar
		x = std::max(0.0f, std::min(x, screenWidth - monsterWidth));
		y = std::max(0.0f, std::min(y, screenHeight - monsterHeight));

		monsterSprite->SetPosition(x, y);

		if (game->GetInputManager()->IsKeyPressed("Attack")) {
			monsterSprite->PlayAnim("attack");
		}
		// Update monster sprite animation
		monsterSprite->Update(game->GetGameTime());
	

		if (debug) {
			//Shape for debug
			BoundingBox* bb = monsterSprite->GetBoundingBox();
			dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()), bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
			dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()), bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
			dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()), bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
			dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()), bb->GetVertices()[3].y - (0.5f * dotSprite4->GetScaleHeight()));

		}
	}

void Engine::GDGameScreen::Draw()
{
	textScore->Draw();
	textGameOver->Draw();
	textRestart->Draw();


	monsterSprite->Draw();

	if (debug) {
		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();
	}
}