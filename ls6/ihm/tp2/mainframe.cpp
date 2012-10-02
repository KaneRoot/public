#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>

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
: wxFrame((wxFrame *)NULL, -1, title, pos, size) 
{
} //constructor

void CMainFrame::CreateMyToolBar()
{
	m_toolbar = CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL | wxTB_TEXT, TOOLBAR_TOOLS);
	wxBitmap toolBarBitmaps[4];

	toolBarBitmaps[0] = wxBitmap(wxT("new.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[1] = wxBitmap(wxT("open.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[2] = wxBitmap(wxT("save.bmp"),wxBITMAP_TYPE_BMP);
	toolBarBitmaps[3] = wxBitmap(wxT("draw.bmp"),wxBITMAP_TYPE_BMP);

	m_toolbar->SetToolBitmapSize(wxSize(toolBarBitmaps[0].GetWidth(), toolBarBitmaps[0].GetHeight()));
	m_toolbar->AddTool(M_NOUVEAU_FICHIER, wxT("Nouveau"), toolBarBitmaps[0]);
	m_toolbar->AddTool(M_OUVRIR, wxT("Ouvrir"), toolBarBitmaps[1]);
	m_toolbar->AddTool(M_SAUVEGARDER, wxT("Sauvegarder"), toolBarBitmaps[2]);
	m_toolbar->AddSeparator();
	m_toolbar->AddTool(M_GESTION_TRIANGLES, wxT("Gestion des triangles"), toolBarBitmaps[3], wxT("Gestion des triangles"));

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
}
void CMainFrame::OnSave(wxCommandEvent& event)
{
}
void CMainFrame::OnEpaisseurTrait(wxCommandEvent& event)
{
}
void CMainFrame::OnColor(wxCommandEvent& event)
{
}
void CMainFrame::OnGestionTriangles(wxCommandEvent& event)
{
}
void CMainFrame::OnToolBar(wxCommandEvent& event)
{
}
void CMainFrame::OnVersion(wxCommandEvent& event)
{
}
