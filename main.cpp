#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include"Common_Function.h"
#include"BaseObject.h"
#include"map.h"
#include"Player.h"
#include"ImpTime.h"

int main(int argc, char* args[])
{
	init();
	loadMedia();
	while (!quit)
		{
		Handle_event();
		Update_Entity();
		}
	close();
	return 0;
}