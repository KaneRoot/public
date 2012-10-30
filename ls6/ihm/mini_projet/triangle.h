#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <wx/colour.h>
#include <wx/wx.h>
#include "definitions.h"

// Define a new triangle class
class Triangle
{
	public:
		point p[3];

		wxColour colour;
		wxString nom;

		int thickness; // epaisseur de trait 
		void setP(int n, float x, float y);
		float getPX(int n);
		float getPY(int n);
		bool IsPointInTriangle(int x, int y);
		bool existe();
		void supprimer();
		void creer();

	private:
		bool existe_var;
};

#endif // #ifndef __TRIANGLE_H__


