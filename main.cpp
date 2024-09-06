#include <Novice.h>
#include<stdio.h>
#include"MapOpen.h"
#include"Map.h"
#include"Vector2.h"

const char kWindowTitle[] = "LE2D_10_タテイシ_ヨシヒロ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		int map[mapCountY][mapCountX] = { 0 };

		int box = Novice::LoadTexture("./Resources/box.png");

		///
		/// ↓更新処理ここから
		///

		MapOpen(map);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int y = 0; y < mapCountY; y++) {
			for (int x = 0; x < mapCountX; x++) {
				if (map[y][x] == 1) {
					Novice::DrawQuad(
						0 + x * mapTipSize, 0 + y * mapTipSize, mapTipSize + x * mapTipSize, 0 + y * mapTipSize,
						0 + x * mapTipSize, mapTipSize + y * mapTipSize, mapTipSize + x * mapTipSize, mapTipSize + y * mapTipSize,
						0, 0, mapTipSize, mapTipSize,
						box,
						0xaa77aaFF
					);
				}
			}
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
