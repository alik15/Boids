#pragma once
#include"SDL.h"
#include "Turtle.h"
#include <iostream>
class Loop {
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	static const int HEIGHT = 800;
	static const int WIDTH = 600;
	float f_centerx;
	float f_centery;
	SDL_Texture* texture;

	

	friend class Turtle;


public:
	Loop();
	~Loop();
	Uint32 pixels[WIDTH * HEIGHT];
	void init(const char* title, int xpos, int ypos, bool fullscreen);
	void update(Turtle *t, int  n);
	void render(Turtle *t, int n);
	void clean();
	void handleEvents();
	void save();
	bool running();

};

