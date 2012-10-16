
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

	int epaisseur_trait_courante;
	wxColour couleur_courante; 
	bool is_drawing;

	void OnNew(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnEpaisseurTrait(wxCommandEvent& event);
	void OnColor(wxCommandEvent& event);
	void OnGestionTriangles(wxCommandEvent& event);
	void OnToolBar(wxCommandEvent& event);
	void OnVersion(wxCommandEvent& event);

	DECLARE_EVENT_TABLE();
}; //MyFrame

#endif
