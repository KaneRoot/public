
#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "wx/wx.h"

enum { M_NOUVEAU_FICHIER, M_OUVRIR, M_SAUVEGARDER, M_QUITTER, 
	M_EPAISSEUR_TRAIT, M_COULEUR, M_GESTION_TRIANGLES, M_TOOLBAR,
	M_VERSION, TOOLBAR_TOOLS};


class CMainFrame: public wxFrame {
public:
	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CreateMyToolBar();

private:
	wxToolBar *m_toolbar;
	DECLARE_EVENT_TABLE();


}; //MyFrame

#endif
