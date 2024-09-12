#include <Novice.h>
#include "Player.h"
#include<stdio.h>
#include"MapOpen.h"
#include"Map.h"
#include"Vector2.h"

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
			}
			break;
		case Game:
			player->Update();
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = GameClear;
			}
			if (player->isAlive == false) {
				scene = GameOver;
			}
			break;
		case GameClear:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = Title;
			}
			break;
		case GameOver:
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
			
			break;
		case Game:
			player->Draw();
			
			map->Draw();
			break;
		case GameClear:
			break;
		case GameOver:
			
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
