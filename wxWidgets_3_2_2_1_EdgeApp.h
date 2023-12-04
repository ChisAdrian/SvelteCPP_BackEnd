/***************************************************************
 * Name:      wxWidgets_3_2_2_1_EdgeApp.h
 * Purpose:   Defines Application Class
 * Author:    Adrian Chis (chis.adrian@gmail.com)
 * Created:   2023-08-24
 * Copyright: Adrian Chis ()
 * License:
 **************************************************************/

#ifndef WXWIDGETS_3_2_2_1_EDGEAPP_H
#define WXWIDGETS_3_2_2_1_EDGEAPP_H

#include <wx/app.h>
#include "wx/webview.h"

class wxWidgets_3_2_2_1_EdgeApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // WXWIDGETS_3_2_2_1_EDGEAPP_H
