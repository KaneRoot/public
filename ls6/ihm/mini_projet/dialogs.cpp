#include "dialogs.h"

BEGIN_EVENT_TABLE(VersionDialog, wxDialog)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(ColorDialog, wxDialog)
	EVT_RADIOBOX(COULEUR_RD_BOX, ColorDialog::OnChangerCouleur)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(EpaisseurDialog, wxDialog)
	EVT_SCROLL(EpaisseurDialog::OnScroll)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(TriangleDialog, wxDialog)
	EVT_BUTTON(TEXTE_PROPRIETES, TriangleDialog::OnProprietes)
	EVT_BUTTON(TEXTE_SUPPRIMER, TriangleDialog::OnSupprimer)
END_EVENT_TABLE ()
BEGIN_EVENT_TABLE(ProprietesDialog, wxDialog)
	EVT_SPINCTRL(ID_EPAISSEUR_TRAIT_SPINCTRL, ProprietesDialog::ChangerEpaisseurTrait)
	EVT_RADIOBOX(COULEUR_RD_BOX, ProprietesDialog::ChangerCouleurTriangle)
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
	main_frame = (CMainFrame *) parent;
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


void EpaisseurDialog::OnScroll(wxScrollEvent& e)
{
	//std::cout << "coucou " << slider->GetValue() << std::endl;
	main_frame->setEpaisseurTraitCourante(slider->GetValue());
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
	main_frame = (CMainFrame *) parent;
	conteneur = new wxBoxSizer( wxVERTICAL );
	texte = new wxStaticText( this, V_ID_TEXTE, wxT("Choisir la nouvelle couleur"));
	wxString strs8[] = { wxT("Rouge"), wxT("Vert"), wxT("Bleu")};
	rb_couleurs = new wxRadioBox(this, COULEUR_RD_BOX, 
			wxT("Couleurs"), wxDefaultPosition, wxDefaultSize, 3, strs8);
	button_ok = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);
	int indice_couleur = 0;
	if(main_frame->getCouleurCourante()->Green() == 255)
		indice_couleur = 1;
	else if(main_frame->getCouleurCourante()->Blue() == 255)
		indice_couleur = 2;

	rb_couleurs->SetSelection(indice_couleur);
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
void ColorDialog::OnChangerCouleur(wxCommandEvent& e)
{
	switch(rb_couleurs->GetSelection())
	{
		case 0 : main_frame->setCouleurCourante(255,0,0); break;
		case 1 : main_frame->setCouleurCourante(0,255,0); break;
		default : main_frame->setCouleurCourante(0,0,255); break;
	}
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

	wxString nouveau_texte( liste_triangles->GetStringSelection() );

	for(i = 0, j = -1 ; j < liste_triangles->GetSelection() ; i++)
	{
		if(main_frame->getTri(i)->existe())
			j++;
	}

	ProprietesDialog vdlg( this, -1, wxT("Proprietes"), main_frame->getTri(j));
	/*
	// Choix couleur 
	if(main_frame->getTri(j)->colour.Red() == 255)
		vdlg.radiobox_couleur->SetSelection(0);
	if(main_frame->getTri(j)->colour.Green() == 255)
		vdlg.radiobox_couleur->SetSelection(1);
	else
		vdlg.radiobox_couleur->SetSelection(2);
	*/
	vdlg.spinctl_epaisseur_trait->SetValue(main_frame->getTri(j)->thickness);
	
	vdlg.ChangerTexteIdTriangle(nouveau_texte); // Mettre le nouveau texte
	vdlg.ShowModal();
}

void TriangleDialog::OnSupprimer(wxCommandEvent& event)
{
	wxArrayInt selections;
	liste_triangles->GetSelections(selections);
	for( int i(0), j(-1), k(0) ; i < selections.GetCount() ; i++)
	{
		k = -1;
		j = -1;
		while( j < selections.Item(i))
		{
			k++;
			if(main_frame->tab_tri[k].existe())
				j++;
		}
		liste_triangles->Delete(selections.Item(i));
		main_frame->supprimerTriangle(k); 
	}
	if( ! main_frame->existeTriangle())
	{
		main_frame->activerGestionTriangles(false);
		Close();
	}
}

ProprietesDialog::ProprietesDialog( wxWindow *parent, wxWindowID id, const wxString &title, Triangle* ptriangle) : wxDialog( parent, id, title)
{
	tri = (Triangle *) ptriangle;
	main_frame = (CMainFrame *) parent;
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
	
	// Choix couleur 
	if(tri->colour.Red() == 255)
		radiobox_couleur->SetSelection(0);
	else if(tri->colour.Green() == 255)
		radiobox_couleur->SetSelection(1);
	else
		radiobox_couleur->SetSelection(2);

	spinctl_epaisseur_trait->SetValue(tri->thickness);
	ChangerTexteIdTriangle(tri->nom);
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

void ProprietesDialog::ChangerEpaisseurTrait(wxSpinEvent& e)
{
	//std::cout << "Epaisseur Trait : " << e.GetInt() << std::endl;
	tri->setThickness(e.GetInt());
}

void ProprietesDialog::ChangerCouleurTriangle(wxCommandEvent& e)
{
	switch(e.GetInt())
	{
		case 0 : tri->colour.Set(255,0,0); break;
		case 1 : tri->colour.Set(0,255,0); break;
		case 2 : tri->colour.Set(0,0,255); break;
		default :
			std::cout << "erreur sélection couleur " << std::endl;
			break;
	}
}
