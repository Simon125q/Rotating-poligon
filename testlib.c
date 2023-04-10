/*This program creates an animated poligon which rotate, grow an shrink continuously*/

#include "primlib.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define POLYGON_COLOR YELLOW
#define NUMBER_OF_DIAGONALS 5
#define MAXIMUM_RADIUS 300
#define MINIMUM_RADIUS 20
#define RADIUS_CHANGE 1
// Angle between diagonals
#define ANGLE_ALFA (2 * M_PI / NUMBER_OF_DIAGONALS)
// Initial angle of the poligon
#define ANGLE_BETA 0
#define ROTATION_ANGLE (M_PI / 360.0)
#define DELAY 10

double r_growth = RADIUS_CHANGE;

void DrawPoligon(double radius, double angle_beta);
double CalculateNewAngle(double angle);
double CalculateNewRadius(double radius);

int main(int argc, char* argv[])
{
	
	if (gfx_init()) {
		exit(3);
	}

	#define X_CENTER (gfx_screenWidth() / 2)
	#define Y_CENTER (gfx_screenHeight() / 2)
	
	int play = TRUE;
	double new_beta = ANGLE_BETA;
	double new_r = MAXIMUM_RADIUS;

	while (play) {

		gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);

		new_beta = CalculateNewAngle(new_beta);

		new_r = CalculateNewRadius(new_r);

		DrawPoligon(new_r, new_beta);
		
		gfx_updateScreen();

		SDL_Delay(DELAY);

		if (gfx_isKeyDown(SDLK_ESCAPE))
		{
			play= FALSE;
		}
	}

	gfx_getkey();

	return 0;
}

void DrawPoligon(double radius, double angle_beta)
{
	/*This function draws the polygon with the given radius and angle_beta. It uses the cos() and sin()
	functions from math.h to calculate the coordinates of the polygon vertices. The function loops through
	the number diagonals and calculates the coordinates of their endpoints.*/
	double coord_x1;
	double coord_y1;
	double coord_x2;
	double coord_y2;

	for(int vertice = NUMBER_OF_DIAGONALS; vertice > 0; vertice--)
		{
			coord_x1 = X_CENTER + radius * cos(angle_beta + vertice * ANGLE_ALFA);
			coord_y1 = Y_CENTER + radius * sin(angle_beta + vertice * ANGLE_ALFA);
			coord_x2 = X_CENTER + radius * cos(angle_beta + (vertice-1) * ANGLE_ALFA);
			coord_y2 = Y_CENTER + radius * sin(angle_beta + (vertice-1) * ANGLE_ALFA);
			gfx_line(coord_x1, coord_y1, coord_x2, coord_y2, POLYGON_COLOR);
		}
}

double CalculateNewAngle(double angle)\
{
	/*This function calculates the new angle of the polygon after rotation. It adds the ROTATION_ANGLE
	 to the current angle and checks if the result is greater than 2PI. If it is,
	 the function subtracts 2PI from the result to keep the angle within the range of [0, 2PI).*/

	angle += ROTATION_ANGLE;

	if(angle > 2 * M_PI)
	{
		angle -= 2 * M_PI;
	}
	return angle;
}

double CalculateNewRadius(double radius)
{
	/*This function calculates the new radius of the polygon after growth or shrinkage.
	It checks if the current radius is less than or equal to MINIMUM_RADIUS or greater than or equal to MAXIMUM_RADIUS.
	If it is, the function changes the sign of r_growth to reverse the direction of the radius change.
	It then adds r_growth to the current radius to obtain the new radius.*/

	if(radius <= MINIMUM_RADIUS || radius >= MAXIMUM_RADIUS)
		{
			r_growth = -r_growth;
		}

	radius += r_growth;
	
	return radius;
}