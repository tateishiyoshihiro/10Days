#include "Player.h"
#include<Novice.h>

void Player::Initialize()
{
	pos.x = 640;
	pos.y = 390;
	speed.x = 5;
	speed.y = 0;
	acceleration.x = 0;
	acceleration.y = 0.8f;
	radius.x = 10;
	radius.y = 10;
}

void Player::Update()
{
	Novice::GetHitKeyStateAll(keys);

	// プレイヤーがラインより奥に移動すると落ちる
	if (pos.x > 1100)
	{
		speed.y -= acceleration.y;
		pos.y -= speed.y;
	}

	if (keys[DIK_A])
	{
		pos.x -= speed.x;
	}
	if (keys[DIK_D])
	{
		pos.x += speed.x;
	}
}

void Player::Draw()
{
	Novice::DrawEllipse((int)pos.x, (int)pos.y, (int)radius.x, (int)radius.y, 0.0f, WHITE, kFillModeSolid);
}