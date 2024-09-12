#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<Novice.h>
#include <iostream>
#include <algorithm>
#include"MapOpen.h"

void Player::Initialize()
{
	pos.x = 50;
	pos.y = 50;
	speed.x = 3;
	speed.y = 0;
	acceleration.x = 0.05f;
	acceleration.y = 0.1f;
	radius.x = 16;
	radius.y = 16;

	theta = 0.0f;
	w = 32;
	h = 32;
	leftTopPos.x = -w / 2;
	leftTopPos.y = -h / 2;
	rightTopPos.x = w / 2;
	rightTopPos.y = -h / 2;
	leftDownPos.x = -w / 2;
	leftDownPos.y = h / 2;
	rightDownPos.x = w / 2;
	rightDownPos.y = h / 2;

	leftTopRotated.x = 0.0f;
	leftTopRotated.y = 0.0f;
	rightTopRotated.x = w / 2;
	rightTopRotated.y = 0.0f;
	leftDownRotated.x = 0.0f;
	leftDownRotated.y = h / 2;
	rightDownRotated.x = w / 2;
	rightDownRotated.y = h / 2;
	grHandle = Novice::LoadTexture("white1x1.png"); //プレイヤーの画像に入れ替える
	MapOpen(map2);
	life = 3;
	isAlive = true;
	lifeTime = 30;
	lifeTimer = lifeTime;
	collisionInvalid = false;
	isGorl = false;
}

void Player::Update()
{
	// フラグのリセット
	bool collidedLeft = false;
	bool collidedRight = false;

	Novice::GetHitKeyStateAll(keys);

	// プレイヤーが重力で落ちる
	if (speed.x <= 5.0f) {
		speed.y -= acceleration.y;
		pos.y -= speed.y;
	}

	if (speed.x >= 6.0f) {
		speed.x = 6.0f;
	}
	// マップとの衝突判定 (下方向の衝突判定)
	int mapTileY = (int)((pos.y + radius.y) / mapTipSize);  // プレイヤーの底が接するマップチップのY座標
	int mapTileX = (int)(pos.x / mapTipSize);               // プレイヤーのX座標のマップチップ

	// プレイヤーがいるマップチップ
	int mapTile = (int)(pos.y / mapTipSize);
	// プレイヤーの下にマップチップが存在するか確認
	if (map2[mapTileY][mapTileX] == BLOCK) // マップが "BLOCK" の場合
	{
		// プレイヤーのY座標をマップのブロックの上に固定
		pos.y = mapTileY * mapTipSize - radius.y;

		// Y方向の速度を0にする (落下を停止)
		speed.y = 0;
	}

	if (keys[DIK_A])
	{
		theta -= 0.1f;
		speed.x += acceleration.x;
		pos.x -= speed.x;

		// プレイヤーの移動方向が左なので、左のマップチップと衝突するかを確認
		for (int y = 0; y < mapCountY; y++)
		{
			for (int x = 0; x < mapCountX; x++) {
				if (map2[y][x] == 1) {
					int rectX1 = x * mapTipSize;
					int rectY1 = y * mapTipSize;
					int rectX2 = rectX1 + mapTipSize;
					int rectY2 = rectY1 + mapTipSize;

					// 円の中心よりも左側のマップチップと衝突判定
					if (pos.x - radius.x < rectX2 && pos.x > rectX1 &&
						CheckCircleRectCollision((int)pos.x, (int)pos.y, (int)radius.x, (int)rectX1, (int)rectY1, (int)rectX2, (int)rectY2)) {
						collidedLeft = true; // 左側の衝突
						pos.x = rectX2 + radius.x; // プレイヤーの位置を修正
					}
				}
			}
		}


	}
	else if (keys[DIK_D])
	{
		theta += 0.1f;
		speed.x += acceleration.x;
		pos.x += speed.x;

		// プレイヤーの移動方向が右なので、右のマップチップと衝突するかを確認
		for (int y = 0; y < mapCountY; y++) {
			for (int x = 0; x < mapCountX; x++) {
				if (map2[y][x] == 1) {
					int rectX1 = x * mapTipSize;
					int rectY1 = y * mapTipSize;
					int rectX2 = rectX1 + mapTipSize;
					int rectY2 = rectY1 + mapTipSize;

					// 円の中心よりも右側のマップチップと衝突判定
					if (pos.x + radius.x > rectX1 && pos.x < rectX2 &&
						CheckCircleRectCollision((int)pos.x, (int)pos.y, (int)radius.x, rectX1, rectY1, rectX2, rectY2)) {
						collidedRight = true; // 右側の衝突
						pos.x = rectX1 - radius.x; // プレイヤーの位置を修正
					}
				}
			}
		}
	}
	else {
		speed.x = 3.0f;
	}

	// 衝突時の速度制御
	if (collidedLeft) {
		// 左に衝突した場合、左方向への移動を止める
		if (keys[DIK_A]) {
			pos.x += speed.x;  // 衝突していたら移動を元に戻す
		}
		speed.x = 3.0f;
	}
	if (collidedRight) {
		// 右に衝突した場合、右方向への移動を止める
		if (keys[DIK_D]) {
			pos.x -= speed.x;  // 衝突していたら移動を元に戻す
		}
		speed.x = 3.0f;
	}

	if (map2[mapTileY][mapTileX] == OBSTACLE) // マップが "OBSTACLE" の場合
	{
		if (!collisionInvalid) {
			life--;
			collisionInvalid = true;
		}

	}

	if (life <= 0) {
		isAlive = false;
	}

	if (collisionInvalid) {
		lifeTimer--;
	}

	if (lifeTimer <= 0) {
		collisionInvalid = false;
		lifeTimer = lifeTime;
	}


	if (map2[mapTile][mapTileX] == NEST) // マップが "OBSTACLE" の場合
	{
		isGorl = true;

	}
	leftTopRotated.x = (leftTopPos.x * cosf(theta) - leftTopPos.y * sinf(theta)) + pos.x;
	leftTopRotated.y = (leftTopPos.y * cosf(theta) + leftTopPos.x * sinf(theta)) + pos.y;
	rightTopRotated.x = (rightTopPos.x * cosf(theta) - rightTopPos.y * sinf(theta)) + pos.x;
	rightTopRotated.y = (rightTopPos.y * cosf(theta) + rightTopPos.x * sinf(theta)) + pos.y;
	leftDownRotated.x = (leftDownPos.x * cosf(theta) - leftDownPos.y * sinf(theta)) + pos.x;
	leftDownRotated.y = (leftDownPos.y * cosf(theta) + leftDownPos.x * sinf(theta)) + pos.y;
	rightDownRotated.x = (rightDownPos.x * cosf(theta) - rightDownPos.y * sinf(theta)) + pos.x;
	rightDownRotated.y = (rightDownPos.y * cosf(theta) + rightDownPos.x * sinf(theta)) + pos.y;
}

void Player::Draw()
{
	// 当たり判定するようの円
	Novice::DrawEllipse((int)pos.x, (int)pos.y, (int)radius.x, (int)radius.y, 0.0f, WHITE, kFillModeSolid);

	Novice::DrawQuad((int)leftTopRotated.x, (int)leftTopRotated.y,
		(int)rightTopRotated.x, (int)rightTopRotated.y,
		(int)leftDownRotated.x, (int)leftDownRotated.y,
		(int)rightDownRotated.x, (int)rightDownRotated.y,
		0, 0,
		(int)w, (int)h,
		grHandle,
		WHITE);
}

bool Player::CheckCircleRectCollision(int circleX, int circleY, int circleRadius, int rectX1, int rectY1, int rectX2, int rectY2)
{
	// 円の中心から矩形に最も近い点を求める
	int closestX = (std::max)(rectX1, (std::min)(circleX, rectX2));
	int closestY = (std::max)(rectY1, (std::min)(circleY, rectY2));
	// 円の中心とその点との距離を計算
	int dx = circleX - closestX;
	int dy = circleY - closestY;
	int distanceSquared = dx * dx + dy * dy;

	// 距離が円の半径の2乗より小さいか確認
	return distanceSquared < (circleRadius * circleRadius);
}
