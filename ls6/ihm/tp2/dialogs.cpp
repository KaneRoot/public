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
	conteneur = new wxBoxSizer( wxVERTICAL );
	texte = new wxStaticText( this, V_ID_TEXTE, wxT("Version 2.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	button_ok = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	conteneur->Add( texte, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur->Add( button_ok, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur );
	conteneur->Fit( this );
	conteneur->SetSizeHints( this );
	 
}
EpaisseurDialog::EpaisseurDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	conteneur = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer *conteneur = new wxBoxSizer( wxVERTICAL );
	texte = new wxStaticText( this, V_ID_TEXTE, wxT("Choisir la nouvelle épaisseur de trait"));

	slider = new wxSlider(this, SLIDER_EPAISSEUR_TRAIT, 5, 0, 10, wxDefaultPosition, 
			wxDefaultSize, wxSL_HORIZONTAL, wxDefaultValidator, wxT("Epaisseur"));
	button_ok = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	conteneur->Add( texte, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur->Add( slider, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur->Add( button_ok, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur );
	conteneur->Fit( this );
	conteneur->SetSizeHints( this );
	 
}
ColorDialog::ColorDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	conteneur = new wxBoxSizer( wxVERTICAL );
	texte = new wxStaticText( this, V_ID_TEXTE, wxT("Choisir la nouvelle couleur"));

	wxString strs8[] = { wxT("Rouge"), wxT("Vert"), wxT("Bleu")};
	rb_couleurs = new wxRadioBox(this, COULEUR_RD_BOX, wxT("Couleurs"), wxDefaultPosition, wxDefaultSize, 3, strs8);

	button_ok = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	conteneur->Add( texte, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur->Add( rb_couleurs, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur->Add( button_ok, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur );
	conteneur->Fit( this );
	conteneur->SetSizeHints( this );
	 
}
TriangleDialog::TriangleDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	// Conteneurs
	conteneur[0] = new wxBoxSizer( wxVERTICAL );
	conteneur[1] = new wxBoxSizer( wxHORIZONTAL );
	conteneur[2] = new wxBoxSizer( wxVERTICAL );

	texte = new wxStaticText( this, V_ID_TEXTE, wxT("Liste des triangles"));
	wxString choix[] = { wxT("Triangle0"), wxT("Triangle1"), wxT("Triangle2") };
	liste_triangles = new wxListBox(this, ID_LISTE_BOITE, wxDefaultPosition,  wxDefaultSize, 3, choix);

	// Boutons
	bouton[0] = new wxButton( this, TEXTE_PROPRIETES, wxT("Propriétés"), wxDefaultPosition);
	bouton[1] = new wxButton( this, TEXTE_SUPPRIMER, wxT("Supprimer"), wxDefaultPosition);
	bouton[2] = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	conteneur[0]->Add( texte, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[0]->Add( conteneur[1], 0, wxALIGN_CENTRE|wxALL, 5 );

	conteneur[1]->Add( liste_triangles, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[1]->Add( conteneur[2], 0, wxALIGN_CENTRE|wxALL, 5 );

	conteneur[2]->Add( bouton[0], 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[2]->Add( bouton[1], 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[2]->Add( bouton[2], 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur[0] );
	conteneur[0]->Fit( this );
	conteneur[0]->SetSizeHints( this );
}
ProprietesDialog::ProprietesDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	// Conteneurs
	conteneur[0] = new wxBoxSizer( wxVERTICAL );
	conteneur[1] = new wxBoxSizer( wxHORIZONTAL );
	conteneur[2] = new wxBoxSizer( wxVERTICAL );

	// Textes
	texte_id_triangle = new wxStaticText( this, V_ID_TEXTE, wxT("Identifiant du triangle"));

	texte_epaisseur_trait = new wxStaticText( this, V_ID_TEXTE, wxT("Epaisseur trait"));

	// Autres objets
	textctrl_id_boite_texte = new wxTextCtrl(this, ID_BOITE_TEXTE, wxT("Triangle 0"));

	spinctl_epaisseur_trait = new wxSpinCtrl(this, ID_EPAISSEUR_TRAIT_SPINCTRL, 
			 wxEmptyString, wxDefaultPosition, wxDefaultSize, 
			 wxSP_ARROW_KEYS, 0, 100, 2, wxT("EpaisseurTrait"));

	wxString couleurs[] = { wxT("Rouge"), wxT("Vert"), wxT("Bleu")};
	radiobox_couleur = new wxRadioBox(this, COULEUR_RD_BOX, 
			wxT("Couleurs"), wxDefaultPosition, wxDefaultSize, 3, couleurs);

	button_ok = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	// Ajout des objets aux conteneurs
	conteneur[0]->Add( conteneur[1], 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[0]->Add( button_ok, 0, wxALIGN_CENTRE|wxALL, 5 );

	conteneur[1]->Add( conteneur[2], 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[1]->Add( radiobox_couleur, 0, wxALIGN_CENTRE|wxALL, 5 );

	conteneur[2]->Add( texte_id_triangle, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[2]->Add( textctrl_id_boite_texte, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[2]->Add( texte_epaisseur_trait, 0, wxALIGN_CENTRE|wxALL, 5 );
	conteneur[2]->Add( spinctl_epaisseur_trait, 0, wxALIGN_CENTRE|wxALL, 5 );

	// Affichage
	this->SetAutoLayout( TRUE );
	this->SetSizer( conteneur[0] );
	conteneur[0]->Fit( this );
	conteneur[0]->SetSizeHints( this );
	 
}
