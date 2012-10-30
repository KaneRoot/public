#ifndef __OPENGLCANVAS_H__
#define __OPENGLCANVAS_H__

class CMainFrame;

#include <wx/wx.h> 
#include <wx/dialog.h>
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include "mainframe.h"

enum { POPUP_FICHIER = 1000, POPUP_GESTION, POPUP_VAL_COURANTES,
	POPUP_PROPRIETES, POPUP_SUPPRIMER};

class OpenGLCanvas: public wxGLCanvas {
	public :
		OpenGLCanvas(wxWindow *parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style, const wxString& name);
		~OpenGLCanvas(void);
		CMainFrame * main_frame;

	private :
		int selected_tri;
		void Draw();
		void OnPaint( wxPaintEvent& event );
		void OnSize( wxSizeEvent& event );
		void OnEraseBackground( wxEraseEvent& event );
		void OnMouseMove(wxMouseEvent& e);
		void OnLeftDown(wxMouseEvent& e);
		void OnRightDown(wxMouseEvent& e);
		void OnLeftUp(wxMouseEvent& e);
		int est_dans_triangle(int x, int y);
		void OnContextPptes(wxCommandEvent& e);
		void OnContextSuppr(wxCommandEvent& e);
		DECLARE_EVENT_TABLE()
};

#endif

