#include"BaseObject.h"
BaseObject::BaseObject() {
	p_object_= NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}
BaseObject::~BaseObject() {
	Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen) {
	Free();
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load duong dan
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Xu li hinh anh, xoa di cai background thua
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

		//Tao be mat phu hop voi pixel
		newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Kich thuoc cua vat the tren man hinh
			rect_.w = loadedSurface->w;
			rect_.h = loadedSurface->h;
		}

		//Giai phong
		SDL_FreeSurface(loadedSurface);
	}
		p_object_ = newTexture;
		return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip ) {
	SDL_Rect renderQuad = {rect_.x,rect_.y,rect_.w, rect_.h };
	SDL_RenderCopy(des, p_object_, clip, &renderQuad);
}
void BaseObject::Free() {
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}