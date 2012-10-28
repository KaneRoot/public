#ifndef __OPENGLCANVAS_H__
#define __OPENGLCANVAS_H__

class CMainFrame;

#include <wx/wx.h> 
#include <wx/dialog.h>
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include "mainframe.h"

class OpenGLCanvas: public wxGLCanvas {
	public :
		OpenGLCanvas(wxWindow *parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style, const wxString& name);
		~OpenGLCanvas(void);
		CMainFrame * main_frame;

	private :
		void Draw();
		void OnPaint( wxPaintEvent& event );
		void OnSize( wxSizeEvent& event );
		void OnEraseBackground( wxEraseEvent& event );
		void OnMouseMove(wxMouseEvent& e);
		void OnLeftDown(wxMouseEvent& e);
		void OnLeftUp(wxMouseEvent& e);
		DECLARE_EVENT_TABLE()
};

#endif

