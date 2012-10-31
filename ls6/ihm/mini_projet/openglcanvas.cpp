#include "openglcanvas.h"


BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
	EVT_PAINT(OpenGLCanvas::OnPaint)
	EVT_SIZE(OpenGLCanvas::OnSize)
	EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)
	EVT_LEFT_DOWN(OpenGLCanvas::OnLeftDown)
	EVT_RIGHT_DOWN(OpenGLCanvas::OnRightDown)
	EVT_LEFT_UP(OpenGLCanvas::OnLeftUp)
	EVT_MOTION(OpenGLCanvas::OnMouseMove)
	EVT_MENU(POPUP_PROPRIETES, OpenGLCanvas::OnContextPptes)
	EVT_MENU(POPUP_SUPPRIMER, OpenGLCanvas::OnContextSuppr)
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
	for(int i(0); i < main_frame->getNombreTriangles() ; i++)
	{
		t = main_frame->getTri(i + k);
		while(! t->existe())
			t = main_frame->getTri(i + (++k));

		glBegin(GL_TRIANGLES);
			glColor3d(t->colour.Red(),t->colour.Green(),t->colour.Blue());
			glVertex2i(t->getPX(0),t->getPY(0)); 
			glVertex2i(t->getPX(1),t->getPY(1)); 
			glVertex2i(t->getPX(2),t->getPY(2)); 
		glEnd();

		glColor3d(0,0,0);
		glLineWidth((float) t->thickness);
		glBegin(GL_LINE_LOOP);
			glVertex2i(t->getPX(0),t->getPY(0)); 
			glVertex2i(t->getPX(1),t->getPY(1)); 
			glVertex2i(t->getPX(2),t->getPY(2)); 
		glEnd();
	}
	wxColour * couleur_cour;
	switch(main_frame->getNbPointsDefinis())
	{
		case 1 : 
			/* 
			 std::cout << "case 1 :: px0 : " << main_frame->getTriangleCourant()->getPX(0) << " :: 
			 py0 : " << main_frame->getTriangleCourant()->getPY(0) << " :: pcourant x : " 
			 << main_frame->getPointCourant().x << " :: pcourant y : " << 
			 main_frame->getPointCourant().y << std::endl; 
			*/
			glBegin(GL_LINES);
				couleur_cour = main_frame->getCouleurCourante();
				glColor3f(couleur_cour->Red(),couleur_cour->Green(), couleur_cour->Blue());
				glLineWidth(main_frame->getEpaisseurTraitCourante());
				glVertex2i(main_frame->getTriangleCourant()->getPX(0), main_frame->getTriangleCourant()->getPY(0));
				glVertex2i(main_frame->getPointCourant().x, main_frame->getPointCourant().y);
			glEnd();
			break;
		case 2 :
			couleur_cour = main_frame->getCouleurCourante();
			glBegin(GL_TRIANGLES);
				glColor3f(couleur_cour->Red(),couleur_cour->Green(), couleur_cour->Blue());
				//glLineWidth(main_frame->getEpaisseurTraitCourante());
				glVertex2i(main_frame->getTriangleCourant()->getPX(0), main_frame->getTriangleCourant()->getPY(0));
				glVertex2i(main_frame->getTriangleCourant()->getPX(1), main_frame->getTriangleCourant()->getPY(1));
				glVertex2i(main_frame->getPointCourant().x, main_frame->getPointCourant().y);
			glEnd();
			glColor3d(0,0,0);
			glLineWidth((float) main_frame->getEpaisseurTraitCourante());
			glBegin(GL_LINE_LOOP);
				glVertex2i(main_frame->getTriangleCourant()->getPX(0), main_frame->getTriangleCourant()->getPY(0));
				glVertex2i(main_frame->getTriangleCourant()->getPX(1), main_frame->getTriangleCourant()->getPY(1));
				glVertex2i(main_frame->getPointCourant().x, main_frame->getPointCourant().y);
			glEnd();
			break;
		default :
			//std::cout << "case 3" << std::endl;
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
		//std::cout << "e.GetX : " << e.GetX() << " e.GetY : " << e.GetY() << std::endl;
		main_frame->setDrawing(true);
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

void OpenGLCanvas::OnRightDown(wxMouseEvent& e)
{
	int h,w;
	int x, y;
	wxMenu popupmenu;

	GetClientSize(&w,&h);
	x = e.GetX() - w/2;
	y = h/2 - e.GetY();
	selected_tri = est_dans_triangle(x, y);
	if(selected_tri != -1)
	{
		popupmenu.Append(POPUP_PROPRIETES, wxT("Propriétés"));
		popupmenu.Append(POPUP_SUPPRIMER, wxT("Supprimer"));
	}
	else
	{
		wxMenu * fichier = new wxMenu;
		wxMenu * gestion = new wxMenu;
		wxMenu * valeurs_courantes = new wxMenu;
		fichier->Append(M_OUVRIR, wxT("Ouvrir fichier"));
		fichier->Append(M_SAUVEGARDER, wxT("Sauvegarder"));
		gestion->Append(M_GESTION_TRIANGLES, wxT("Gestion des triangles"));
		valeurs_courantes->Append(M_COULEUR, wxT("Couleur courante"));
		valeurs_courantes->Append(M_EPAISSEUR_TRAIT, wxT("Epaisseur trait"));
		popupmenu.Append(POPUP_FICHIER, wxT("Fichier") ,fichier);
		popupmenu.Append(POPUP_GESTION, wxT("Gestion") ,gestion);
		popupmenu.Append(POPUP_VAL_COURANTES, wxT("Valeurs courantes") ,valeurs_courantes);
	}
	PopupMenu( &popupmenu, e.GetX(), e.GetY() );
}

int OpenGLCanvas::est_dans_triangle(int x, int y)
{
	//std::cout << "x : " << x << " y : " << y << std::endl;
	int k(0);
	Triangle *t;
	for(int i(0); i < main_frame->getNombreTriangles() ; i++)
	{
		t = main_frame->getTri(i + k);
		while(! t->existe())
			t = main_frame->getTri(i + (++k));
		if(t->IsPointInTriangle(x,y))
			return i + k ;
	}
	return -1;
}

void OpenGLCanvas::OnContextPptes(wxCommandEvent& e)
{
	Triangle *t = main_frame->getTri(selected_tri);
	ProprietesDialog vdlg( this, -1, wxT("Proprietes"), t);
	vdlg.ShowModal();
}

void OpenGLCanvas::OnContextSuppr(wxCommandEvent& e)
{
	main_frame->supprimerTriangle(selected_tri);
}
