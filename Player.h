#pragma once
#include "Vector2.h"

struct Player
{
public:
	Vector2 pos;
	Vector2 radius;
	Vector2 speed;
	Vector2 acceleration;
    char keys[256];

public:
	void Initialize();
	void Update();
	void Draw();
};