#pragma once
#ifndef GAME_MAP_H_
#define GAME_MAP_H_
#include"Common_Function.h"
#include "BaseObject.h"

#define MAX_TILE 20
class TileMat :public BaseObject {
public:
	TileMat() { ; }
	~TileMat() { ; }
};
class GameMap {
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(char* name);
	void LoadTiles(SDL_Renderer* gRenderer);
	void DrawMap(SDL_Renderer* gRenderer);
	Map getMap() const { return game_map_; }
	void SetMap(Map map_data) { game_map_ = map_data; }
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILE];
};

#endif