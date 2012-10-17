#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include <wx/wx.h>
#include <wx/accel.h>
#include <wx/toolbar.h>

#include "triangle.h"
#include "dialogs.h"
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
	int i, r,g,b;
	
	fo >> num_tri;
	for( i = 0 ; i < num_tri ; i++)
	{
		//tab_tri[i] = Triangle();
		
		fo  >> tab_tri[i].p1.x >> tab_tri[i].p1.y 
			>> tab_tri[i].p2.x >> tab_tri[i].p2.y 
			>> tab_tri[i].p3.x >> tab_tri[i].p3.y;
		fo	>> r >> g >> b;
		tab_tri[i].colour.Set(r,g,b);
		fo >> tab_tri[i].thickness;
	}
	if(num_tri > 0)
	{
		m_toolbar->EnableTool(M_GESTION_TRIANGLES, true);
		this->GetMenuBar()->Enable(M_GESTION_TRIANGLES, true);
	}

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
		fs  << tab_tri[i].p1.x << " " << tab_tri[i].p1.y << " "
			<< tab_tri[i].p2.x << " " << tab_tri[i].p2.y << " "
			<< tab_tri[i].p3.x << " " << tab_tri[i].p3.y << std::endl;
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
	TriangleDialog vdlg(this, -1, wxT("Gestion des triangles"));
	vdlg.liste_triangles->Clear();
	int i ; 
	for(i = 0 ; i < num_tri ; i++)
	{
		vdlg.liste_triangles->Append(wxT("triangle ") );
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
