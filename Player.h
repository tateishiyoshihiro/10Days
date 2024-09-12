#pragma once
#include "Vector2.h"
#include "Map.h"

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

	// life
	int life;
	bool isAlive;
	int lifeTime;
	int lifeTimer;
	bool collisionInvalid;
	bool isGorl;

public:
	void Initialize();
	void Update();
	void Draw();

	bool CheckCircleRectCollision(int circleX, int circleY, int circleRadius,
		int rectX1, int rectY1, int rectX2, int rectY2);

private:
	int map2[mapCountY][mapCountX] = { 0 };
};