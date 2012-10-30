#ifndef __DIALOGS_H__
#define __DIALOGS_H__

#include <wx/wx.h> 
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/dynarray.h>
#include <wx/listctrl.h>
#include <wx/listbox.h>
#include <wx/combobox.h>
#include <wx/colour.h>
#include <wx/sizer.h>

#include "mainframe.h"

enum { V_ID_TEXTE = 10000, SLIDER_EPAISSEUR_TRAIT, COULEUR_RD_BOX, 
	ID_LISTE_BOITE, TEXTE_PROPRIETES, TEXTE_SUPPRIMER, ID_BOITE_TEXTE,
	ID_EPAISSEUR_TRAIT_SPINCTRL};

class VersionDialog: public wxDialog {
	public :
		    VersionDialog(wxWindow *parent, wxWindowID id, const wxString &title);
			virtual	~VersionDialog();
	private :
			wxBoxSizer *conteneur;
			wxStaticText *texte;
			wxButton *button_ok;
			DECLARE_EVENT_TABLE()
};
class EpaisseurDialog: public wxDialog {
	public :
		    EpaisseurDialog(wxWindow *parent, wxWindowID id, const wxString &title);
			virtual ~EpaisseurDialog();
	private :
			wxBoxSizer *conteneur;
			wxStaticText *texte;
			wxSlider *slider;
			wxButton *button_ok;
			DECLARE_EVENT_TABLE()
};
class ColorDialog: public wxDialog {
	public :
		    ColorDialog(wxWindow *parent, wxWindowID id, const wxString &title);
			virtual ~ColorDialog();
	private :
			CMainFrame *main_frame;
			wxBoxSizer *conteneur;
			wxStaticText *texte;
			wxRadioBox *rb_couleurs;
			wxButton *button_ok;
			void OnChangerCouleur(wxCommandEvent& e);
			DECLARE_EVENT_TABLE()
};
class TriangleDialog: public wxDialog {
	public :
		    TriangleDialog(wxWindow *parent, wxWindowID id, const wxString &title);
			virtual ~TriangleDialog();
			wxListBox *liste_triangles;
	private :
			CMainFrame *main_frame;
			wxBoxSizer *conteneur[3];
			wxStaticText *texte;
			wxButton *bouton[3];
			void OnProprietes(wxCommandEvent& event);
			void OnSupprimer(wxCommandEvent& event);
			DECLARE_EVENT_TABLE()
};
class ProprietesDialog: public wxDialog {
	public :
		    ProprietesDialog(wxWindow *parent, wxWindowID id, const wxString &title, Triangle* ptriangle);
			virtual ~ProprietesDialog();
			void ChangerTexteIdTriangle(wxString& idTriangle);
			void ChangerEpaisseurTrait(wxCommandEvent& e);
			void ChangerCouleurTriangle(wxCommandEvent& e);
			wxRadioBox *radiobox_couleur;
			wxSpinCtrl *spinctl_epaisseur_trait;

	private :
			Triangle * tri;
			CMainFrame *main_frame;
			wxBoxSizer *conteneur[3];
			wxStaticText *texte_epaisseur_trait;
			wxStaticText *texte_id_triangle;
			wxTextCtrl *textctrl_id_boite_texte;
			wxButton *button_ok;
			DECLARE_EVENT_TABLE()
};
#endif
