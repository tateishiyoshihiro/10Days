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
	Novice::Initialize(kWindowTitle, 1280, 720);

	enum SCENE {
		Title,
		Game,
		GameClear,
		GameOver,
	};

	SCENE scene = Title;

	Player* player = new Player();
	player->Initialize();

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

	int map[mapCountY][mapCountX] = { 0 };

	int box = Novice::LoadTexture("./Resources/wall.png");
	int obstacle = Novice::LoadTexture("./Resources/sky.png");



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
			MapOpen(map);
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = Game;
			}
			break;
		case Game:
			player->Update();
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = GameClear;
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
			for (int y = 0; y < mapCountY; y++) {
				for (int x = 0; x < mapCountX; x++) {
					if (map[y][x] == 1) {
						Novice::DrawQuad(
							0 + x * mapTipSize, 0 + y * mapTipSize, mapTipSize + x * mapTipSize, 0 + y * mapTipSize,
							0 + x * mapTipSize, mapTipSize + y * mapTipSize, mapTipSize + x * mapTipSize, mapTipSize + y * mapTipSize,
							0, 0, mapTipSize, mapTipSize,
							box,
							0xFFFFFFFF
						);
					}
					else if (map[y][x] == 2) {
						Novice::DrawQuad(
							0 + x * mapTipSize, 0 + y * mapTipSize, mapTipSize + x * mapTipSize, 0 + y * mapTipSize,
							0 + x * mapTipSize, mapTipSize + y * mapTipSize, mapTipSize + x * mapTipSize, mapTipSize + y * mapTipSize,
							0, 0, mapTipSize, mapTipSize,
							obstacle,
							0xFFFFFFFF
						);
					}
				}
			}
			break;
		case Game:
			player->Draw();
			for (int y = 0; y < mapCountY; y++) {
				for (int x = 0; x < mapCountX; x++) {
					if (map[y][x] == 1) {
						Novice::DrawQuad(
							0 + x * mapTipSize, 0 + y * mapTipSize, mapTipSize + x * mapTipSize, 0 + y * mapTipSize,
							0 + x * mapTipSize, mapTipSize + y * mapTipSize, mapTipSize + x * mapTipSize, mapTipSize + y * mapTipSize,
							0, 0, mapTipSize, mapTipSize,
							box,
							0xFFFFFFFF
						);
					}
					else if (map[y][x] == 2) {
						Novice::DrawQuad(
							0 + x * mapTipSize, 0 + y * mapTipSize, mapTipSize + x * mapTipSize, 0 + y * mapTipSize,
							0 + x * mapTipSize, mapTipSize + y * mapTipSize, mapTipSize + x * mapTipSize, mapTipSize + y * mapTipSize,
							0, 0, mapTipSize, mapTipSize,
							obstacle,
							0xFFFFFFFF
						);
					}
				}
			}
			
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
