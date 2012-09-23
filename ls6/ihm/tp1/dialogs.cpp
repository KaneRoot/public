#include "wx/wx.h" 
#include "dialogs.h"

BEGIN_EVENT_TABLE(VersionDialog, wxDialog)

END_EVENT_TABLE ()

VersionDialog::VersionDialog( wxWindow *parent, wxWindowID id, const wxString &title) : wxDialog( parent, id, title)
{
	wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );
	wxStaticText *item1 = new wxStaticText( this, V_ID_TEXTE, wxT("Version 1.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	wxButton *item2 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

	item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
	item0->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );

	this->SetAutoLayout( TRUE );
	this->SetSizer( item0 );
	item0->Fit( this );
	item0->SetSizeHints( this );
	 
}
