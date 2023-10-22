#include"Common_Function.h"
#include"map.h"
#include"Player.h"
#include"ImpTime.h"
//Init các thành phần
BaseObject g_background;
GameMap game_map;
Player p_player;
ImpTime fps_timer;
//Ham tao cua so
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Shooting Star", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		SDL_Surface* icon = IMG_Load("Img/squid.png");
		SDL_SetWindowIcon(gWindow, icon);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}
//Ham load cac Image
bool loadMedia()
{
	bool success = true;
	//Load background
	bool ret = g_background.LoadImg("Img/game.jpg", gRenderer);
	if (ret == false) return false;
	//Load map
	char dat[] = "Map/map01.dat";
	game_map.LoadMap(dat);
	game_map.LoadTiles(gRenderer);
	//Load player
	p_player.LoadImg("Img/player_right.png", gRenderer);
	p_player.set_clips();
	return success;
}
//Ham xu ly nut an
void Handle_event() {
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
			exit(0);
		}
		p_player.HandleInputAction(e, gRenderer);
	}
}
//Ham cap nhat cac thong so cua cac thuc the
void Update_Entity() {
	fps_timer.start();
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	//Map data
	g_background.Render(gRenderer, NULL);
	Map map_data = game_map.getMap();
	//Player
	p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
	p_player.DoPlayer(map_data);
	p_player.Show(gRenderer);
	//Map
	game_map.SetMap(map_data);
	game_map.DrawMap(gRenderer);
	//Finally
	SDL_RenderPresent(gRenderer);
	//Lam cham lai thoi gian (toc do load game fps)
	int real_imp_time = fps_timer.get_ticks();
	int time_one_frame = 1000 / FRAME_PER_SECOND;//ms
	if (real_imp_time < time_one_frame) {
		int delay_time = time_one_frame - real_imp_time;
		if (delay_time > 0) SDL_Delay(delay_time);
	}
}
//Ham giai phong SDL
void close()
{
	g_background.Free();
	gRenderer = NULL;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
}