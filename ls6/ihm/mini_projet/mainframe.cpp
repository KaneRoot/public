#include "mainframe.h"


BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
	EVT_MENU(M_NOUVEAU_FICHIER, CMainFrame::OnNew)
	EVT_MENU(M_QUITTER, CMainFrame::OnQuit)
	EVT_MENU(M_OUVRIR, CMainFrame::OnOpen)
	EVT_MENU(M_SAUVEGARDER, CMainFrame::OnSave)
	EVT_MENU(M_EPAISSEUR_TRAIT, CMainFrame::OnEpaisseurTrait)
	EVT_MENU(M_COULEUR, CMainFrame::OnColor)
	EVT_MENU(M_GESTION_TRIANGLES, CMainFrame::OnGestionTriangles)
	EVT_MENU(M_TOOLBAR, CMainFrame::OnToolBar)
	EVT_MENU(M_VERSION, CMainFrame::OnVersion)
END_EVENT_TABLE()

CMainFrame::CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size), num_tri(0)
{
	canvas_opengl = new OpenGLCanvas(this,CANVAS_OPENGL, wxDefaultPosition, wxDefaultSize, 
			0, wxT("MonGLCanvas"));
	setCouleurCourante(0,255,0);
} //constructor

void CMainFrame::CreateMyToolBar()
{
	m_toolbar = CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL | wxTB_TEXT, TOOLBAR_TOOLS);
	wxBitmap toolBarBitmaps[4];

	toolBarBitmaps[0] = wxBitmap(wxT("img/new.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[1] = wxBitmap(wxT("img/open.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[2] = wxBitmap(wxT("img/save.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[3] = wxBitmap(wxT("img/draw.bmp"),wxBITMAP_TYPE_BMP);

	m_toolbar->SetToolBitmapSize(wxSize(toolBarBitmaps[0].GetWidth(), toolBarBitmaps[0].GetHeight()));
	m_toolbar->AddTool(M_NOUVEAU_FICHIER, wxT("Nouveau"), toolBarBitmaps[0]);
	m_toolbar->AddTool(M_OUVRIR, wxT("Ouvrir"), toolBarBitmaps[1]);
	m_toolbar->AddTool(M_SAUVEGARDER, wxT("Sauvegarder"), toolBarBitmaps[2]);
	m_toolbar->AddSeparator();
	m_toolbar->AddTool(M_GESTION_TRIANGLES, wxT("Gestion des triangles"), toolBarBitmaps[3], wxT("Gestion des triangles"));
	m_toolbar->EnableTool(M_GESTION_TRIANGLES, false);

	m_toolbar->Realize();
	SetToolBar(m_toolbar);
}

void CMainFrame::OnNew(wxCommandEvent& event)
{
	supprimerTousTriangles();
	activerGestionTriangles(false);
}

void CMainFrame::OnQuit(wxCommandEvent& event)
{
	Close(TRUE);
}

void CMainFrame::OnOpen(wxCommandEvent& event)
{
	//std::cout << "coucou" << std::endl;
	wxFileDialog fenetre_dialogue(this, wxT("Choix d'un fichier"), wxT("./"), wxT("trian.tri"), wxT("*.*"), wxFD_OPEN);
	fenetre_dialogue.ShowModal();
	std::ifstream fo(fenetre_dialogue.GetPath().fn_str(), std::ios::in);
	// if open file failed, show an error message box
	if (!fo)
	{
		wxString errormsg, caption;
		errormsg.Printf(wxT("Unable to open file "));
		errormsg.Append(fenetre_dialogue.GetPath());
		caption.Printf(wxT("Erreur"));
		wxMessageDialog msg(this, errormsg, caption, wxOK | wxCENTRE | wxICON_ERROR);
		msg.ShowModal();
		return ;
	}
	int i, r,g,b, x[3], y[3];
	fo >> num_tri;
	for( i = 0 ; i < num_tri ; i++)
	{
		//tab_tri[i] = Triangle();
		fo  >> x[0]>> y[0]
			>> x[1]>> y[1]
			>> x[2]>> y[2];
		tab_tri[i].setP(0, x[0],y[0]);
		tab_tri[i].setP(1, x[1],y[1]);
		tab_tri[i].setP(2, x[2],y[2]);
		fo	>> r >> g >> b;
		tab_tri[i].colour.Set(r,g,b);
		fo >> tab_tri[i].thickness;
		tab_tri[i].existe = 1;
		tab_tri[i].nom = wxT("");
		tab_tri[i].nom << wxT("triangle ");
	   	tab_tri[i].nom = tab_tri[i].nom << i;
	}
	if(num_tri > 0)
	{
		this->activerGestionTriangles(true);
	}
}

void CMainFrame::supprimerTousTriangles()
{
	for(int i(0) ; i < NOMBRE_TRIANGLES_MAX ; i++)
		supprimerTriangle(i);
	num_tri = 0;
}

void CMainFrame::supprimerTriangle(int i)
{
	tab_tri[i].existe = 0;
	if( num_tri != 0)
		num_tri--;
}

void CMainFrame::setPointCourant(float x, float y)
{
	contexte_dessin.point_courant.x = x;
	contexte_dessin.point_courant.y = y;
}

void CMainFrame::activerGestionTriangles(bool b)
{
	m_toolbar->EnableTool(M_GESTION_TRIANGLES, b);
	this->GetMenuBar()->Enable(M_GESTION_TRIANGLES, b);
}

void CMainFrame::OnSave(wxCommandEvent& event)
{
	wxFileDialog fenetre_dialogue(this, wxT("Sauvegarde"), wxT("./"), wxT("trian.tri"), wxT("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	fenetre_dialogue.ShowModal();
	std::ofstream fs(fenetre_dialogue.GetPath().fn_str(), std::ios::out);
	if (!fs)
	{
		wxString errormsg, caption;
		errormsg.Printf(wxT("Unable to open file "));
		errormsg.Append(fenetre_dialogue.GetPath());
		caption.Printf(wxT("Erreur"));
		wxMessageDialog msg(this, errormsg, caption, wxOK | wxCENTRE | wxICON_ERROR);
		msg.ShowModal();
		return ;
	}
	fs << num_tri << std::endl;
	fs << std::endl;
	int i, r,g,b;
	for( i = 0 ; i < num_tri ; i++)
	{
		fs  << tab_tri[i].getPX(0) << " " << tab_tri[i].getPY(0) << " "
			<< tab_tri[i].getPX(1) << " " << tab_tri[i].getPY(1) << " "
			<< tab_tri[i].getPX(2) << " " << tab_tri[i].getPY(2) << std::endl;
		r = tab_tri[i].colour.Red();
		g = tab_tri[i].colour.Green();
		b = tab_tri[i].colour.Blue();
		fs	<< r << " " << g << " " << b << std::endl;
		fs	<< tab_tri[i].thickness << std::endl << std::endl;
	}
}

void CMainFrame::OnEpaisseurTrait(wxCommandEvent& event)
{
	EpaisseurDialog vdlg(this, -1, wxT("Epaisseur du trait"));
	vdlg.ShowModal();
}

void CMainFrame::OnColor(wxCommandEvent& event)
{
	ColorDialog vdlg(this, -1, wxT("Couleur"));
	vdlg.ShowModal();
}

void CMainFrame::OnGestionTriangles(wxCommandEvent& event)
{
	if( ! existeTriangle() )
	{
		activerGestionTriangles(false);
	}
	TriangleDialog vdlg(this, -1, wxT("Gestion des triangles"));
	vdlg.liste_triangles->Clear();
	int i ; 
	for(i = 0 ; i < NOMBRE_TRIANGLES_MAX ; i++)
	{
		if(tab_tri[i].existe != 0)
		{
			vdlg.liste_triangles->Append(tab_tri[i].nom);
		}
	}
	vdlg.liste_triangles->SetSelection(0);
	vdlg.ShowModal();
}

void CMainFrame::OnToolBar(wxCommandEvent& event)
{
	// On masque / affiche la barre d'outils
	if(m_toolbar->IsShownOnScreen())
		m_toolbar->Hide();
	else
		m_toolbar->Show(true);
}

void CMainFrame::OnVersion(wxCommandEvent& event)
{
	VersionDialog vdlg(this, -1, wxT("Version"));
	vdlg.ShowModal();
}

// S'il existe un triangle
bool CMainFrame::existeTriangle()
{
	bool res = false;
	for(int i(0) ; i < NOMBRE_TRIANGLES_MAX && res == false ; i++)
		if( tab_tri[i].existe == 1 )
			res = true;
	return res;
}

int CMainFrame::getNombreTriangles() { return num_tri; }
void CMainFrame::setNombreTriangles(int n) { num_tri = n; }
Triangle * CMainFrame::getTri(int n) { return &tab_tri[n]; }
wxColour * CMainFrame::getCouleurCourante() { return &contexte_dessin.couleur_courante; }
void CMainFrame::setCouleurCourante(int r, int g, int b) { contexte_dessin.couleur_courante.Set(r,g,b); }
void CMainFrame::setDrawing(bool b) { contexte_dessin.is_drawing = b; }
bool CMainFrame::isDrawing() { return contexte_dessin.is_drawing; }
Triangle * CMainFrame::getTriangleCourant() { return &contexte_dessin.triangle_courant; }
int CMainFrame::getNbPointsDefinis() { return contexte_dessin.nb_points_definis; }
point CMainFrame::getPointCourant() { return contexte_dessin.point_courant; }
int CMainFrame::getEpaisseurTraitCourante() { return contexte_dessin.epaisseur_trait_courante; }
void CMainFrame::setEpaisseurTraitCourante(int x) { contexte_dessin.epaisseur_trait_courante = x; }

void CMainFrame::ajoute_point_triangle_courant(float x, float y)
{
	Triangle * t = getTriangleCourant();
	switch( contexte_dessin.nb_points_definis)
	{
		case 0 : 
		case 1 :
			t->setP(contexte_dessin.nb_points_definis, x, y);
			contexte_dessin.nb_points_definis++;
			break;
		case 2 :
			t->setP(contexte_dessin.nb_points_definis, x, y);
			contexte_dessin.nb_points_definis = 0;
			setDrawing(false);
			ajouter_tri_courant_tab_tri();
			break;
		default :
			std::cout << "erreur : nb de points dans le triangle courant > 3 " << std::endl;
			break;
	}
}

void CMainFrame::ajouter_tri_courant_tab_tri()
{
	activerGestionTriangles(true);
	int i;
	if(num_tri < NOMBRE_TRIANGLES_MAX)
	{
		num_tri++;
		for(i = 0 ; i < NOMBRE_TRIANGLES_MAX ; i++)
			if(tab_tri[i].existe == 0)
				break;
		std::cout << "num trouvé : " << i << std::endl;
		Triangle * t = getTriangleCourant();
		tab_tri[i].setP(0,t->getPX(0),t->getPY(0));
		tab_tri[i].setP(1,t->getPX(1),t->getPY(1));
		tab_tri[i].setP(2,t->getPX(2),t->getPY(2));
		tab_tri[i].colour.Set(
				contexte_dessin.couleur_courante.Red(),
				contexte_dessin.couleur_courante.Green(),
				contexte_dessin.couleur_courante.Blue());
		tab_tri[i].thickness = contexte_dessin.epaisseur_trait_courante;
		tab_tri[i].existe = 1;
		tab_tri[i].nom = wxT("triangle ");
		tab_tri[i].nom << i;
	}
}
