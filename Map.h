#pragma once
const int mapCountX = 25;
const int mapCountY = 25;
//const int mapSizeY = 25;
const int mapTipSize = 32;

enum MapNum {
	NONE,
	BLOCK,
	OBSTACLE,
	NEST,
	POISON,
};

struct Map
{
public:
	void Initialize();
	void Update();
	void Draw();

public:
	int map[mapCountY][mapCountX] = { 0 };

	int box;
	int obstacle;
	int nest;
	int poison;
};