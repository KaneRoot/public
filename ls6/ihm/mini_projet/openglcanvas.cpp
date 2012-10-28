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

	int w, h, k(0);
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
			t = main_frame->getTri(i + k);
			while(t->existe != 1)
				t = main_frame->getTri(i + ++k);

			glColor3d(t->colour.Red(),t->colour.Green(),t->colour.Blue());
			glVertex2i(t->getPX(0),t->getPY(0)); 
			glVertex2i(t->getPX(1),t->getPY(1)); 
			glVertex2i(t->getPX(2),t->getPY(2)); 

			glLineWidth((float) t->thickness);
			glVertex2i(t->getPX(0),t->getPY(0)); 
			glVertex2i(t->getPX(1),t->getPY(1)); 
			glVertex2i(t->getPX(2),t->getPY(2)); 
		}
	glEnd();
	// TODO : afficher le triangle en cours de construction
	switch(main_frame->getNbPointsDefinis())
	{
		case 1 : 
			std::cout << "case 1 :: px0 : " << main_frame->getTriangleCourant()->getPX(0) << " :: py0 : " << main_frame->getTriangleCourant()->getPY(0) << " :: pcourant x : " << main_frame->getPointCourant().x << " :: pcourant y : " << main_frame->getPointCourant().y << std::endl;
			glBegin(GL_LINES);
				glColor3d(1,0,0);
				glVertex2i(main_frame->getTriangleCourant()->getPX(0), main_frame->getTriangleCourant()->getPY(0));
				glVertex2i(main_frame->getPointCourant().x, main_frame->getPointCourant().y);
			glEnd();
			break;
		case 2 :
			std::cout << "case 2" << std::endl;
			glBegin(GL_TRIANGLES);
			glEnd();
			break;
		default :
			std::cout << "case 3" << std::endl;
			break;
	}
}

void OpenGLCanvas::OnMouseMove(wxMouseEvent& e)
{
	//std::cout << "mouse : " << e.GetX() << " :: " << e.GetY() << std::endl;
	int h,w;
	GetClientSize(&w,&h);
	glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);
	glViewport(0,0,(GLint)w,(GLint)h);
	int x, y;
	x = e.GetX() - w/2;
	y = h/2 - e.GetY();
	main_frame->setPointCourant(x, y);
	if(main_frame->isDrawing())
	{
		//std::cout << "px0 : " << main_frame->getTriangleCourant()->getPX(0) << " :: py0 : " << main_frame->getTriangleCourant()->getPY(0) << " :: pcourant x : " << main_frame->getPointCourant().x << " :: pcourant y : " << main_frame->getPointCourant().y << std::endl;
		Draw();					// fonction de dessins
		SwapBuffers();
	}
}

void OpenGLCanvas::OnLeftDown(wxMouseEvent& e)
{
}

void OpenGLCanvas::OnLeftUp(wxMouseEvent& e)
{
	if(! main_frame->isDrawing())
	{
		std::cout << "e.GetX : " << e.GetX() << " e.GetY : " << e.GetY() << std::endl;
		main_frame->setDrawing(true);
	}
	else
	{
	}
	int h,w;
	GetClientSize(&w,&h);
	glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);
	glViewport(0,0,(GLint)w,(GLint)h);
	int x, y;
	x = e.GetX() - w/2;
	y = h/2 - e.GetY();
	main_frame->ajoute_point_triangle_courant(x,y);
}
