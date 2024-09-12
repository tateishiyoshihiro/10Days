#pragma once
#include "Vector2.h"
#include "Player.h"

struct FallEnemy
{
private:
	Vector2 FallEnemyPos;
	Vector2 initialPosition;  // 元の位置を保存
	float FallEnemyW;
	float FallEnemyH;
	bool isFalling;       // 敵が落下しているかどうか
	Vector2 fallSpeed;    // 落下速度
	float detectionRange; // プレイヤーを検出する範囲
	int resetTimer;   // 元の位置に戻るまでの時間を計測
	int resetDuration; // 敵が元の位置に戻るまでの待機時間

public:
	void Initialize();
	void Update(Player* player);
	void Draw();

	float DistanceToPlayer(Player* player);
	bool IsCircleCollidingWithRect2(float circleX, float circleY, float radius,
		float rectX, float rectY, float rectW, float rectH);
};