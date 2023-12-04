/***************************************************************
 * Name:      wxWidgets_3_2_2_1_EdgeMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Adrian Chis (chis.adrian@gmail.com)
 * Created:   2023-08-24
 * Copyright: Adrian Chis ()
 * License:
 **************************************************************/

#include "wxWidgets_3_2_2_1_EdgeMain.h"

#include <iostream>
#include "httplib.h"
#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"

#include <nanodbc_exec/nanodbc.h>
#include <nanodbc_exec/mssql_functions.hpp>
#include <thread>         // std::thread

std::string connStr = "DRIVER={SQL Server};....";
using json = nlohmann::json; // Alias the json namespace

#include <algorithm>  // for std::remove_if
#include <cctype>     // for std::isascii


bool isNonAscii(unsigned char c) {
    return static_cast<int>(c) > 127;
}

void sanitize(std::string &inputString)
{
// Use std::remove_if with the isNonAscii function
    inputString.erase(
        std::remove_if(inputString.begin(), inputString.end(), isNonAscii),
        inputString.end()
    );


}


int th_main()
{
    // Create an httplib Server instance
    httplib::Server server;

    // Handle the OPTIONS request for preflight check
    server.Options("/data", [](const httplib::Request& req, httplib::Response& res)
    {
        // Set the CORS headers for the preflight request
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        // Send a successful response
        res.status = 200;
    });

    // Define a route handler for the "/data" path
    server.Post("/data", [](const httplib::Request& req, httplib::Response& res)
    {
        // Set the CORS headers
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        json rec_data = json::parse(req.body);
        std::string qTXT = rec_data["sql"];

        // Create a JSON array
        json json_data = json::array();
        auto data =  mssql_select_vector(qTXT,connStr,true);
        for(size_t r=0; r<data.size(); r++)
        {
            //ELL70 BI D TD EU 2G°
            json json_row = json::object();
            for(size_t c=0; c<data[r].size(); c++)
            {
                std::string rawData = data[r][c];
                sanitize(rawData);
                json_row[ std::to_string(c)  ] = rawData;
            }
            json_data.push_back(json_row);
        }
        res.set_content(json_data.dump(), "application/json");
    });

    // Start the server and listen on port 8080
    server.listen("localhost", 5000);
    return 0;
}


const long wxWidgets_3_2_2_1_EdgeFrame::ID_WEBW = wxNewId();

//(*InternalHeaders(wxWidgets_3_2_2_1_EdgeFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

// helper functions
enum wxbuildinfoformat
{
    short_f,
    long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f)
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wxWidgets_3_2_2_1_EdgeFrame)
//*)

BEGIN_EVENT_TABLE(wxWidgets_3_2_2_1_EdgeFrame, wxFrame)
//(*EventTable(wxWidgets_3_2_2_1_EdgeFrame)
//*)
END_EVENT_TABLE()

#define wxUSE_WEBVIEW 1
#include "wx/webview.h"

#include <wx/webview.h>

#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream

wxWebView *webView;

wxWidgets_3_2_2_1_EdgeFrame::wxWidgets_3_2_2_1_EdgeFrame(wxWindow *parent, wxWindowID id)
{
    //(*Initialize(wxWidgets_3_2_2_1_EdgeFrame)
    Create(parent, id, _("SvelteTemplate"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(432,468));
    //*)
        SetIcon(wxIcon("aaaa"));

        std::ifstream inFile;
        inFile.open("source.html"); //open the input file
        std::stringstream strStream;
        strStream << inFile.rdbuf(); //read the file
        std::string str = strStream.str(); //str holds the content of the file

        webView = wxWebView::New(this, ID_WEBW); //, "about:blank", wxDefaultPosition, wxDefaultSize, wxWebViewBackendEdge);


        webView->EnableHistory(false);
        int width, height;

     this->GetSize(&width,&height)		;
     webView->SetSize(width,height);

        webView->SetPage(str, "");

  std::thread http_Serv (th_main);     // spawn new thread that calls th_main()
 http_Serv.detach();
}

wxWidgets_3_2_2_1_EdgeFrame::~wxWidgets_3_2_2_1_EdgeFrame()
{
    //(*Destroy(wxWidgets_3_2_2_1_EdgeFrame)
    //*)
}

#include <wx/msgdlg.h>



void wxWidgets_3_2_2_1_EdgeFrame::OnQuit(wxCommandEvent &event)
{
    Close();
}



