
#include "wx/wx.h" 
#include "mainframe.h"
#include <wx/menu.h>

class MyApp: public wxApp 
{
	virtual bool OnInit();
	CMainFrame *m_MainFrame;
};


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit() 
{
	enum { M_NOUVEAU_FICHIER, M_OUVRIR, M_SAUVEGARDER, M_QUITTER, M_EPAISSEUR_TRAIT, M_COULEUR, M_GESTION_TRIANGLES, M_VERSION};
	int i = 0;
	m_MainFrame = new CMainFrame( wxString("Fenêtre", wxConvUTF8), wxPoint(50,50), wxSize(450,340) );
	wxMenuBar *menu_bar = new wxMenuBar;
	wxMenu *file_menu = new wxMenu;
	menu_bar->Append(file_menu, wxT("Fichier"));
	file_menu->Append(M_NOUVEAU_FICHIER, wxT("Nouveau\tCtrl-N"));
	file_menu->Append(M_OUVRIR, wxT("Ouvrir\tCtrl-O"));
	file_menu->Append(M_SAUVEGARDER, wxT("Sauvegarder\tCtrl-S"));
	file_menu->Append(M_QUITTER, wxT("Quitter\tCtrl-Q"));

	wxMenu *option_menu = new wxMenu;
	menu_bar->Append(option_menu, wxT("Option"));
	option_menu->Append(M_EPAISSEUR_TRAIT, wxT("Epaisseur Trait\tCtrl-E"));
	option_menu->Append(M_COULEUR, wxT("Couleur\tCtrl-C"));
	option_menu->Append(M_GESTION_TRIANGLES, wxT("Gestion des triangles\tCtrl-T"));

	wxMenu *aide_menu = new wxMenu;
	menu_bar->Append(aide_menu, wxT("Aide"));
	aide_menu->Append(M_VERSION, wxT("Version\tCtrl-V"));

	m_MainFrame->SetMenuBar(menu_bar);
	m_MainFrame->Show(TRUE);

	return TRUE;
} 


