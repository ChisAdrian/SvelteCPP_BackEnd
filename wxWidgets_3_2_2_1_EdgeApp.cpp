/***************************************************************
 * Name:      wxWidgets_3_2_2_1_EdgeApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Adrian Chis (chis.adrian@gmail.com)
 * Created:   2023-08-24
 * Copyright: Adrian Chis ()
 * License:
 **************************************************************/

#include "wxWidgets_3_2_2_1_EdgeApp.h"

//(*AppHeaders
#include "wxWidgets_3_2_2_1_EdgeMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxWidgets_3_2_2_1_EdgeApp);

bool wxWidgets_3_2_2_1_EdgeApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxWidgets_3_2_2_1_EdgeFrame* Frame = new wxWidgets_3_2_2_1_EdgeFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
