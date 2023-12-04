/***************************************************************
 * Name:      wxWidgets_3_2_2_1_EdgeMain.h
 * Purpose:   Defines Application Frame
 * Author:    Adrian Chis (chis.adrian@gmail.com)
 * Created:   2023-08-24
 * Copyright: Adrian Chis ()
 * License:
 **************************************************************/

#ifndef WXWIDGETS_3_2_2_1_EDGEMAIN_H
#define WXWIDGETS_3_2_2_1_EDGEMAIN_H

//(*Headers(wxWidgets_3_2_2_1_EdgeFrame)
#include <wx/frame.h>
//*)


#define wxUSE_WEBVIEW 1
#include "wx/webview.h"


class wxWidgets_3_2_2_1_EdgeFrame: public wxFrame
{
    public:

        wxWidgets_3_2_2_1_EdgeFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxWidgets_3_2_2_1_EdgeFrame();

    private:
        void OnwxWebView(wxWebViewEvent& event);

        static const long ID_WEBW;

        //(*Handlers(wxWidgets_3_2_2_1_EdgeFrame)
        void OnQuit(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxWidgets_3_2_2_1_EdgeFrame)
        //*)

        //(*Declarations(wxWidgets_3_2_2_1_EdgeFrame)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXWIDGETS_3_2_2_1_EDGEMAIN_H
