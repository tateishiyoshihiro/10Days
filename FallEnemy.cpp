#include "FallEnemy.h"
#include "Novice.h"
#include "Player.h"
#include "math.h"

void FallEnemy::Initialize()
{
	FallEnemyPos.x = 550.0f;
	FallEnemyPos.y = 193.0f;
	FallEnemyW = 32.0f;
	FallEnemyH = 32.0f;
	isFalling = false;
	fallSpeed.x = 0.0f;
	fallSpeed.y = 2.0f;
	detectionRange = 150.0f;

	initialPosition = FallEnemyPos; // 初期位置を保存
	resetTimer = 0;
	resetDuration = 120;
}

void FallEnemy::Update(Player* player)
{

	// プレイヤーとの距離を計算
	float distance = DistanceToPlayer(player);

	// プレイヤーが敵の下にいて、かつ距離が検出範囲内にいる場合にのみ落下を開始
	if (distance <= detectionRange && player->pos.y > FallEnemyPos.y) {
		isFalling = true;
	}
	// 敵が落下している場合
	if (isFalling) {
		FallEnemyPos.y += fallSpeed.y;
	}
	// 地面に到達したら止まる処理
	if (FallEnemyPos.y > 300) {
		isFalling = false;

		// 落下後、一定時間経過したら元の位置に戻る
		resetTimer++;
		if (resetTimer >= resetDuration) {
			FallEnemyPos = initialPosition; // 元の位置に戻す
			resetTimer = 0;
		}
	}

	Novice::ScreenPrintf(0, 0, "Player Y: %f", player->pos.y);
	Novice::ScreenPrintf(0, 20, "Enemy Y: %f", FallEnemyPos.y);
	Novice::ScreenPrintf(0, 40, "Distance: %f", distance);

}

void FallEnemy::Draw()
{
	Novice::DrawBox((int)FallEnemyPos.x, (int)FallEnemyPos.y, (int)FallEnemyW, (int)FallEnemyH, 0.0f, RED, kFillModeSolid);
}

float FallEnemy::DistanceToPlayer(Player* player)
{
	// プレイヤーとの距離を計算
	float dx = player->pos.x - FallEnemyPos.x;
	float dy = player->pos.y - FallEnemyPos.y;
	return sqrtf(dx * dx + dy * dy);
}
