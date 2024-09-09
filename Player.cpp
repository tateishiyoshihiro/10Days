#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<Novice.h>

void Player::Initialize()
{
	pos.x = 640;
	pos.y = 390;
	speed.x = 5;
	speed.y = 0;
	acceleration.x = 0;
	acceleration.y = 0.8f;
	radius.x = 32;
	radius.y = 32;

	theta = 0.0f;
	w = 63;
	h = 63;
	leftTopPos.x =  -w / 2;
	leftTopPos.y =  -h / 2;
	rightTopPos.x =  w / 2;
	rightTopPos.y = -h / 2;
	leftDownPos.x = -w / 2;
	leftDownPos.y =  h / 2;
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
		theta -= 0.1f;
		pos.x -= speed.x;
	}
	if (keys[DIK_D])
	{
		theta += 0.1f;
		pos.x += speed.x;
	}

	leftTopRotated.x = (leftTopPos.x * cosf(theta) - leftTopPos.y * sinf(theta)) + pos.x;
	leftTopRotated.y = (leftTopPos.y * cosf(theta) + leftTopPos.x * sinf(theta)) + pos.y;
	rightTopRotated.x = (rightTopPos.x * cosf(theta) - rightTopPos.y * sinf(theta)) + pos.x;
	rightTopRotated.y = (rightTopPos.y * cosf(theta) + rightTopPos.x * sinf(theta)) + pos.y;
	leftDownRotated.x = (leftDownPos.x * cosf(theta) - leftDownPos.y * sinf(theta)) + pos.x;
	leftDownRotated.y = (leftDownPos.y * cosf(theta) + leftDownPos.x * sinf(theta)) + pos.y;
	rightDownRotated.x = (rightDownPos.x * cosf(theta) - rightDownPos.y * sinf(theta)) + pos.x;
	rightDownRotated.y = (rightDownPos.y * cosf(theta) + rightDownPos.x * sinf(theta)) + pos.y;

	/*leftTopRotated.x += 63;
	leftTopRotated.y += 63;
	rightTopRotated.x += 63;
	rightTopRotated.y += 63;
	leftDownRotated.x += 63;
	leftDownRotated.y += 63;
	rightDownRotated.x += 63;
	rightDownRotated.y += 63;*/

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