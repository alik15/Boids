#include "Turtle.h"

Turtle::Turtle()
{
	srand(time(0));
	x = (rand() % Loop::WIDTH) + Loop::WIDTH;
	y = (rand() % Loop::HEIGHT) + Loop::HEIGHT;
	velocity_x = 5;
	velocity_y = -5;
	color = 0xFFFFFF;

}
Turtle::~Turtle()
{
}

void Turtle::update_pos(Turtle* t, int nmbrofboids)
{
	avoidance(t, nmbrofboids);
	flock_center(t, nmbrofboids);
	//v_match(t, nmbrofboids);
	velocity_x += v1[0] + v2[0] + v3[0];
	velocity_y += v1[1] + v2[1] + v3[1];
	x += velocity_x;
	y += velocity_y;

}

//THIS IS NOT BASED ON THE BOIDS NEARBY, ITS BASED ON ALL THE BOIDS, WORKS BY CONSIDERING THE CENTER OF MASS OF THE WHOLE FLOCK

void Turtle::flock_center(Turtle* t, int nmbrofboids)
{

	int a, b;
	int sum = 0;
	int check = 0;

	for (int j=0; j < nmbrofboids; j++) {   // here for the nmbr of boids give the total number of boids we have

			//for the x component
		sum += (t+j)->x;
		check++;

		a = sum / check;

		//for the y component
		sum += (t + j)->y;
		check++;

		b = sum / (check - 1);


		v1[0] = a - x;
		v1[1] = b - y;


	}

};

void Turtle::avoidance(Turtle * t, int nmbrofboids)
{
	v2[0] = 0;
	v2[1] = 0;


	for (int j=0; j < nmbrofboids; j++) {
		if ((std::abs((x - (t + j)->x)) < 100) && (std::abs((x - (t + j)->x)) < 100)) {

			v2[0] = v2[0] - ((t + j)->x - x);
			v2[1] = v2[1] - ((t + j)->y - y);


		}

	}
}
/*
void Turtle::v_match(Turtle *t, int nmbrofboids)
{
	//for boids around calc the avg velocity and add to current v
	int avg_velocityx=0;
	int avg_velocityy=0;
	for (int j=0; j < nmbrofboids; j++) {
		avg_velocityx = avg_velocityx + (t + j)->velocity_x;
		avg_velocityy = avg_velocityy + (t + j)->velocity_y;

	}
	avg_velocityx = avg_velocityx / (nmbrofboids);
	avg_velocityy = avg_velocityx / (nmbrofboids);

	v3[0] = avg_velocityx/8;
	v3[1] = avg_velocityy/8;
}
*/

