#include "wx/wx.h" 
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include "dialogs.h"

BEGIN_EVENT_TABLE(VersionDialog, wxDialog)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(ColorDialog, wxDialog)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(EpaisseurDialog, wxDialog)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(TriangleDialog, wxDialog)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(ProprietesDialog, wxDialog)
END_EVENT_TABLE ()

VersionDialog::VersionDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );
	wxStaticText *item1 = new wxStaticText( this, V_ID_TEXTE, 
			wxT("Version 1.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	wxButton *item2 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
	item0->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( item0 );
	item0->Fit( this );
	item0->SetSizeHints( this );
	 
}
EpaisseurDialog::EpaisseurDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );
	wxStaticText *item1 = new wxStaticText( this, V_ID_TEXTE, 
			wxT("Choisir la nouvelle épaisseur de trait"), 
			wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	wxSlider *item2 = new wxSlider(this, SLIDER_EPAISSEUR_TRAIT, 5, 0, 10, wxDefaultPosition, 
			wxDefaultSize, wxSL_HORIZONTAL, wxDefaultValidator, wxT("Epaisseur"));
	wxButton *item3 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
	item0->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );
	item0->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( item0 );
	item0->Fit( this );
	item0->SetSizeHints( this );
	 
}
ColorDialog::ColorDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );
	wxStaticText *item1 = new wxStaticText( this, V_ID_TEXTE, 
			wxT("Choisir la nouvelle couleur"), 
			wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

	wxString strs8[] = { wxT("Rouge"), wxT("Vert"), wxT("Bleu")};
	wxRadioBox *item2 = new wxRadioBox(this, COULEUR_RD_BOX, wxT("Couleurs"), wxDefaultPosition, wxDefaultSize, 3, strs8);

	wxButton *item3 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
	item0->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );
	item0->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( item0 );
	item0->Fit( this );
	item0->SetSizeHints( this );
	 
}
TriangleDialog::TriangleDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	// Conteneurs
	wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer *item2 = new wxBoxSizer( wxVERTICAL );

	wxStaticText *item3 = new wxStaticText( this, V_ID_TEXTE, 
			wxT("Liste des triangles"), 
			wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	wxString choix[] = { wxT("Triangle0"),wxT("Triangle1"),wxT("Triangle2") };
	wxListBox *item4 = new wxListBox(this, ID_LISTE_BOITE, wxDefaultPosition,  wxDefaultSize, 3, choix);

	// Boutons
	wxButton *item5 = new wxButton( this, TEXTE_PROPRIETES, wxT("Propriétés"), wxDefaultPosition);
	wxButton *item6 = new wxButton( this, TEXTE_SUPPRIMER, wxT("Supprimer"), wxDefaultPosition);
	wxButton *item7 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	item0->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );
	item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );

	item1->Add( item4, 0, wxALIGN_CENTRE|wxALL, 5 );
	item1->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );

	item2->Add( item5, 0, wxALIGN_CENTRE|wxALL, 5 );
	item2->Add( item6, 0, wxALIGN_CENTRE|wxALL, 5 );
	item2->Add( item7, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( item0 );
	item0->Fit( this );
	item0->SetSizeHints( this );
	 
}
ProprietesDialog::ProprietesDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	// Conteneurs
	wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer *item2 = new wxBoxSizer( wxVERTICAL );

	wxStaticText *item3 = new wxStaticText( this, V_ID_TEXTE, 
			wxT("Identifiant du triangle"), 
			wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	wxTextCtrl *item4 = new wxTextCtrl(this, ID_BOITE_TEXTE);
	wxStaticText *item5 = new wxStaticText( this, V_ID_TEXTE, 
			wxT("Epaisseur trait"), 
			wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

	 wxSpinCtrl *item6 = new wxSpinCtrl(this, ID_EPAISSEUR_TRAIT_SPINCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 2, wxT("EpaisseurTrait"));

	wxString couleurs[] = { wxT("Rouge"), wxT("Vert"), wxT("Bleu")};
	wxRadioBox *item7 = new wxRadioBox(this, COULEUR_RD_BOX, wxT("Couleurs"), wxDefaultPosition, wxDefaultSize, 3, couleurs);

	// Boutons
	wxButton *item8 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );

	item1->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );
	item1->Add( item7, 0, wxALIGN_CENTRE|wxALL, 5 );

	item2->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );
	item2->Add( item4, 0, wxALIGN_CENTRE|wxALL, 5 );
	item2->Add( item5, 0, wxALIGN_CENTRE|wxALL, 5 );
	item2->Add( item6, 0, wxALIGN_CENTRE|wxALL, 5 );
	item0->Add( item8, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( item0 );
	item0->Fit( this );
	item0->SetSizeHints( this );
	 
}
