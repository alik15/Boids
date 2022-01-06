#include "Loop.h"
#include <chrono>
#include <iostream>
using namespace std;
Loop::Loop() {

}

Loop::~Loop() {

}

void Loop::init(const char* title, int xpos, int ypos, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems Initialized" << endl;

		window = SDL_CreateWindow(title, xpos, ypos, HEIGHT + 100, WIDTH + 200, flags);

		if (window) {
			cout << "Window Created!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			cout << "Renderer Created!" << endl;
		}
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
		if (texture) {
			cout << "Texturer Created!" << endl;
			memset(pixels, 255, 640 * 480 * sizeof(Uint32));
		}

		isRunning = true;
	}
	else {

		cerr << "Failed to initialize subsystems, SDL_GetError() - " << SDL_GetError() << "\n";

		isRunning = false;

	}

}

void Loop::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
	default:
		break;
	}
}

void Loop::render(Turtle* t, int n) {

	for (int j = 0; j < n; j++) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);
		SDL_RenderDrawPoint(renderer, (t + j)->x, (t + j)->y);
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	}
}

void Loop::update(Turtle* t, int n) {
	for (int j = 0; j < n; j++) {
		(t+j)->update_pos(t,n);
		
		//pixels[(((t + j)->getx()) * WIDTH) + ((t + j)->gety())] = 0xFFFFFFFF;
		
	}



}


void Loop::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_Quit();
	cout << "Loopation Cleaned!" << endl;
}

void Loop::save() {

	std::time_t ct = std::time(0);
	#pragma warning(disable : 4996)
	char* cc = ctime(&ct);

	string filepath = cc;
	filepath += ".bmp";
	SDL_Surface* infoSurface = NULL;
	infoSurface = SDL_GetWindowSurface(window);
	if (infoSurface == NULL) {
		std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
	}
	else {
		unsigned char* pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
		if (pixels == nullptr) {
			std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
			return;
		}
		else {
			if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
				delete[] pixels;
				return;
			}
			else {
				SDL_Surface* saveSurface = nullptr;
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
				if (saveSurface == NULL) {
					std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
					delete[] pixels;
					return;
				}
				SDL_SaveBMP(saveSurface, filepath.c_str());
				SDL_FreeSurface(saveSurface);
				saveSurface = NULL;
				cout << "Image Saved!\n";
			}
			delete[] pixels;
		}
		SDL_FreeSurface(infoSurface);
		infoSurface = NULL;
	}

}


bool Loop::running() {

	return isRunning;
}
