#ifndef __OPENGLCANVAS_H__
#define __OPENGLCANVAS_H__

#include <wx/glcanvas.h>

class OpenGLCanvas: public wxGLCanvas {
	public :
		OpenGLCanvas(wxWindow *parent, wxWindowID id,
			const wxPoint& pos, const wxSize& size, long style, const wxString& name);
		~OpenGLCanvas(void);

	private :
		void Draw();
		void OnPaint( wxPaintEvent& event );
		void OnSize( wxSizeEvent& event );
		void OnEraseBackground( wxEraseEvent& event );
		DECLARE_EVENT_TABLE()
};

#endif

