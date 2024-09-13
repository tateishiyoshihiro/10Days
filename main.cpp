#include <Novice.h>
#include "Player.h"
#include<stdio.h>
#include"MapOpen.h"
#include"Map.h"
#include"Vector2.h"
#include "FallEnemy.h"

const char kWindowTitle[] = "卵の帰還";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1000, 800);


	enum SCENE {
		Title,
		Game,
		GameClear,
		GameOver,
	};

	SCENE scene = Title;

	Player* player = new Player();
	player->Initialize();

	FallEnemy* fallEnemy = new FallEnemy();
	fallEnemy->Initialize();

	Map* map = new Map();
	map->Initialize();

	struct Line
	{
		Vector2 start;
		Vector2 end;
		unsigned int color;
	};

	Line line
	{
		{0.0f,400.0f},
		{1100.0f,400.0f},
		WHITE
	};

	int TitlePng = Novice::LoadTexture("./Resources/title.png");
	int back = Novice::LoadTexture("./Resources/back.png");
	int over = Novice::LoadTexture("./Resources/over.png");
	int clear = Novice::LoadTexture("./Resources/clear.png");

	int soundHandle1; // 決定音
	soundHandle1 = Novice::LoadAudio("./Resources/determine.wav");

	//int map[mapCountY][mapCountX] = { 0 };

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		
		///
		/// ↓更新処理ここから
		///

		switch (scene) {
		case Title:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = Game;
				player->Initialize();

				if (!Novice::IsPlayingAudio(soundHandle1)) {
					Novice::PlayAudio(soundHandle1, false, 1.0f);
				}
			}
			break;
		case Game:
			player->Update();
			fallEnemy->Update(player);
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				if (player->isGorl) {
					scene = GameClear;

					if (!Novice::IsPlayingAudio(soundHandle1)) {
						Novice::PlayAudio(soundHandle1, false, 1.0f);
					}
				}	
			}
			if (player->isAlive == false) {
				scene = GameOver;
			}
			break;
		case GameClear:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = Title;

				if (!Novice::IsPlayingAudio(soundHandle1)) {
					Novice::PlayAudio(soundHandle1, false, 1.0f);
				}
			}
			break;
		case GameOver:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = Title;

				if (!Novice::IsPlayingAudio(soundHandle1)) {
					Novice::PlayAudio(soundHandle1, false, 1.0f);
				}
			}
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (scene) {
		case Title:
			Novice::DrawSprite(0, 0, TitlePng, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			break;
		case Game:
			Novice::DrawSprite(0, 0, back, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			player->Draw();
			fallEnemy->Draw();
			map->Draw();

			break;
		case GameClear:
			Novice::DrawSprite(0, 0, clear, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			break;
		case GameOver:
			Novice::DrawSprite(0, 0, over, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			break;
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
