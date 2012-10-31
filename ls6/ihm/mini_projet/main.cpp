#include "wx/wx.h" 
#include <wx/menu.h>
#include <wx/html/helpctrl.h>
#include "dialogs.h"
#include "mainframe.h"
#include "openglcanvas.h"

class MyApp: public wxApp 
{
	virtual bool OnInit();
	CMainFrame *m_MainFrame;
};


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() 
{
	m_MainFrame = new CMainFrame( wxString("Fenêtre", wxConvUTF8), wxPoint(50,50), wxSize(450,340) );
	wxMenuBar *menu_bar = new wxMenuBar;
	wxMenu *file_menu = new wxMenu;
	wxMenu *option_menu = new wxMenu;
	wxMenu *aide_menu = new wxMenu;

	// fichier
	menu_bar->Append(file_menu, wxT("Fichier"));
	file_menu->Append(M_NOUVEAU_FICHIER, wxT("Nouveau\tCtrl-N"));
	file_menu->AppendSeparator();
	file_menu->Append(M_OUVRIR, wxT("Ouvrir\tCtrl-O"));
	file_menu->Append(M_SAUVEGARDER, wxT("Sauvegarder\tCtrl-S"));
	file_menu->AppendSeparator();
	file_menu->Append(M_QUITTER, wxT("Quitter\tCtrl-Q"));

	// options
	menu_bar->Append(option_menu, wxT("Option"));
	option_menu->Append(M_EPAISSEUR_TRAIT, wxT("Epaisseur Trait\tCtrl-E"));
	option_menu->Append(M_COULEUR, wxT("Couleur\tCtrl-C"));
	option_menu->Append(M_GESTION_TRIANGLES, wxT("Gestion des triangles\tCtrl-T"));
	option_menu->AppendCheckItem(M_TOOLBAR, wxT("Barre de menu\tCtrl-B"));
	option_menu->Check(M_TOOLBAR, TRUE);
	option_menu->Enable(M_GESTION_TRIANGLES, false);

	// aide
	menu_bar->Append(aide_menu, wxT("Aide"));
	aide_menu->Append(M_AIDE, wxT("Ouvrir aide\tCtrl-A"));
	aide_menu->Append(M_VERSION, wxT("Version\tCtrl-V"));

	m_MainFrame->SetMenuBar(menu_bar);
	m_MainFrame->CreateMyToolBar();

	if(! m_MainFrame->help.Initialize(wxT("HELP")))
	{
		wxLogError(wxT("Cannot initialize the help system, aborting."));
		return FALSE;
	}

	m_MainFrame->Show(TRUE);

	return TRUE;
} 


