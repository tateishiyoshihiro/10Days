#include<Novice.h>
#include"MapOpen.h"
#include<stdio.h>
#include<string.h>

void MapOpen(int map[mapCountX][mapCountY]) {
	FILE* fp = NULL;
	char fname[] = "Resources/mapSample.csv";

	fopen_s(&fp, fname, "rt");
	char str[256];
	char* ch;
	char* dastBox;

	if (fp == NULL) {
		return;
	}


	for (int i = 0; i < mapCountY; i++) {
		fgets(str, 256, fp);
		ch = strtok_s(str, ",", &dastBox);
		for (int l = 0; l < mapCountX; l++) {
			if (ch == NULL) {
				break;
			}
			else {
				map[i][l] = atoi(ch);
			}
			ch = strtok_s(NULL, ",", &dastBox);
		}
	}
	fclose(fp);
}