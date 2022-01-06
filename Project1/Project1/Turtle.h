#pragma once


#include <SDL.h>
#include <iostream>
#include "Loop.h"
#include <time.h>
#include <vector>
#include <cmath>

class Turtle {

	friend class Loop;
protected:
	int x, y;
	int v1[2] = { 0 }, v2[2] = { 0 }, v3[2] = { 0 };
	float v;
	float velocity_x, velocity_y;
	Uint8 color;


public:
	Turtle();
	~Turtle();
	int getx() { return x; }
	int gety() { return y; }
	
	void update_pos(Turtle *t, int nmbrofboids);
	void flock_center(Turtle* t, int nmbrofboids);
	void avoidance(Turtle* t, int nmbrofboids);
	void v_match(Turtle* t, int nmbrofboids);
	
	
};

