#include "FallEnemy.h"
#include "Novice.h"
#include "Player.h"
#include "math.h"

void FallEnemy::Initialize()
{
	fall = Novice::LoadTexture("./Resources/fall.png");
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

	// プレイヤーと落下する敵の当たり判定
	if (IsCircleCollidingWithRect2(player->pos.x, player->pos.y, player->radius.x,
		FallEnemyPos.x, FallEnemyPos.y, FallEnemyW, FallEnemyH)) {
		// 衝突した場合の処理
		if (!player->collisionInvalid) {
			player->life--;
			player->collisionInvalid = true;
		}
	}
	if (player->life <= 0) {
		player->isAlive = false;
	}

	if (player->collisionInvalid) {
		player->lifeTimer--;
	}

	if (player->lifeTimer <= 0) {
		player->collisionInvalid = false;
		 player->lifeTimer = player->lifeTimer;
	}

	Novice::ScreenPrintf(0, 0, "Player Y: %f", player->pos.y);
	Novice::ScreenPrintf(0, 20, "Enemy Y: %f", FallEnemyPos.y);
	Novice::ScreenPrintf(0, 40, "Distance: %f", distance);
	
}

void FallEnemy::Draw()
{
	Novice::DrawQuad(
		(int)FallEnemyPos.x,
		(int)FallEnemyPos.y,
		(int)FallEnemyPos.x+32,
		(int)FallEnemyPos.y,
		(int)FallEnemyPos.x,
		(int)FallEnemyPos.y+32,
		(int)FallEnemyPos.x+32,
		(int)FallEnemyPos.y+32,
		0,
		0,
		32, 
		32, 
		fall,0xFFFFFFFF);
}

float FallEnemy::DistanceToPlayer(Player* player)
{
	// プレイヤーとの距離を計算
	float dx = player->pos.x - FallEnemyPos.x;
	float dy = player->pos.y - FallEnemyPos.y;
	return sqrtf(dx * dx + dy * dy);
}

bool FallEnemy::IsCircleCollidingWithRect2(float circleX, float circleY, float radius, float rectX, float rectY, float rectW, float rectH)
{
	// 円の中心から矩形の最も近い点を探す
	float closestX = fmaxf(rectX, fminf(circleX, rectX + rectW));
	float closestY = fmaxf(rectY, fminf(circleY, rectY + rectH));

	// 円の中心と矩形の最も近い点の距離を計算
	float distanceX = circleX - closestX;
	float distanceY = circleY - closestY;

	// 距離の二乗と円の半径の二乗を比較
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (radius * radius);
}
