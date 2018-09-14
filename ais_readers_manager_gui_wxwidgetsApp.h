/***************************************************************
 * Name:      ais_readers_manager_gui_wxwidgetsApp.h
 * Purpose:   Defines Application Class
 * Author:    Bojan Rajkovic (bojan.rajkovic@d-logic.rs)
 * Created:   2018-08-29
 * Copyright: Bojan Rajkovic ()
 * License:
 **************************************************************/

#ifndef AIS_READERS_MANAGER_GUI_WXWIDGETSAPP_H
#define AIS_READERS_MANAGER_GUI_WXWIDGETSAPP_H

#include <wx/app.h>

class ais_readers_manager_gui_wxwidgetsApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // AIS_READERS_MANAGER_GUI_WXWIDGETSAPP_H
