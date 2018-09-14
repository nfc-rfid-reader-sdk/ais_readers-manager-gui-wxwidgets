/***************************************************************
 * Name:      ais_readers_manager_gui_wxwidgetsApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Bojan Rajkovic (bojan.rajkovic@d-logic.rs)
 * Created:   2018-08-29
 * Copyright: Bojan Rajkovic ()
 * License:
 **************************************************************/

#include "ais_readers_manager_gui_wxwidgetsApp.h"

//(*AppHeaders
#include "ais_readers_manager_gui_wxwidgetsMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ais_readers_manager_gui_wxwidgetsApp);

bool ais_readers_manager_gui_wxwidgetsApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ais_readers_manager_gui_wxwidgetsFrame* Frame = new ais_readers_manager_gui_wxwidgetsFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
