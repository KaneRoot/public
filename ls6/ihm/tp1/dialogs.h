#ifndef __DIALOGS_H__
#define __DIALOGS_H__

#include "wx/wx.h" 

enum { V_ID_TEXTE = 10000, SLIDER_EPAISSEUR_TRAIT, COULEUR_RD_BOX};
class VersionDialog: public wxDialog {
	public :
		     VersionDialog(wxWindow *parent, wxWindowID id, const wxString &title);
	private :
			 DECLARE_EVENT_TABLE()
};
class EpaisseurDialog: public wxDialog {
	public :
		     EpaisseurDialog(wxWindow *parent, wxWindowID id, const wxString &title);
	private :
			 DECLARE_EVENT_TABLE()
};
class ColorDialog: public wxDialog {
	public :
		     ColorDialog(wxWindow *parent, wxWindowID id, const wxString &title);
	private :
			 DECLARE_EVENT_TABLE()
};
class TriangleDialog: public wxDialog {
	public :
		     TriangleDialog(wxWindow *parent, wxWindowID id, const wxString &title);
	private :
			 DECLARE_EVENT_TABLE()
};
#endif
