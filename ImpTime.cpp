#include"ImpTime.h"
#include"Common_Function.h"
ImpTime::ImpTime() {
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}
ImpTime::~ImpTime() {
	;
}
void ImpTime::start() {
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}
void ImpTime::stop() {
	is_paused_ = false;
	is_started_ = false;
	start_tick_ = SDL_GetTicks();
}

void ImpTime::paused() {
	if (is_started_ == true && is_paused_ == false) {
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks() - start_tick_;
	}
}
void ImpTime::unpaused() {
	if (is_paused_ == true) {
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - paused_tick_;
		paused_tick_ = 0;
	}
}

int ImpTime::get_ticks() {
	if (is_started_ == true) {
		if (is_paused_ == true) {
			return paused_tick_;
		}
		else {
			return SDL_GetTicks() - start_tick_;
		}
	}
	return 0;
}

bool ImpTime::is_started() {
	return is_started_;
}
bool ImpTime::is_paused() {
	return is_paused_;
}