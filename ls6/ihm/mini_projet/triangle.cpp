#include "triangle.h"

void Triangle::setP(int n, float x, float y)
{
	p[n].x = x;
	p[n].y = y;
}

float Triangle::getPX(int n) { return p[n].x; }
float Triangle::getPY(int n) { return p[n].y; } 

void Triangle::supprimer()
{
	existe_var = false;
}
void Triangle::creer()
{
	existe_var = true;
}
bool Triangle::existe() 
{
	return existe_var;
}

bool Triangle::IsPointInTriangle(int x, int y)
{
	int fAB = (y-getPY(0))*(getPX(1)-getPX(0)) - (x-getPX(0))*(getPY(1)-getPY(0));
	int fCA = (y-getPY(2))*(getPX(0)-getPX(2)) - (x-getPX(2))*(getPY(0)-getPY(2));
	int fBC = (y-getPY(1))*(getPX(2)-getPX(1)) - (x-getPX(1))*(getPY(2)-getPY(1));
	if ((fAB*fBC)>0 && (fBC*fCA)>0)
		return true;
	else
		return false;
}
