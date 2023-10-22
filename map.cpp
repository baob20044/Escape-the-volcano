#include "map.h"
void GameMap::LoadMap(char* name) {
	//Doc file map
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) {
		return;
	}
	//Khoi tao kich thuoc map
	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;
	//Kich thuoc thuc su cua map
	for (int i = 0; i < MAP_MAP_Y; i++) {
		for (int j = 0; j < MAP_MAP_X; j++) {
			fscanf_s(fp, "%d", &game_map_.tile[i][j]); // Doc map
			int val = game_map_.tile[i][j];
			//Ranh gioi cua map
			if (val > 0) {
				if (j > game_map_.max_x_) {
					game_map_.max_x_ = j;
				}
				if (i > game_map_.max_y_) {
					game_map_.max_y_ = i;
				}
			}
		}
	}
	//Cap nhat theo don vi pixels
	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;
	//Diem xuat phat cua ban do
	game_map_.start_x_ = 0;
	game_map_.start_y_ = 0;
	//Luu ten tep
	game_map_.file_name = name;
	fclose(fp);
}
void GameMap::LoadTiles(SDL_Renderer* gRenderer) {
	char file_img[30];
	FILE* fp = NULL;
	//Ve cac khoi mat dat
	for (int i = 0; i < MAX_TILE; i++) {
		sprintf_s(file_img, "map/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) {
			continue;
		}
		fclose(fp);
		tile_mat[i].LoadImg(file_img, gRenderer);
	}
}
void GameMap::DrawMap(SDL_Renderer* gRenderer) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_x_ / TILE_SIZE;
	//Ve cai mấy cái tile map (khối dưới chân)
	x1 = (game_map_.start_x_ % TILE_SIZE) * -1;
	//Neu khong cong cai tilesize thi se bi load thieu goc phai
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = game_map_.start_y_ / TILE_SIZE;
	y1 = (game_map_.start_y_ % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	//Ve theo toa do
	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = game_map_.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map_.tile[map_y][map_x];
			if (val > 0) {
				tile_mat[val].SetRect(j, i);
				tile_mat[val].Render(gRenderer);
			}
			map_x++;
		}
		map_y++;
	}
}