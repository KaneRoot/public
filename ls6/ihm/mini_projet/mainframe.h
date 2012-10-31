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
#include <wx/html/helpctrl.h>

class OpenGLCanvas;

#include "openglcanvas.h"
#include "triangle.h"
#include "definitions.h"
#include "dialogs.h"

typedef struct {
	bool is_drawing;
	int nb_points_definis;
	point point_courant;
	int epaisseur_trait_courante;
	wxColour couleur_courante; 
	Triangle triangle_courant; // le triangle qu'on crée
} ctxt_dessin;


enum { NOMBRE_TRIANGLES_MAX = 5 };

enum { M_NOUVEAU_FICHIER, M_OUVRIR, M_SAUVEGARDER, M_QUITTER, 
	M_EPAISSEUR_TRAIT, M_COULEUR, M_GESTION_TRIANGLES, M_TOOLBAR,
	M_VERSION, M_AIDE, TOOLBAR_TOOLS,
	CANVAS_OPENGL
};

class CMainFrame: public wxFrame {
public:
	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	int num_tri;
	Triangle tab_tri[NOMBRE_TRIANGLES_MAX];

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
	void setCouleurCourante(int r, int g, int b);
	void setDrawing(bool b);
	bool isDrawing();
	void setPointCourant(float x, float y);
	point getPointCourant();
	Triangle * getTriangleCourant();
	void ajoute_point_triangle_courant(float x, float y);
	int getNbPointsDefinis();
	void setEpaisseurTraitCourante(int x);
	int getEpaisseurTraitCourante();
	wxHtmlHelpController help;

private:
	wxToolBar *m_toolbar;
	ctxt_dessin contexte_dessin;

	void OnNew(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnEpaisseurTrait(wxCommandEvent& event);
	void OnColor(wxCommandEvent& event);
	void OnGestionTriangles(wxCommandEvent& event);
	void OnToolBar(wxCommandEvent& event);
	void OnVersion(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);

	void ajouter_tri_courant_tab_tri();
	DECLARE_EVENT_TABLE();
}; //MyFrame

#endif
