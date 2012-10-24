#ifndef __OPENGLCANVAS_H__
#define __OPENGLCANVAS_H__

#include <wx/glcanvas.h>

class OpenGLCanvas: public wxGLCanvas {
	public :
		OpenGLCanvas::OpenGLCanvas(wxWindow *parent, wxWindowID id,
			const wxPoint& pos, const wxSize& size, long style, const wxString& name);
		OpenGLCanvas::~OpenGLCanvas(void);

	private :
		void OnPaint( wxPaintEvent& event );
		void OnSize( wxSizeEvent& event );
		void OnEraseBackground( wxEraseEvent& event );
		DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(OpenGLCanvas, wxDialog)
	EVT_PAINT(OpenGLCanvas::OnPaint)
	EVT_SIZE(OpenGLCanvas::OnSize)
	EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)
END_EVENT_TABLE ()

OpenGLCanvas::OpenGLCanvas(wxWindow *parent, wxWindowID id,
const wxPoint& pos, const wxSize& size, long style, const wxString& name): 
wxGLCanvas(parent, id, pos, size, style, name)
{
}
OpenGLCanvas::~OpenGLCanvas(void)
{
}
void OnPaint( wxPaintEvent& event )
{
}
void OnSize( wxSizeEvent& event )
{
}
void OnEraseBackground( wxEraseEvent& event )
{
}

#endif

