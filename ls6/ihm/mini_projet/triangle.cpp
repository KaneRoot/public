#include "triangle.h"

void Triangle::setP(int n, float x, float y)
{
	p[n].x = x;
	p[n].y = y;
}

float Triangle::getPX(int n) { return p[n].x; }
float Triangle::getPY(int n) { return p[n].y; } 
