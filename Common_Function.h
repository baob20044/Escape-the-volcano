#pragma once

#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include"BaseObject.h"
using namespace std;
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 640;
const int FRAME_PER_SECOND = 40; //fps
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;
static bool quit = false;

#define TILE_SIZE 64
#define MAP_MAP_X 400
#define MAP_MAP_Y 10
#define BLANK_TILE 0

typedef struct Input {
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};
typedef struct Map {
	int start_x_;
	int start_y_;
	int max_x_;
	int max_y_;
	int tile[MAP_MAP_Y][MAP_MAP_X];
	char* file_name;
};

bool init();
bool loadMedia();
void Handle_event();
void Update_Entity();
void close();

#endif