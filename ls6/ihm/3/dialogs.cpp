#include "wx/wx.h" 
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/dynarray.h>
#include <wx/listctrl.h>
#include <wx/listbox.h>
#include <wx/combobox.h>
#include <wx/colour.h>
#include "dialogs.h"

BEGIN_EVENT_TABLE(VersionDialog, wxDialog)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(ColorDialog, wxDialog)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(EpaisseurDialog, wxDialog)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(TriangleDialog, wxDialog)
	EVT_BUTTON(TEXTE_PROPRIETES, TriangleDialog::OnProprietes)
	EVT_BUTTON(TEXTE_SUPPRIMER, TriangleDialog::OnSupprimer)
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
VersionDialog::~VersionDialog()
{
	/*
	delete button_ok;
	delete texte;
	delete conteneur;
	*/
}
EpaisseurDialog::EpaisseurDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	conteneur = new wxBoxSizer( wxVERTICAL );
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
EpaisseurDialog::~EpaisseurDialog()
{
	/*
	delete conteneur;
	delete texte;
	delete slider;
	delete button_ok;
	*/
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
ColorDialog::~ColorDialog()
{
	/*
	delete conteneur;
	delete texte;
	delete rb_couleurs;
	delete button_ok;
	*/
}
TriangleDialog::TriangleDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	main_frame = (CMainFrame *) parent;
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
TriangleDialog::~TriangleDialog()
{
	/*
	for( int i(0) ; i < 3 ; i++)
		delete conteneur[i];
	delete texte;
	delete liste_triangles;
	for( int i(0) ; i < 3 ; i++)
		delete bouton[i];
	*/
}
void TriangleDialog::OnProprietes(wxCommandEvent& event)
{
	int i(0), j(0);

	ProprietesDialog vdlg( this, -1, wxT("Proprietes"));
	wxString nouveau_texte( liste_triangles->GetStringSelection() );

	for(i = 0, j = -1 ; j < liste_triangles->GetSelection() ; i++)
	{
		if(main_frame->tab_tri[i].existe == 1)
			j++;
	}

	//std::cout<<main_frame->tab_tri[j].p1.x<<std::endl;
	
	// Choix couleur 
	if(main_frame->tab_tri[j].colour.Red() == 255)
		vdlg.radiobox_couleur->SetSelection(0);
	else if(main_frame->tab_tri[j].colour.Green() == 255)
		vdlg.radiobox_couleur->SetSelection(1);
	else
		vdlg.radiobox_couleur->SetSelection(2);

	vdlg.spinctl_epaisseur_trait->SetValue(main_frame->tab_tri[j].thickness);

	vdlg.ChangerTexteIdTriangle(nouveau_texte); // Mettre le nouveau texte
	vdlg.ShowModal();
}
void TriangleDialog::OnSupprimer(wxCommandEvent& event)
{
	// TODO FINIR ça qui fonctionne pas tout à fait 
	wxArrayInt selections;
	liste_triangles->GetSelections(selections);
	for( int i(0), j(-1), k(0) ; i < selections.GetCount() ; i++)
	{
		std::cout << "selection " << selections.Item(i) << std::endl;
		while( j < selections.Item(i))
		{
			if(main_frame->tab_tri[k].existe == 1)
				j++;
			k++;
		}
		
		liste_triangles->Delete(selections.Item(i));
		main_frame->tab_tri[j].existe = 0;
		k = 0;
	}
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
	textctrl_id_boite_texte = new wxTextCtrl(this, ID_BOITE_TEXTE, wxT("Valeur par défaut"));

	spinctl_epaisseur_trait = new wxSpinCtrl(this, ID_EPAISSEUR_TRAIT_SPINCTRL, 
			 wxEmptyString, wxDefaultPosition, wxDefaultSize, 
			 wxSP_ARROW_KEYS, 0, 100, 2, wxT("EpaisseurTrait"));

	wxString couleurs[] = { wxT("Rouge"), wxT("Vert"), wxT("Bleu")};
	radiobox_couleur = new wxRadioBox( this, COULEUR_RD_BOX, 
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
ProprietesDialog::~ProprietesDialog()
{
	/*
	for( int i(0) ; i < 3 ; i++)
		delete conteneur[i];
	delete texte_id_triangle;
	delete texte_epaisseur_trait;
	delete textctrl_id_boite_texte;
	delete spinctl_epaisseur_trait;
	delete radiobox_couleur;
	delete button_ok;
	*/
}
void ProprietesDialog::ChangerTexteIdTriangle(wxString& idTriangle)
{
	textctrl_id_boite_texte->Clear();
	textctrl_id_boite_texte->AppendText(idTriangle);
}
void ProprietesDialog::ChangerEpaisseurTrait(int epaisseur)
{
}
void ProprietesDialog::ChangerCouleurTriangle(int couleur)
{
}
