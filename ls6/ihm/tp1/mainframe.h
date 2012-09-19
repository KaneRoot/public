
#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "wx/wx.h"

enum { M_NOUVEAU_FICHIER, M_OUVRIR, M_SAUVEGARDER, M_QUITTER, M_EPAISSEUR_TRAIT, M_COULEUR, M_GESTION_TRIANGLES, M_VERSION};

class CMainFrame: public wxFrame {
public:
	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:

	DECLARE_EVENT_TABLE();


}; //MyFrame

#endif
