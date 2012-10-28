#include "openglcanvas.h"


BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
	EVT_PAINT(OpenGLCanvas::OnPaint)
	EVT_SIZE(OpenGLCanvas::OnSize)
	EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)
	EVT_LEFT_DOWN(OpenGLCanvas::OnLeftDown)
	EVT_LEFT_UP(OpenGLCanvas::OnLeftUp)
	EVT_MOTION(OpenGLCanvas::OnMouseMove)
END_EVENT_TABLE()

OpenGLCanvas::OpenGLCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name): 
wxGLCanvas(parent, id, pos, size, style, name)
{
	main_frame = (CMainFrame *) parent;
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
	Triangle *t;
	GetClientSize(&w, &h);
	glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClearColor( 1.f, 1.f, 1.f, 1 );
	glClear( GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_TRIANGLES);
		for(int i(0); i < main_frame->getNombreTriangles() ; i++)
		{
			t = main_frame->getTri(i);
			glColor3d(t->colour.Red(),t->colour.Green(),t->colour.Blue());
			glVertex2i(t->getPX(0),t->getPY(0)); 
			glVertex2i(t->getPX(1),t->getPY(1)); 
			glVertex2i(t->getPX(2),t->getPY(2)); 

			glLineWidth((float) t->thickness);
			glVertex2i(t->getPX(0),t->getPY(0)); 
			glVertex2i(t->getPX(1),t->getPY(1)); 
			glVertex2i(t->getPX(2),t->getPY(2)); 
		}
		// TODO : afficher le triangle en cours de construction
	glEnd();
}

void OpenGLCanvas::OnMouseMove(wxMouseEvent& e)
{
	//std::cout << "mouse : " << e.GetX() << " :: " << e.GetY() << std::endl;
	if(main_frame->isDrawing())
	{
		main_frame->setPointCourant(e.GetX(), e.GetY());
		Draw();
	}
}

void OpenGLCanvas::OnLeftDown(wxMouseEvent& e)
{
}

void OpenGLCanvas::OnLeftUp(wxMouseEvent& e)
{
	if(! main_frame->isDrawing())
	{
		main_frame->setDrawing(true);
	}
	else
	{
	}
	main_frame->ajoute_point_triangle_courant(e.GetX(),e.GetY());
}
