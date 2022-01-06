#include "Loop.h"
#include "Turtle.h"

Loop* anim = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Turtle t[1000];
	anim = new Loop();

	anim->init("Loop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

	while (anim->running()) {
		frameStart = SDL_GetTicks();

		anim->handleEvents();
		anim->update(t, 1000);
		anim->render(t, 1000);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	anim->save();
	anim->clean();

	return 0;
}
