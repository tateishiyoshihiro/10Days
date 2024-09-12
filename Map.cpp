#include <Novice.h>
#include "Map.h"
#include"MapOpen.h"

void Map::Initialize() {
	box = Novice::LoadTexture("./Resources/wall.png");
	obstacle = Novice::LoadTexture("./Resources/sky.png");
	MapOpen(map);
}

void Map::Update() {

}

void Map::Draw() {
	for (int y = 0; y < mapCountY; y++) {
		for (int x = 0; x < mapCountX; x++) {
			if (map[y][x] == 1) {
				Novice::DrawQuad(
					0 + x * mapTipSize, 0 + y * mapTipSize, mapTipSize + x * mapTipSize, 0 + y * mapTipSize,
					0 + x * mapTipSize, mapTipSize + y * mapTipSize, mapTipSize + x * mapTipSize, mapTipSize + y * mapTipSize,
					0, 0, mapTipSize, mapTipSize,
					box,
					0xFFFFFFFF
				);
			}
			else if (map[y][x] == 2) {
				Novice::DrawQuad(
					0 + x * mapTipSize, 0 + y * mapTipSize, mapTipSize + x * mapTipSize, 0 + y * mapTipSize,
					0 + x * mapTipSize, mapTipSize + y * mapTipSize, mapTipSize + x * mapTipSize, mapTipSize + y * mapTipSize,
					0, 0, mapTipSize, mapTipSize,
					obstacle,
					0xFFFFFFFF
				);
			}
		}
	}
}
