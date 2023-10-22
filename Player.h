#ifndef PLAYER_H_
#define PLAYER_H_
#include"Common_Function.h"
#include"BaseObject.h"
#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP 20
class Player :public BaseObject {
public:
	Player();
	~Player();
	enum WalkType {
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
	};
	bool LoadImg(std::string path, SDL_Renderer* gRenderer);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event e, SDL_Renderer* gRenderer);
	void set_clips();
	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x, map_y_ = map_y; }
	void CenterEntityOnMap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);
private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;
	bool on_ground;

	int map_x_;
	int map_y_;
	int come_back_time_;
};


#endif