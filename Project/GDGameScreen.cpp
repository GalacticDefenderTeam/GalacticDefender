#include "GDGameScreen.h"
#include "DinoRestartMenuScreen.h"


Engine::GDGameScreen::GDGameScreen()
{
}
Engine::GDGameScreen::~GDGameScreen()
{
	for (Sprite* s : middlegrounds) delete s;
	for (Sprite* s : foregrounds) delete s;
	delete dotTexture;
	delete shipSprite;
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
	
	//Create background
	for (int i = 1; i <= 1; i++) {
		AddToLayer(middlegrounds, "bgspace" + to_string(i) + ".png");
	}
	for (int i = 2; i <= 2; i++) {
		AddToLayer(foregrounds, "bgspace" + to_string(i) + ".png");
	}

	offset = 2;

	Texture* shipTexture = new Texture("Result.png");

	shipSprite = new Sprite(shipTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	shipSprite->SetRotation(90.0f)->SetPosition(750, 50)->SetNumXFrames(15)->SetNumYFrames(10)->SetAnimationDuration(70)->SetScale(1.2f)->AddAnimation("idle", 45, 49)->AddAnimation("up", 60, 63)->AddAnimation("left", 90, 92)->AddAnimation("right", 105, 107);
	shipSprite->SetBoundingBoxSize(shipSprite->GetScaleWidth() - (43 * shipSprite->GetScale()),
		shipSprite->GetScaleHeight() - (4 * shipSprite->GetScale()));


	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite2 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite3 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite4 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());


	// Add input mapping 
	game->GetInputManager()->AddInputMapping(SDLK_UP,"Up" )->AddInputMapping(SDLK_DOWN,"Down" )->AddInputMapping(SDLK_x, "Attack")->AddInputMapping(SDLK_RIGHT,"Right" )->AddInputMapping(SDLK_LEFT,"Left" );

	// Playing music
	music = (new Music("2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.ogg"))->SetVolume(40)->Play(true);

	//sound = (new Sound("jump.wav"))->SetVolume(100);

	textScore = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	textGameOver = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	textRestart = new Text("lucon.ttf", 24, game->GetDefaultTextShader());

	int offset = 20; // Atur offset sesuai kebutuhan
	textScore->SetScale(2.0f)->SetColor(255, 255, 255)->SetPosition(50, game->GetSettings()->screenHeight - (textScore->GetFontSize() * textScore->GetScale()) - offset);
	//Set the background color
	game->SetBackgroundColor(0, 0, 0);
	// Set debug
	debug = false;

	// Add input mappings
	game->GetInputManager()->AddInputMapping(SDLK_ESCAPE,"mainmenu" );

}

void Engine::GDGameScreen::ResetGameState() {
	// Reset posisi monster dan kecepatan
	shipSprite->SetPosition(90, 0);


	// Reset skor dan timer
	score = 0;
	scoreUpdateTime = 0;


}

void Engine::GDGameScreen::Update()
{
	MoveLayer(middlegrounds, 0.03f);
	MoveLayer(foregrounds, 0.09f);


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
		shipSprite->PlayAnim("idle");

		// Move monster sprite using keyboard
		vec2 oldMonsterPos = shipSprite->GetPosition();
		float x = oldMonsterPos.x, y = oldMonsterPos.y;

		float monsterWidth = shipSprite->GetScaleWidth();
		float monsterHeight = shipSprite->GetScaleHeight();

		// Dapatkan lebar dan tinggi layar
		float screenWidth = game->GetSettings()->screenWidth;
		float screenHeight = game->GetSettings()->screenHeight;

		if (game->GetInputManager()->IsKeyPressed("Right")) {
			x += 0.5f * game->GetGameTime();
			shipSprite->PlayAnim("right");
		}

		if (game->GetInputManager()->IsKeyPressed("Left")) {
			x -= 0.5f * game->GetGameTime();
			shipSprite->PlayAnim("left");
		}
		if (game->GetInputManager()->IsKeyPressed("Up")) {
			y += 0.5f * game->GetGameTime();
			shipSprite->PlayAnim("up");
		}
		if (game->GetInputManager()->IsKeyPressed("Down")) {
			y -= 0.5f * game->GetGameTime();
			shipSprite->PlayAnim("down");
		}

		// Batasi posisi agar tidak keluar layar
		x = std::max(0.0f, std::min(x, screenWidth - monsterWidth));
		y = std::max(0.0f, std::min(y, screenHeight - monsterHeight));

		shipSprite->SetPosition(x, y);

		if (game->GetInputManager()->IsKeyPressed("Attack")) {
			shipSprite->PlayAnim("attack");
		}
		// Update monster sprite animation
		shipSprite->Update(game->GetGameTime());
	

		if (debug) {
			//Shape for debug
			BoundingBox* bb = shipSprite->GetBoundingBox();
			dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()), bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
			dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()), bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
			dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()), bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
			dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()), bb->GetVertices()[3].y - (0.5f * dotSprite4->GetScaleHeight()));

		}
	}

void Engine::GDGameScreen::Draw()
{
	DrawLayer(middlegrounds);
	DrawLayer(foregrounds);
	textScore->Draw();
	textGameOver->Draw();
	textRestart->Draw();


	shipSprite->Draw();

	if (debug) {
		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();
	}
}
void Engine::GDGameScreen::MoveLayer(vector<Sprite*>& bg, float speed)
{
	for (Sprite* s : bg) {
		if (s->GetPosition().y < -game->GetSettings()->screenHeight + offset) {
			s->SetPosition(0,game->GetSettings()->screenHeight + offset - 2.5);
		}
		s->SetPosition(s->GetPosition().x, s->GetPosition().y - speed * game->GetGameTime());
		s->Update(game->GetGameTime());
	}
}

void Engine::GDGameScreen::DrawLayer(vector<Sprite*>& bg)
{
	for (Sprite* s : bg) {
		s->Draw();
	}
}

void Engine::GDGameScreen::AddToLayer(vector<Sprite*>& bg, const std::string& name)
{
	Texture* texture = new Texture(name);

	// Sprite pertama: letakkan di posisi layar atas
	Sprite* s1 = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s1->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight + offset);
	bg.push_back(s1);

	// Sprite kedua: posisikan di bawah sprite pertama
	Sprite* s2 = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s2->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight + offset);
	s2->SetPosition(0, -game->GetSettings()->screenHeight + offset);  // letakkan tepat di bawah s1
	bg.push_back(s2);

}
