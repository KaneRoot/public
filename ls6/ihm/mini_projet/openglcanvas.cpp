
#include <wx/dialog.h>
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include "openglcanvas.h"


BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
	EVT_PAINT(OpenGLCanvas::OnPaint)
	EVT_SIZE(OpenGLCanvas::OnSize)
	EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)
END_EVENT_TABLE ()

OpenGLCanvas::OpenGLCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name): 
wxGLCanvas(parent, id, pos, size, style, name)
{
}

OpenGLCanvas::~OpenGLCanvas(void)
{
}

void OpenGLCanvas::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(this);
	SetCurrent();
	Draw();					// fonction de dessins
	SwapBuffers();
}

void OpenGLCanvas::OnSize( wxSizeEvent& event )
{
	wxGLCanvas::OnSize(event);
	int w, h;
	GetClientSize(&w, &h);
	glViewport(0, 0, (GLint) w, (GLint) h);
}

void OpenGLCanvas::OnEraseBackground( wxEraseEvent& event )
{
}

void OpenGLCanvas::Draw()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	int w, h;
	GetClientSize(&w, &h);
	glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClearColor( 1.f, 1.f, 1.f, 1 );
	glClear( GL_COLOR_BUFFER_BIT);
	/*
	glBegin(GL_LINES);
		glVertex2i(0,0);glVertex2i(0,20);
		glVertex2i(0,0);glVertex2i(20,0);
	glEnd(); 
	*/
	glBegin(GL_TRIANGLES);
		glColor3d(0,0,0);
		glVertex2i(0,0); glVertex2i(10,10); glVertex2i(0,10);
	glEnd();
}
