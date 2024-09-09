#pragma once
#include "Vector2.h"

struct Player
{
public:
	Vector2 pos;
	Vector2 radius;
	Vector2 speed;
	Vector2 acceleration; // 重力
    char keys[256];

	float w;
	float h;
	Vector2 leftTopPos;
	Vector2 rightTopPos;
	Vector2 leftDownPos;
	Vector2 rightDownPos;
	float theta;
	Vector2 leftTopRotated;
	Vector2 rightTopRotated;
	Vector2 leftDownRotated;
	Vector2 rightDownRotated;
	int grHandle;

public:
	void Initialize();
	void Update();
	void Draw();
};