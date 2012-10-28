#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include <wx/wx.h>
#include <wx/accel.h>
#include <wx/toolbar.h>
#include <wx/glcanvas.h>

class OpenGLCanvas;

#include "openglcanvas.h"
#include "triangle.h"
#include "dialogs.h"

enum { NOMBRE_TRIANGLES_MAX = 5 };

enum { M_NOUVEAU_FICHIER, M_OUVRIR, M_SAUVEGARDER, M_QUITTER, 
	M_EPAISSEUR_TRAIT, M_COULEUR, M_GESTION_TRIANGLES, M_TOOLBAR,
	M_VERSION, TOOLBAR_TOOLS,
	CANVAS_OPENGL
};

class CMainFrame: public wxFrame {
public:
	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	int num_tri;
	Triangle tab_tri[5];

	void CreateMyToolBar();
	bool existeTriangle();
	void supprimerTriangle(int i);
	void supprimerTousTriangles();
	void activerGestionTriangles(bool oui_ou_non);
	OpenGLCanvas *canvas_opengl;
	int getNombreTriangles();
	void setNombreTriangles(int n);
	Triangle * getTri(int n);
	wxColour * getCouleurCourante();

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
