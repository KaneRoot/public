#ifndef __OPENGLCANVAS_H__
#define __OPENGLCANVAS_H__

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
		wxFrame * main_frame;

	private :
		void Draw();
		void OnPaint( wxPaintEvent& event );
		void OnSize( wxSizeEvent& event );
		void OnEraseBackground( wxEraseEvent& event );
		DECLARE_EVENT_TABLE()
};

#endif

